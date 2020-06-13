#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDECIMALACCURACY 6

void Add(const double *, const double *);
void Sub(const double *, const double *);
void Mul(const double *, const double *);
void Div(const double *, const double *);
int CountDecimals(const double *);

int main() {
    void (*calculator[4])(double *, double *) = {Add, Sub, Mul, Div};
    int operation;
    double a;
    double b;

    printf("Calculator options:\n[1] Addition\n[2] Subtraction\n[3] Multiplication\n[4] Division\n");

    printf("\nEnter what operation you would like to perform (1-4): ");
    fflush(stdout);
    scanf("%d", &operation);

    while(operation != -1)
    {
        printf("\nEnter the first number: ");
        fflush(stdout);
        scanf("%.*lf", MAXDECIMALACCURACY, &a);//scanf does a bad job at reading the console, MAXDECIMALACCURACY is used to limit cascading error

        printf("\nEnter the second number: ");
        fflush(stdout);
        scanf("%.*lf", MAXDECIMALACCURACY, &b);//scanf does a bad job at reading the console, MAXDECIMALACCURACY is used to limit cascading error

        (*calculator[operation-1])(&a, &b);

        printf("\nEnter what operation you would like to perform: ");
        fflush(stdout);
        scanf("%d", &operation);
    }


    return 0;
}

/**
 * This function is used to have more control over how many decimals are being shown. The printf options for %.6lf would force 6 trailing zeros for
 * numbers that may have less than 6. This method removes trailing zeros, and lets the max decimals shown be set through a definition.
 * @param a Number to determine the number of decimals for.
 * @return The number of decimal places used in the given number.
 */
 //could be done by using strtok and then determining the size of the second array
int CountDecimals(const double *a)
{
    char *doubleString = malloc(sizeof(char) * MAXDECIMALACCURACY + sizeof(char)); //I had issues with strchr, and allocating memory for the string
    // this way
    // fixed it.
    sprintf(doubleString, "%.*lf", MAXDECIMALACCURACY, *a); //convert the double into a string. Using %lf means there will always be something
    // after the decimal.

    char *decimalstr = strchr(doubleString, '.'); //copy only the part of the string after the decimal

    // countDecimal starts at the last digit. If it's a trailing zero, it's removed from the string. Once there are no trailing zeros, the loop
    // breaks and the count is returned.
    int countDecimal;
    for(countDecimal = strlen(decimalstr) - 1 ; countDecimal >= 0; countDecimal --)
    {
        if(decimalstr[countDecimal] == '0')
            decimalstr[countDecimal] = '/0';
        else
            break;
    }

    return countDecimal;
}

/**
 *
 * @param a
 * @param b
 */
void Add(const double *a, const double *b)
{
    double result = (*a + *b);
    printf("\n%.*lf + %.*lf = %.*lf\n", CountDecimals(a), *a, CountDecimals(b), *b, CountDecimals(&result), result);
}

/**
 *
 * @param a
 * @param b
 */
void Sub(const double *a, const double *b)
{
    double result = (*a-*b);
    printf("\n%.*lf - %.*lf = %.*lf\n", CountDecimals(a), *a, CountDecimals(b), *b, CountDecimals(&result), result);
}

/**
 *
 * @param a
 * @param b
 */
void Mul(const double *a, const double *b)
{
    double result = (*a) * (*b);
    printf("\n%.*lf x %.*lf = %.*lf\n", CountDecimals(a), *a, CountDecimals(b), *b, CountDecimals(&result), result);
}

/**
 *
 * @param a
 * @param b
 */
void Div(const double *a, const double *b)
{
    double result = *a / *b;
    printf("\n%.*lf / %.*lf = %.*lf\n", CountDecimals(a), *a, CountDecimals(b), *b, CountDecimals(&result), result);
}