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

void Test() // 三个问题野指针，内存泄露，和值传递
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