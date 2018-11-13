#ifndef ARRAY
#define ARRAY
#include "tipos_primarios.h"

static double ARRAY__ZERO = 0;

void print_if_array(void *array, size_t length, size_t s, void (*print)(const void *), int (*condicao)(const void *)); // OK
void print_array(void *array, size_t length, size_t s, void (*print)(const void *));                                   // OK
void printz_array(void *array, size_t length, size_t s, void (*print)(const void *));                                  // OK

void *arrayz(size_t length, size_t s); // OK

void *dup_array(void *array, size_t length, size_t s); // OK

int unique_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

void *shuffle_array(void *array, size_t length, size_t s); // OK

void *reverse_array(void *array, size_t length, size_t s); // OK

int equals_array(void *ar1, void *ar2, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

int find_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

int max_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK
int min_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

void *resize_array(void *array, size_t length, int new_length, size_t s);         // OK
static void *_resize_array(void *array, size_t length, int new_length, size_t s); // OK

void *remove_if(void *array, size_t length, size_t s, int (*condicao)(const void *));               // OK
static void *_remove_if_array(void *array, size_t length, size_t s, int (*condicao)(const void *)); // OK

void *update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s);         // OK
static void *_update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s); // OK

/*
 * stdlib.h implementa:
 *
 * Ordenação:
 * void qsort(void *array, size_t length, size_t size, int (*cmp)(const void *, const void *));
 *
 * Busca binária:
 * void *bsearch(const void *array, const void *element, size_t length, size_t size, int (*cmp)(const void *, const void *));
 *
*/

/* INT */
int *random_array(int begin, int end, int n);
int mult_array(int *v, int n);
int sum_array(int *v, int n);

/* FLOAT */
float *random_arrayf(float begin, float end, int n);
float mult_arrayf(float *v, int n);
float sum_arrayf(float *v, int n);

/* DOUBLE */
double *random_arraylf(double begin, double end, int n);
double mult_arraylf(double *v, int n);
double sum_arraylf(double *v, int n);
/* IMPLEMENTAÇÕES */

/* Faz a impressão do array enquanto a condição é satisfeita. */
void print_if_array(void *array, size_t length, size_t s, void (*print)(const void *), int (*condicao)(const void *))
{
    printf("( ");
    int n = length * s;
    for (int i = 0; i < n && condicao(array + i); i += s)
    {
        print(array + i);
        printf(", ");
    }
    printf(")");
}
/* Faz a impressão de todo o array. */
void print_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    // Dependencias: print_if_array
    int condicao(const void *element)
    {
        return 1;
    }
    print_if_array(array, length, s, print, condicao);
}
/* Faz a impressão do array até o primeiro valor nulo. */
void printz_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    // Dependencias: print_if_array
    int condicao(const void *element)
    {
        return toDouble(element) != ARRAY__ZERO;
    }
    print_if_array(array, length, s, print, condicao);
}

/* Cria um array de tamanho length do tamanho do tipo s, inicialmente inicializado com zeros. */
void *arrayz(size_t length, size_t s)
{
    return calloc(length, s);
}

/* Duplica o array enviado e retorna um ponteiro do resultado. */
void *dup_array(void *array, size_t length, size_t s)
{
    return memcpy(calloc(length, s), array, length * s);
}

/* Faz a copia do array fonte(source) para o array destino(destiny) e retorna o ponteiro do destino. */
void *copy_array(void *destiny, void *source, size_t length, size_t s)
{
    return memcpy(destiny, source, s * length);
}

