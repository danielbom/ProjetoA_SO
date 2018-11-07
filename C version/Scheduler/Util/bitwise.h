#include "tipos_primarios.h"

#define bit8 unsigned char
#define bit32 unsigned int
#define bit64 unsigned long long int

#define _last_bit_8 0b10000000
#define _last_bit_32 0b10000000000000000000000000000000
#define _last_bit_64 0b1000000000000000000000000000000000000000000000000000000000000000

/*
 * Esta biblioteca tem como objetivo auxiliar na manipulação bit a bit de variáveis.
 * Está definido as variaveis bit8, bit16, bit32, onde os numeros representam a
 * quantidade de bits usadas.
 * Bitwise operators
 * 
 * and : &
 * or  : |
 * xor : ^
 * not : ~
 * 
 * Os bits são interpretados no formato big-endian (primeiros digitos possuem maior peso).
 * A posição começa em 0 (menor peso) e vai até o tamanho do bit -1 (maior peso).
*/
bit64 bit(bit8 position);

/* Retona se determinados bits estão setados ou não. */
bool is_set_bit_8(bit8 bits, bit8 mask);
bool is_set_bit_32(bit32 bits, bit32 mask);
bool is_set_bit_64(bit64 bits, bit64 mask);

/* Retorna o resultado do valor dos bits marcando os valores da máscara. */
bit8 set_bit_8(bit8 bits, bit8 maks);
bit32 set_bit_32(bit32 bits, bit32 maks);
bit64 set_bit_64(bit64 bits, bit64 maks);

/* Retorna o resultado do valor dos bits desmarcando os valores da máscara. */
bit8 unset_bit_8(bit8 bits, bit8 maks);
bit32 unset_bit_32(bit32 bits, bit32 maks);
bit64 unset_bit_64(bit64 bits, bit64 maks);

/* Converte uma variável do tipo bit para string. */
char *to_bin_8(bit8 valor);
char *to_bin_32(bit32 valor);
char *to_bin_64(bit64 valor);

/* Imprime uma variável do tipo bit. */
void printBin8(bit8 valor);
void printBin32(bit32 valor);
void printBin64(bit64 valor);

bit64 bit(bit8 position)
{
    return 1ull << position;
}

// 8 bits
bool is_set_bit_8(bit8 bits, bit8 mask)
{
    return (bits & mask) == mask;
}
bit8 set_bit_8(bit8 bits, bit8 maks)
{
    return bits | maks;
}
bit8 unset_bit_8(bit8 bits, bit8 maks)
{
    return bits & ~maks;
}
char *to_bin_8(bit8 valor)
{
    char bin[9] = "\0";
    for (bit8 i = _last_bit_8, j = 0; i; i >>= 1, j++)
        itoa(is_set_bit_8(valor, i), bin + j, 2);
    return strdup(bin);
}
void printBin8(bit8 valor)
{
    for (bit8 i = _last_bit_8; i; i >>= 1)
        printf("%d", is_set_bit_8(valor, i));
}

// 32 bits
bool is_set_bit_32(bit32 bits, bit32 mask)
{
    return (bits & mask) == mask;
}
bit32 set_bit_32(bit32 bits, bit32 maks)
{
    return bits | maks;
}
bit32 unset_bit_32(bit32 bits, bit32 maks)
{
    return bits & ~maks;
}
char *to_bin_32(bit32 valor)
{
    char bin[33] = "\0";
    for (bit32 i = _last_bit_32, j = 0; i; i >>= 1, j++)
        itoa(is_set_bit_32(valor, i), bin + j, 2);
    return strdup(bin);
}
void printBin32(bit32 valor)
{
    for (bit32 i = _last_bit_32; i; i >>= 1)
        printf("%d", is_set_bit_32(valor, i));
}

// 64 bits
bool is_set_bit_64(bit64 bits, bit64 mask)
{
    return (bits & mask) == mask;
}
bit64 set_bit_64(bit64 bits, bit64 maks)
{
    return bits | maks;
}
bit64 unset_bit_64(bit64 bits, bit64 maks)
{
    return bits & ~maks;
}
char *to_bin_64(bit64 valor)
{
    char bin[129] = "\0";
    for (bit64 i = _last_bit_64, j = 0; i; i >>= 1, j++)
        itoa(is_set_bit_64(valor, i), bin + j, 2);
    return strdup(bin);
}
void printBin64(bit64 valor)
{
    for (bit64 i = _last_bit_64; i; i >>= 1)
        printf("%d", is_set_bit_64(valor, i));
}