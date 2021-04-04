#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define CAPACITY 50000

uint32_t hash(const char *str)
{
    uint32_t value = 5381;
    uint32_t i=0;
    uint32_t len=strlen(str);

    for (;i <len ; i++)
    {
    	value= 33*value + str[i];
    	value= value=value%5381;
    }
    return value;
};
