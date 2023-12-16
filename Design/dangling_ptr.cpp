#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GetMemory(char *p) // p is a local variable, it will be released after the function is over
{
    p = (char *)malloc(100);
}

void GetMemory2(char **p) // use double pointer to solve the problem
{
    *p = (char *)malloc(100);
}

// Three problems:
// 1. p is a local variable, it will be released after the function is over
// 2. p is not checked, it may be NULL
// 3. memory is not released, memory leak
void Test()
{
    char *str = NULL;
    GetMemory(str);
    strcpy(str, "hello world");
    printf(str);
}

void Test2() 
{
    char *str = NULL;
    GetMemory2(&str);
    if (str != NULL)
    {
        strcpy(str, "hello world");
        printf("%s", str);
        free(str);  // 释放内存
    }
}

int main()
{
    Test();
    return 0;
}