/*
 * Este algoritmo busca deixar o array apenas com valores únicos, isto é, sem repetição.
 * Para isto, cada elemento repetido é substituído pelo valor 0.
 * Por fim um vetor auxiliar é criado para posicionar os valores não nulos no início do array recebido.
 * Esta função retorna o novo tamanho do vetor sem as repetições, mas não modifica o seu tamanho
 * original.
 *
 * Complexidade : n * lg n
*/
/* Remove valores duplicados do array. */
int unique_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    // Dependencias: tipos_primarios.h
    qsort(array, length, s, cmp);
    int n, i, j;
    for (i = n = 0; i < (length - 1) * s; i += s, n++)
    {
        if (EQUAL_TO(cmp(array + i, array + i + s)))
        {
            void *elem = array + i;
            for (i += s; i < length * s && EQUAL_TO(cmp(elem, array + i)); i += s)
                memcpy(array + i, &ARRAY__ZERO, s);
            i -= s;
        }
    }
    if (n < length)
    {
        void *tmp = calloc(n, s); // MALLOC tmp
        for (i = j = 0; i < length * s; i += s)
        {
            if (NOT_EQUAL_TO(cmp(array + i, &ARRAY__ZERO)))
            {
                memcpy(tmp + j, array + i, s);
                memcpy(array + i, &ARRAY__ZERO, s);
                j += s;
            }
        }
        memcpy(array, tmp, s * n);
        free(tmp); // FREE tmp
    }
    return n;
}

/*
 * Este algoritmo tem o objetivo de embaralhar os valores de um vetor.
 * Para isto, primeiro se embaralha os valores das posições do intervalo [0, n/2],
 * com posições aletórias entre o intervalo [n/2, n].
 * Por fim, embaralha os valores no intervalo [n/2, n], com valores aleatórios no
 * intervalo [0, n/2].
 *
 * Complexidade : n
*/
/* Embarralha os valores do array. */
void *shuffle_array(void *array, size_t length, size_t s)
{
    // Dependencias: tipos_primarios.h
    srand((unsigned)time(NULL));
    int range = length / 2;
    int begin = length / 2;
    for (int i = 0; i < (length / 2) * s; i += s)
        swap(array + i, array + s * ((rand() % range) + begin), s);
    begin = 0;
    for (int i = (length - 1) * s; i >= (length / 2) * s; i -= s)
        swap(array + i, array + s * ((rand() % range) + begin), s);

    return array;
}

/* Inverte a ordem do array e retorna o array. */
void *reverse_array(void *array, size_t length, size_t s)
{
    // Dependencias: tipos_primarios.h
    for (int i = 0, j = (length - 1) * s; i < j; i += s, j -= s)
        swap(array + i, array + j, s);
    return array;
}

/* Verifica se o array ar1 é igual ao array ar2. */
int equals_array(void *ar1, void *ar2, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    // Dependencias: tipos_primarios.h
    int n = s * length;
    for (int i = 0; i < n; i += s)
        if (NOT_EQUAL_TO(cmp(ar1 + i, ar2 + i)))
        {
            // printf("\n\n%d %d\n\n", toInt(ar1 + i), toInt(ar2 + i)); // DEBUG
            return 0;
        }
    return 1;
}

/* Retorna a posição da primeira ocorrencia do elemento no array. */
int find_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    // Dependencias: tipos_primarios.h
    for (int i = 0; i < length; i += s)
        if (EQUAL_TO(cmp(array + i, element)))
            return i / s;
    return -1;
}

/* Retorna a posição do maior valor do array. */
int max_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    // Dependencias: tipos_primarios.h
    int max = 0;
    for (int i = 1; i < length; i += s)
        if (GREATER_THAN(cmp(array + i, array + max)))
            max = i;
    return max / s;
}
/* Retorna a posição do menor valor do array. */
int min_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    // Dependencias: tipos_primarios.h
    int min = 0;
    for (int i = 1; i < length; i += s)
        if (LESS_THAN(cmp(array + i, array + min)))
            min = i;
    return min / s;
}

/* Realoca o array para um novo tamanho. */
#define resize_array(array, length, new_length, s) ({array = _resize_array(array, length, new_length, s); array; })
static void *_resize_array(void *array, size_t length, int new_length, size_t s)
{
    // Dependencias: copy_array
    void *new = copy_array(calloc(new_length, s), array, (length < new_length ? length : new_length), s);
    free(array);
    return new;
}

