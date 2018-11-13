#include <string.h>

char *replace_string(char const *const original, char const *const pattern, char const *const replacement)
{
    size_t const replacement_length = strlen(replacement);
    size_t const original_length = strlen(original);
    size_t const pattern_length = strlen(pattern);

    size_t pattern_count = 0;
    const char *p;
    const char *token;

    // find how many times the pattern occurs in the original string
    for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        pattern_count++;

    // allocate memory for the new string
    size_t const returned_length = original_length + pattern_count * (replacement_length - pattern_length);
    char *const returned = calloc((returned_length + 1), sizeof(char));

    if (returned != NULL)
    {
        // copy the original string,
        // replacing all the instances of the pattern
        char *p2 = returned;
        for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        {
            size_t const skip_length = token - p;
            // copy the section until the occurence of the pattern
            strncpy(p2, p, skip_length);
            p2 += skip_length;
            // copy the replacement
            strncpy(p2, replacement, replacement_length);
            p2 += replacement_length;
        }
        // copy the rest of the string.
        strcpy(p2, p);
    }
    return returned;
}

char **split_string(char *original, char *pattern, int *parts)
{
    size_t pattern_length = strlen(pattern);
    size_t n = 0;
    char *p;
    char *token;

    // encontra quantas vezes o modelo aparece na string
    for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        n++;

    char **returned = calloc(n + 1, sizeof(char *)); // MALLOC returned

    if (returned != NULL)
    {
        *parts = n + 1;
        int i = 0;
        // duplica cada parte da string sem o modelo
        for (p = original; token = strstr(p, pattern); p = token + pattern_length, i++)
        {
            char tmp = *token;
            returned[i] = strdup(p);
            *token = *pattern;
            if (returned[i] == NULL) // Se der pau
            {
                while (i--)
                    free(returned[i - 1]);
                free(returned); // FREE returned
                return NULL;
            }
        }
        returned[i] = strdup(p);
    }

    return returned;
}

char **split_string2(char *original, char *pattern)
{
    size_t pattern_length = strlen(pattern);
    size_t n = 0;
    char *p;
    char *token;

    // encontra quantas vezes o modelo aparece na string
    for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        n++;

    char **returned = calloc(n + 2, sizeof(char *)); // MALLOC returned

    if (returned != NULL)
    {
        p = original;
        for (int i = 0; p = spliting_string(p, pattern, pattern_length, returned[i]); i++)
        {
            if (returned[i] == NULL)
            {
                while (i--)
                    free(returned[i - 1]);
                free(returned);
                return NULL;
            }
        }
    }

    return returned;
}

char *spliting_string(char *ptr, char *pattern, int length_pattern, char **returned)
{
    char *token = strstr(ptr, pattern);
    if (token)
    {
        *token = 0;
        *returned = strdup(ptr);
        *token = *pattern;
        return token + length_pattern;
    }
    *returned = strdup(ptr);
    return NULL;
}

int count_caracter(char *original, char caracter)
{
    int count = 0;
    for (char *p = original; *p; p++)
        count += *p == caracter;
    return count;
}

int count_substrings(char *original, char *pattern)
{
    size_t const pattern_length = strlen(pattern);
    int count = 0;
    char *p, *token;
    for (p = original; token = strstr(p, pattern); p = token + pattern_length)
        count++;
    return count;
}