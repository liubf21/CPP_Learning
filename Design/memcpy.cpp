#include <iostream>

void* my_memcpy(void* dest, const void* src, size_t num) // overlap is not considered
{
    if (NULL == dest || NULL == src) // assert(dest); assert(src);
    {
        return NULL;
    }
    char* dest_ = (char*)dest; // char* is used to avoid pointer arithmetic
    char* src_ = (char*)src;
    while (num--)
    {
        *dest_++ = *src_++; // copy byte, then move pointer
    }
    return dest;
}

void* my_memmove(void* dest, const void* src, size_t num)
{
    if (NULL == dest || NULL == src)
    {
        return NULL;
    }
    void* ret = dest;
    char *dest_ = (char*)dest;
    char *src_ = (char*)src;
    if (dest_ < src_)
    {
        while (num--)
        {
            *dest_++ = *src_++;
        }
    }
    else // if overlap, copy from end to start
    {
        dest_ += num - 1;
        src_ += num - 1;
        while (num--)
        {
            *dest_-- = *src_--;
        }
    }
    return ret;
}

int main()
{
    char str[] = "hello world";
    std::cout << str << std::endl;
    char dest[20] = { 0 };
    my_memmove(str+3, str, sizeof(str));
    std::cout << str << std::endl;
    my_memcpy(str+3, str, sizeof(str));
    std::cout << str << std::endl;

    return 0;
}