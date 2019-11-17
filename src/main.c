#include <arraylist_new.h>
#include <stdio.h>

typedef struct _vec4 {
    unsigned long long x;
    unsigned long long y;
    unsigned long long z;
    unsigned long long w;
} vec4;

unsigned long long my_pow(int base, int power)
{
    unsigned long long val = base;
    if(power == 0)
        return 1;
    if(power == 1)
        return base;
    for(int i = 0; i < power-1; i++)
        val = val * base;
    return val;
}

int main(void)
{
    char ***file_list = init_arraylist(char **);
    char **file = init_arraylist(char *);
    for(char c = 32; c < 97+26; c++)
    {
        char *str = malloc(sizeof(char)*2);
        str[0] = c;
        str[1] = '\0';
        arraylist_push(file, str);
    }
    arraylist_push(file_list, file);
    for(size_t i = 0; i < arraylist_length(file_list); i++)
    {
        printf("Printing the Contents of File: %zu\n", i);
        printf("--------------------------------\n");
        for(size_t j = 0; j < arraylist_length(file_list[i]); j++)
        {
            printf("Line %03zu: %s\n", j, file_list[i][j]);
        }
        arraylist_free_all(file_list[i]);
        destroy_arraylist(file_list[i]);
    }
    destroy_arraylist(file_list);
    return 0;
}
