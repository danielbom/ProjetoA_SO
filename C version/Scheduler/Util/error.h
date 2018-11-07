/*
 * FUNÇÕES DE DETECÇÃO DE ERROS
*/

bool SizeError(size_t size, char *function)
{
    if (size <= 0)
    {
        printf("\nSizeError in function %s. Variable size must be greater than zero (0).\n", function);
        return true;
    }
    return false;
}
bool NullPointerError(const void *pointer, const char *function)
{
    if (pointer == NULL)
    {
        printf("\nNullPointerError in function %s.\n", function);
        return true;
    }
    return false;
}
bool IndexOutOfTheRangeError(int index, int range_initial, int range_final, char *function)
{
    if (index < range_initial || index >= range_final)
    {
        printf("\nIndexOutOfTheRangeError in function %s.\n", function);
        return true;
    }
    return false;
}