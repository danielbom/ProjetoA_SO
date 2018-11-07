#include "tipos_primarios.h"

// Limite max: n = 170
double factorial(double n);
double factorial_partial(double n, double k);

#define GEN_FIBBONATTI(x) gen_fibbonatti(x)

double gen_fibbonatti(bool run);

double PA_term(double a1, double r, int n);
double PA_sum(double a1, double r, int n);

double PG_term(double a1, double r, int n);
double PG_sum(double a1, double r, int n);
double PG_mult(double a1, double r, int n);

int sum_1(int begin, int end);
int sum_n(int begin, int end);

double permutation(double n);
double arranjo(double n, double k);
double combination(double n, double k);

/* IMPLEMENTAÇÕES */

double factorial(double n)
{
    n = trunc(n);
    if (n <= 0)
        return 1;
    double x = n;
    while (--n)
        x *= n;
    return x;
}

double factorial_partial(double n, double k)
{
    n = trunc(n);
    k = trunc(k);
    if (n <= 0)
        return 1;
    double x = n;
    while (--n > k)
        x *= n;
    return x;
}

double gen_fibbonatti(bool run)
{
    static double a = 0;
    static double b = 1;
    double r;
    if (run)
    {
        r = a;
        a = b;
        b = a + r;
        return r;
    }
    a = 0;
    b = 1;
}

double PA_term(double a1, double r, int n)
{
    return a1 + (n - 1) * r;
}
double PA_sum(double a1, double r, int n)
{
    return (n * (a1 + PA_term(a1, r, n))) / 2.0;
}

double PG_term(double a1, double r, int n)
{
    return a1 * pow(r, n - 1);
}
double PG_sum(double a1, double r, int n)
{
    return (a1 * (1 - pow(r, n))) / (1 - r);
}
double PG_mult(double a1, double r, int n)
{
    return pow(sqrt(a1 * PG_term(a1, r, n)), n + 1);
}

int sum_1(int begin, int end)
{
    return end - (begin - 1);
}
int sum_n(int begin, int end)
{
    return (end * (end + 1) / 2) - (begin * (begin + 1) / 2);
}

double permutation(double n)
{
    return factorial(n);
}
double arrangement(double n, double k)
{
    //return factorial(n) / factorial(n - k);
    return factorial_partial(n, n - k);
}
double combination(double n, double k)
{
    double min = k < (n - k) ? k : n - k;
    //return factorial(n) / (factorial(k) * factorial(n - k));
    return arrangement(n, min) / factorial(min);
}