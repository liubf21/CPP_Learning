// ABCDCD -> ABCD
#include<bits/stdc++.h>

using namespace std;

int dp[100]; // dp[i] 存以第i位为结尾的 最长无重复子串


int main()
{
    string s = "ABCDCD";
    dp[0]=1;

    for(int i=1;i<s.size();i++)
    {
        bool add=true;
        for(int j=1;j<=dp[i-1];j++) // i-1 not i
        {
            if(s[i]==s[i-j])
            {
                add=false;
                dp[i]=j;
                break;
            }
        }
        if(add)dp[i]=dp[i-1]+1;
    }
    int ans=0;
    for(int i=0;i<s.size();i++)
    {
        cout<<dp[i]<<endl;
        ans=max(ans, dp[i]);
    }
    cout<<"ans:"<<ans<<endl;

    return 0;
}