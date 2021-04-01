#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define CAPACITY 20000

uint32_t hash(const char *str)
{
    uint32_t value = 0;
    uint32_t i=0;
    uint32_t len=strlen(str);

    for (;i <len ; i++)
    {
    	value= 37*value + str[i];

    	value= value%CAPACITY;

    	
    }
    return value;
};
