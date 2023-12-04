// Purpose: Source file for string matching algorithms.
#include <iostream>
#include <string>
#include <vector>


// Brute force string matching algorithm.
int g_BruteForce(const std::string& strText, const std::string& strPattern)
{
    int i = 0;
    int j = 0;
    int nTextLen = strText.length();
    int nPatternLen = strPattern.length();
    while (i < nTextLen && j < nPatternLen)
    {
        if (strText[i] == strPattern[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == nPatternLen)
    {
        return i - j;
    }
    return -1;
}

// KMP string matching algorithm.
void g_GetNext(const std::string& strPattern, int* next);
int g_KMP(const std::string& strText, const std::string& strPattern)
{
    int i = 0;
    int j = 0;
    int nTextLen = strText.length();
    int nPatternLen = strPattern.length();
    int* next = new int[nPatternLen];
    g_GetNext(strPattern, next);
    while (i < nTextLen && j < nPatternLen)
    {
        if (j == -1 || strText[i] == strPattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    delete[] next;
    if (j == nPatternLen)
    {
        return i - j;
    }
    return -1;
}

// Get the next array for KMP algorithm.
void g_GetNext(const std::string& strPattern, int* next)
{
    int i = 0;
    int j = -1;
    int nPatternLen = strPattern.length();
    next[0] = -1;
    while (i < nPatternLen - 1)
    {
        if (j == -1 || strPattern[i] == strPattern[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

// BM string matching algorithm.
void g_GetBMBc(const std::string& strPattern, int* bmBc);
void g_GetBMGs(const std::string& strPattern, int* bmGs);
int g_BM(const std::string& strText, const std::string& strPattern)
{
    int i = 0;
    int j = 0;
    int nTextLen = strText.length();
    int nPatternLen = strPattern.length();
    int* bmBc = new int[256];
    int* bmGs = new int[nPatternLen];
    g_GetBMBc(strPattern, bmBc);
    g_GetBMGs(strPattern, bmGs);
    while (i <= nTextLen - nPatternLen)
    {
        for (j = nPatternLen - 1; j >= 0 && strText[i + j] == strPattern[j]; j--);
        if (j < 0)
        {
            delete[] bmBc;
            delete[] bmGs;
            return i;
        }
        else
        {
            i += std::max(bmBc[strText[i + j]] - nPatternLen + 1 + j, bmGs[j]);
        }
    }
    delete[] bmBc;
    delete[] bmGs;
    return -1;
}

// Get the bad character array for BM algorithm.
void g_GetBMBc(const std::string& strPattern, int* bmBc)
{
    int nPatternLen = strPattern.length();
    for (int i = 0; i < 256; i++)
    {
        bmBc[i] = nPatternLen;
    }
    for (int i = 0; i < nPatternLen - 1; i++)
    {
        bmBc[strPattern[i]] = nPatternLen - i - 1;
    }
}

// Get the good suffix array for BM algorithm.
void g_GetBMGs(const std::string& strPattern, int* bmGs)
{
    int i = 0;
    int j = 0;
    int nPatternLen = strPattern.length();
    int* suffix = new int[nPatternLen];
    suffix[nPatternLen - 1] = nPatternLen;
    for (i = nPatternLen - 2; i >= 0; i--)
    {
        j = i;
        while (j >= 0 && strPattern[j] == strPattern[nPatternLen - 1 - i + j])
        {
            j--;
        }
        suffix[i] = i - j;
    }
    for (i = 0; i < nPatternLen - 1; i++)
    {
        bmGs[i] = nPatternLen;
    }
    for (i = nPatternLen - 1; i >= 0; i--)
    {
        if (suffix[i] == i + 1)
        {
            for (j = 0; j < nPatternLen - 1 - i; j++)
            {
                if (bmGs[j] == nPatternLen)
                {
                    bmGs[j] = nPatternLen - 1 - i;
                }
            }
        }
    }
    for (i = 0; i <= nPatternLen - 2; i++)
    {
        bmGs[nPatternLen - 1 - suffix[i]] = nPatternLen - 1 - i;
    }
    delete[] suffix;
}

int main()
{
    std::string strText = "ababababca";
    std::string strPattern = "abababca";
    std::cout << g_BruteForce(strText, strPattern) << std::endl;
    std::cout << g_KMP(strText, strPattern) << std::endl;
    std::cout << g_BM(strText, strPattern) << std::endl;
    return 0;
}