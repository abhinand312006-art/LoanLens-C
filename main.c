
#include <stdio.h>
#include <math.h>

double emi(double p, double r, int n)
{
    r = r / 1200;

    if (r == 0)
        return p / n;

    return p * r * pow(1 + r, n) /
           (pow(1 + r, n) - 1);
}

double amount()
{
    double x;

    do {
        printf("Enter loan amount: ");
        if (scanf("%lf", &x) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            x = -1;
        }
        else if (x <= 0)
            printf("Amount must be positive!\n");

    } while (x <= 0);

    return x;
}

double rate()
{
    double x;

    do {
        printf("Enter annual interest rate (0-50): ");
        if (scanf("%lf", &x) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            x = -1;
        }
        else if (x < 0 || x > 50)
            printf("Rate must be between 0 and 50!\n");

    } while (x < 0 || x > 50);

    return x;
}

int tenure()
{
    int n;

    do {
        printf("Enter tenure in months: ");
        if (scanf("%d", &n) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            n = 0;
        }
        else if (n <= 0)
            printf("Tenure must be positive!\n");

    } while (n <= 0);

    return n;
}

void calculate()
{
    double p, r, e, interest, principal, balance, total = 0;
    int n;

    p = amount();
    r = rate();
    n = tenure();

    e = emi(p, r, n);
    balance = p;

    printf("\nMonthly EMI = %.2f\n", e);
    printf("\nMonth\tInterest\tPrincipal\tBalance\n");

    for (int i = 1; i <= n && balance > 0.01; i++) {
        interest = balance * r / 1200;
        principal = e - interest;

        if (principal > balance)
            principal = balance;

        balance = balance - principal;
        total = total + interest;

        if (balance < 0.01)
            balance = 0;

        printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
               i, interest, principal, balance);
    }

    printf("\nTotal Interest = %.2f\n", total);
    printf("Total Payment = %.2f\n", p + total);
}

void compare()
{
    double p, r, e, interest, lowest = -1;
    int n, count, best = 0;

    p = amount();
    n = tenure();

    do {
        printf("Enter number of offers (2 or 3): ");
        if (scanf("%d", &count) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            count = 0;
        }
    } while (count < 2 || count > 3);

    for (int i = 1; i <= count; i++) {
        printf("\nOffer %d\n", i);

        r = rate();
        e = emi(p, r, n);
        interest = e * n - p;

        printf("Monthly EMI = %.2f\n", e);
        printf("Total Interest = %.2f\n", interest);

        if (lowest < 0 || interest < lowest) {
            lowest = interest;
            best = i;
        }
    }

    printf("\nBest Offer = Offer %d\n", best);
    printf("Lowest Interest = %.2f\n", lowest);
}

void prepayment()
{
    double p, r, e, balance, interest;
    double principal, extra, totalInterest = 0;
    int n, month, i;

    p = amount();
    r = rate();
    n = tenure();

    e = emi(p, r, n);
    balance = p;

    printf("\nOriginal EMI = %.2f\n", e);

    do {
        printf("Enter prepayment month (1 to %d): ", n - 1);

        if (scanf("%d", &month) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            month = 0;
        }
    } while (month < 1 || month >= n);

    extra = amount();

    for (i = 1; i <= n && balance > 0.01; i++) {
        interest = balance * r / 1200;
        principal = e - interest;

        if (principal > balance)
            principal = balance;

        balance = balance - principal;
        totalInterest = totalInterest + interest;

        if (balance < 0.01)
            balance = 0;

        if (i == month) {
            balance = balance - extra;

            if (balance < 0)
                balance = 0;
        }
    }

    printf("\nOriginal Tenure = %d months\n", n);
    printf("New Loan Closure Month = %d\n", i - 1);
    printf("Total Interest After Prepayment = %.2f\n",
           totalInterest);
    printf("Tenure Reduced = %d months\n", n - (i - 1));
}

int main()
{
    int choice;

    do {
        printf("\n========== LOANLENS ==========\n");
        printf("1. Calculate EMI and Schedule\n");
        printf("2. Compare Loan Offers\n");
        printf("3. One-Time Prepayment\n");
        printf("4. Exit\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                calculate();
                break;

            case 2:
                compare();
                break;

            case 3:
                prepayment();
                break;

            case 4:
                printf("Thank you for using LoanLens!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
