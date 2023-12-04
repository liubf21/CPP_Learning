// Purpose: Source file for string matching algorithms.
#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include <cstring>

// Brute force string matching algorithm.
std::vector < int >
g_BruteForce (const std::string & strText, const std::string & strPattern)
{
  std::vector < int >ans;
  int i = 0;
  int j = 0;
  int nTextLen = strText.length ();
  int nPatternLen = strPattern.length ();
  while (i < nTextLen)
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
      if (j == nPatternLen)
        {
          ans.push_back (i - j);
        }
    }

  return ans;
}

// KMP string matching algorithm.
void g_GetNext (const std::string & strPattern, int *next);
std::vector < int >
g_KMP (const std::string & strText, const std::string & strPattern)
{
  std::vector < int >ans;
  int i = 0;
  int j = 0;
  int nTextLen = strText.length ();
  int nPatternLen = strPattern.length ();
  int *next = new int[nPatternLen];
  g_GetNext (strPattern, next);

//   std::cout << "next:";
//   for(int i=0;i<nPatternLen;i++)std::cout << next[i] << " ";
//   std::cout << std::endl;

  while (i < nTextLen)
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
      if (j == nPatternLen)
        {
          ans.push_back (i - j);
        //   std::cout << ":" << ans.back() << "i" << i << "j" << j << " ";
          i += -nPatternLen + std::max(next[j-1], 1);
          j = 0;
        }
    }
  delete[]next;
  return ans;
}

// Get the next array for KMP algorithm.
void
g_GetNext (const std::string & strPattern, int *next)
{
  int i = 0;
  int j = -1;
  int nPatternLen = strPattern.length ();
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
void g_GetBMBc (const std::string & strPattern, int *bmBc);
void g_GetBMGs (const std::string & strPattern, int *bmGs);
std::vector <int>
g_BM (const std::string & strText, const std::string & strPattern)
{
std::vector<int> ans;
  int i = 0;
  int j = 0;
  int nTextLen = strText.length ();
  int nPatternLen = strPattern.length ();
  int *bmBc = new int[256];
  int *bmGs = new int[nPatternLen];
  g_GetBMBc (strPattern, bmBc);
  g_GetBMGs (strPattern, bmGs);
  while (i <= nTextLen - nPatternLen)
    {
      for (j = nPatternLen - 1; j >= 0 && strText[i + j] == strPattern[j];
           j--);
      if (j < 0)
        {
          ans.push_back(i);
          i++;
        }
      else
        {
          i += std::max (bmBc[strText[i + j]] - nPatternLen + 1 + j, bmGs[j]);
        }
    }
  delete[]bmBc;
  delete[]bmGs;
  return ans;
}

// Get the bad character array for BM algorithm.
void
g_GetBMBc (const std::string & strPattern, int *bmBc)
{
  int nPatternLen = strPattern.length ();
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
void
g_GetBMGs (const std::string & strPattern, int *bmGs)
{
  int i = 0;
  int j = 0;
  int nPatternLen = strPattern.length ();
  int *suffix = new int[nPatternLen];
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
  delete[]suffix;
}

// Read the file.
std::string
g_ReadFile (const std::string & strFileName)
{
  std::ifstream fin (strFileName.c_str ());
  std::string strText;
  std::string strLine;
  while (getline (fin, strLine))
    {
      strText += strLine;
    }
  return strText;
}

int
main (int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: " << "algorithm file pattern" << std::endl;
        std::cout << "algorithm: BF, KMP, BM" << std::endl;
        return 0;
    }
    std::string algorithm = argv[1];
    std::string strPattern = argv[3];
    std::string strText = g_ReadFile (argv[2]);

  std::vector < int >ans;
    // if (algorithm == "BF")
    // {
    //     ans = g_BruteForce (strText, strPattern);
    // }
    // else if (algorithm == "KMP")
    // {
    //     ans = g_KMP (strText, strPattern);
    // }
    // else if (algorithm == "BM")
    // {
    //     ans = g_BM (strText, strPattern);
    // }
    // else
    // {
    //     std::cout << "Unknown algorithm: " << algorithm << std::endl;
    //     return 0;
    // }

  ans = g_BruteForce (strText, strPattern);
for (const auto & i:ans)
    std::cout << i << " ";
  std::cout << std::endl;

  ans = g_KMP (strText, strPattern);
for (const auto & i:ans)
    std::cout << i << " ";
  std::cout << std::endl;

  ans = g_BM (strText, strPattern);
for (const auto & i:ans)
    std::cout << i << " ";
  std::cout << std::endl;
  return 0;
}
