#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbol.h"

extern SYMBOL standTbl[];
extern ULONG standTblSize;

unsigned int running = 1;

#define SHELL_CMD_LINE_SIZE 256

void ls()
{
    printf("Listing directory contents...\n");
}

void hello()
{
    printf("hello\n");
}

void quit()
{
    running = 0;
}

void lkup(char *name)
{
    int i;
    printf("Looking for %s\n", name);
    printf("          Value      Name\n");
    for(i = 0; i < standTblSize; ++i)
    {
        if(strcmp(name, standTbl[i].name) == 0)
        {
            printf("%p %10s\n", standTbl[i].value, standTbl[i].name);
            continue;
        }
    }
}

static void shellGetCmd(char buffer[])
{
    char ch = 0;
    unsigned int bytes_read = 0;
    while(1)
    {
        if(bytes_read < SHELL_CMD_LINE_SIZE)
            ch = getc(stdin);
        if(ch == '\n')
            return;
        buffer[bytes_read++] = ch;
    }
}

int main(int argc, char const *argv[])
{
    const char delim[] = " ";
    char cmd_buf[SHELL_CMD_LINE_SIZE];
    char *cmd;
    void (*foo)(char *);
    int i = 0;

    memset(cmd_buf, 0, SHELL_CMD_LINE_SIZE);

    while(running)
    {
        printf("> ");
        shellGetCmd(cmd_buf);
        // printf("%s\n", cmd_buf);
        // return 1;

        cmd = strtok(cmd_buf, delim);
        for(i = 0; i < standTblSize; ++i)
        {
            if(cmd == 0)
                break;
            if(strcmp(cmd, standTbl[i].name) == 0)
            {
                foo = (void (*)(char *))standTbl[i].value;
                foo(strtok(NULL, delim));
                memset(cmd_buf, 0, SHELL_CMD_LINE_SIZE);
                break;
            }
            if(i == (standTblSize - 1))
            {
                printf("Unknown command!\n");
                break;
            }
        }
    }

    return 0;
}