#define remove_if_array(array, length, s, condicao) ({array = _remove_if(array, length, s, condicao); array; })
static void *_remove_if_array(void *array, size_t length, size_t s, int (*condicao)(const void *))
{
    void *new = calloc(length, s);
    int n = length * s;
    for (int i = 0, j = 0; i < n; i += s)
        if (!condicao(array + i))
            memcpy(new + j, array + i, s);
    free(array);
    return new;
}

#define update_array(ar1, len1, ar2, len2, s) ({ar1 = _update_array(ar1, len1, ar2, len2, s); ar1; })
static void *_update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s)
{
    // Dependencias: resize_array, copy_array
    resize_array(ar1, len1, len1 + len2, s);
    copy_array(ar1 + len1 * s, ar2, len2, s);
    return ar1;
}

void rearrange_positives_negatives_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    void *pivo = calloc(1, s);
    length *= s;
    for (int j = 0, i = -s; j < length; j += s)
    {
        if (LESS_THAN(cmp(array + j, pivo)))
        {
            i += s;
            swap(array + j, array + i, s);
        }
    }
}

void merge_sorted_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s, int (*cmp)(const void *, const void *))
{
    /* NEED TESTS */
    int next_gap(int gap, size_t s)
    {
        return gap > s ? (((gap / 2) + (gap % 2)) / s) * s : 0;
    }
    int i, j;
    len1 *= s;
    len2 *= s;
    int gap = len1 + len2;
    for (gap = next_gap(gap, s); gap; gap = next_gap(gap, gap + s))
    {
        for (i = 0; i + gap < len1; i += s)
            if (GREATER_THAN(cmp(ar1 + i, ar1 + i + gap)))
                swap(ar1 + i, ar1 + i + gap, s);

        for (j = gap > len1 ? gap - len1 : 0; i < len1 && j < len2; j += s, i += s)
            if (GREATER_THAN(cmp(ar1 + i, ar2 + j)))
                swap(ar1 + i, ar2 + j, s);

        if (j < len2)
            for (j = 0; j + gap < len2; j++)
                if (GREATER_THAN(cmp(ar2 + j, ar2 + j + gap)))
                    swap(ar2 + j, ar2 + j + gap, s);
    }
}

/* INT */
int *random_array(int begin, int end, int n)
{
    // Dependencias: tipos_primarios.h
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    int *v = calloc(n, sizeof(int));

    int range = end - begin;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = (rand() % range) + begin;

    return v;
}
int mult_array(int *v, int n)
{
    int m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
int sum_array(int *v, int n)
{
    int s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}

/* FLOAT */
float *random_arrayf(float begin, float end, int n)
{
    // Dependencias: tipos_primarios.h
    if (begin > end)
        swap(&begin, &end, sizeof(float));

    float *v = calloc(n, sizeof(float));

    const int MAX = 1e6;

    int range = MAX - (begin / end) * MAX;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = ((rand() * 1000 + rand()) % range) / (float)MAX * end + begin;

    return v;
}
float mult_arrayf(float *v, int n)
{
    float m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
float sum_arrayf(float *v, int n)
{
    float s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}

/* DOUBLE */
double *random_arraylf(double begin, double end, int n)
{
    if (begin > end)
        swap(&begin, &end, sizeof(double));

    double *v = calloc(n, sizeof(double));
    int size = sizeof(double);
    const ULLI MAX = 1e16;

    ULLI range = MAX - (begin / end) * MAX;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = (((ULLI)(rand() * 1e10 + rand() * 1e8 + rand() * 1e4 + rand()) % range) / (double)MAX) * end + begin;

    return v;
}
double mult_arraylf(double *v, int n)
{
    double m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
double sum_arraylf(double *v, int n)
{
    double s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}
#endif
