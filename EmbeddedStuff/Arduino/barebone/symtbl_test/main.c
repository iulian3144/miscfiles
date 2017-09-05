#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"


extern SYMBOL standTbl[];

int test = 2;
char *hello()
{
    return "hello";
}

int main(int argc, char const *argv[])
{
    printf("hw\n");
    printf("standTbl[0]->nameHNode: %p\n", standTbl[0].nameHNode);
    printf("standTbl[0]->name     : %s\n", standTbl[0].name);
    printf("standTbl[0]->value    : %p\n", standTbl[0].value);
    printf("standTbl[0]->symRef   : %lu\n", standTbl[0].symRef);
    printf("standTbl[0]->group    : %d\n", standTbl[0].group);
    printf("standTbl[0]->type     : 0x%x\n", standTbl[0].type);
    return 0;
}
