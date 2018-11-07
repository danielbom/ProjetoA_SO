#include <math.h>

#ifndef LOG2
#define LOG2(x) (log(x) / M_LN2)
#endif

#ifndef ULLI
#define ULLI unsigned long long int
#endif

#ifndef PRIMO
#define PRIMO

#include "array.h"

// LENGTH_PRIME_FACTORS == log2(x)
#define LENGTH_PRIME_FACTORS(x) LOG2(x)
#define LENGTH_DIVIDERS(x) (LENGTH_PRIME_FACTORS(x) * (LENGTH_PRIME_FACTORS(x) + 1)) / 2

typedef struct primo
{
    bool *vetor;
    int n;
} PRIMOS;

PRIMOS *criar_primo(int lim);
void destruir_primo(PRIMOS *P);
bool eh_primo_busca(PRIMOS *P, int x);

bool isprime(ULLI n);
bool eh_primo_rec(ULLI num);
bool eh_primo(ULLI num);

#define IS_PRIME(x) eh_primo(x)

ULLI gen_primos_w(bool run);
ULLI gen_primos_2(bool run);

#define GEN_PRIMES(x) gen_primos(x)

int *fatores_primos_iter(int n);
int *fatores_primos_gen(int n);

#define PRIME_FACTORS(x) fatores_primos_gen(x)

int *divisores_lazy(int num);
int *divisores_optm(int num);
ULLI *divisores_ulli(ULLI num);

#define DIVIDERS_ULLI(x) divisores_ulli(x)
#define DIVIDERS(x) divisores_optm(x)

/* IMPLEMENTAÇÕES DAS FUNÇÕES */

/*  COM BUSCA  */
PRIMOS *criar_primo(int lim)
{
    lim++;
    PRIMOS *P = (PRIMOS *)malloc(sizeof(PRIMOS));
    P->vetor = (bool *)calloc(lim, sizeof(bool));
    P->n = lim;
    P->vetor[2] = true;
    for (int i = 3; i < P->n; i += 2)
        P->vetor[i] = IS_PRIME(i);
    return P;
}
void destruir_primo(PRIMOS *P)
{
    free(P->vetor);
    free(P);
}
bool eh_primo_busca(PRIMOS *P, int x)
{
    return P->vetor[x];
}
/* FIM */
bool eh_primo_rec(ULLI num)
{
    // Aguenta valores de até e inclusive alguns proximos a 1e10, provavelmente pq a profundidade de recursão é muito grande (1e5).
    // Seu tempo de resposta é 2 vezes maior que a versão iterativa.
    bool _eh_primo_rec(ULLI num, ULLI mod)
    {
        return num < mod * mod ? true : IS_DIVISIBLE(num, mod) ? false : _eh_primo_rec(num, mod + 2);
    }
    return num < 2ull ? false : num == 2ull ? true : IS_DIVISIBLE(num, 2ull) ? false : _eh_primo_rec(num, 3);
}
bool eh_primo(ULLI num)
{
    if (num < 2)
        return false;
    if (num < 4)
        return true;
    if (IS_DIVISIBLE(num, 2) || IS_DIVISIBLE(num, 3))
        return false;
    ULLI i = 5;
    ULLI w = 2;
    while (i * i <= num)
    {
        if (IS_DIVISIBLE(num, i))
            return false;
        i += w;
        w = 6 - w;
    }
    return true;
}

/*
 * A variavel run mantem o gerador ligado enquanto true.
 * Se false, reinicia o gerador.
*/
ULLI gen_primos(bool run)
{
    static ULLI i = 2;
    ULLI r;
    if (run)
    {
        while (!IS_PRIME(i))
            i++;
        r = i;
        i++;
        return r;
    }
    i = 2;
}
ULLI gen_primos_2(bool run)
{
    static ULLI i = 2;
    ULLI r;
    if (run)
    {
        if (i == 2)
        {
            r = i++;
            return r;
        }

        while (!IS_PRIME(i))
            i += 2;
        r = i;
        i += 2;
        return r;
    }
    i = 2;
}
ULLI gen_primos_w(bool run)
{
    static ULLI i = 2;
    static int w = 2;
    ULLI r;
    if (run)
    {
        if (i == 2)
        {
            r = i++;
            return r;
        }
        if (i == 3)
        {
            r = i;
            i += 2;
            return r;
        }

        while (!IS_PRIME(i))
        {
            i += w;
            w = 6 - w;
        }
        r = i;
        i += w;
        w = 6 - w;
        return r;
    }
    i = 2;
    w = 2;
}

int *divisores_lazy(int num)
{
    assert(num >= 0);
    // Identifica os divisores sem optimizações Ondem (n)
    int *divs = arrayz(LENGTH_DIVIDERS(num), sizeof(int));
    int k = 0;
    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            divs[k++] = i;
        }
    }
    divs[k++] = num;
    return divs;
}
int *divisores_optm(int num)
{
    assert(num >= 0);
    // Encontra os divisores de um número com optimizações
    int *divs = arrayz(LENGTH_DIVIDERS(num), sizeof(int)); // MALLOC divs
    int lim = num;
    int k = 0;
    int i, j;
    if (!IS_PRIME(num))
    {
        for (i = 2; i < lim; i++)
        {
            if (num % i == 0)
            {
                divs[k++] = i;
                divs[k++] = num / i;
                lim = num / i;
                if (IS_PRIME(lim))
                { // Impede o pior caso Ordem(n)
                    divs[k++] = lim;
                    lim = 0;
                }
            }
        }
    }
    divs[k++] = num;
    unique_array(divs, k + 1, sizeof(int), cmpInt);
    return divs;
}

ULLI *divisores_ulli(ULLI num)
{
    // Encontra os divisores de um número com optimizações
    ULLI *divs = arrayz(LENGTH_DIVIDERS(num), sizeof(ULLI)); // MALLOC divs
    ULLI lim = num;
    int k = 0;
    int i, j;
    if (!IS_PRIME(num))
    {
        for (i = 2; i < lim; i++)
        {
            if (num % i == 0)
            {
                divs[k++] = i;
                divs[k++] = num / i;
                lim = num / i;
                if (IS_PRIME(lim))
                { // Impede o pior caso Ordem(n)
                    divs[k++] = lim;
                    lim = 0;
                }
            }
        }
    }
    divs[k++] = num;
    unique_array(divs, k + 1, sizeof(ULLI), cmpInt);
    return divs;
}

int *fatores_primos_iter(int n)
{
    assert(n >= 0);
    int *primos = arrayz(LENGTH_PRIME_FACTORS(n), sizeof(int));
    int k = 0;
    int i = 2;
    while (n != 1)
    {
        if (IS_PRIME(i))
        {
            while (n % i == 0)
            {
                primos[k++] = i;
                n /= i;
            }
            if (IS_PRIME(n))
            { // Evita o pior caso
                primos[k++] = n;
                n = 1;
            }
        }
        i++;
    }
    return primos;
}
int *fatores_primos_gen(int n)
{
    assert(n >= 0);
    int *primos = arrayz(LENGTH_PRIME_FACTORS(n), sizeof(int));
    int k = 0;
    int primo;
    while (n != 1)
    {
        primo = GEN_PRIMES(true);
        while (n % primo == 0)
        {
            primos[k++] = primo;
            n /= primo;
        }
        if (IS_PRIME(n))
        { // Evita o pior caso
            primos[k++] = n;
            n = 1;
        }
    }
    GEN_PRIMES(false);
    return primos;
}

#endif