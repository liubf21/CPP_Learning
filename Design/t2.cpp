#include<bits/stdc++.h>

using namespace std;

string add_long(string a, string b)
{
    string ret;
    if(a[0]=='-'&&b[0]=='-')
    {
        auto ai=a.rbegin();
        auto bi=b.rbegin();
        bool ad=false;
        while(ai!=a.rend()-1&&bi!=b.rend()-1)
        {
            if(*ai+*bi-'0'-'0'>=10)
            {
                ret+=*ai+*bi-'0'-10;
                if(ad)ret.back()+=1;
                ad=true;
            }else{
                ret.back()+=*ai+*bi-'0';
                if(ad)ret.back()+=1;
                ad=false;
            }
            ai++;
            bi++;
        }
        while(ai!=a.rend()-1)
        {
            ret+=*ai;
            if(ad)ret.back()+=1;
            ad=false;
            ai++;
        }
        while(bi!=b.rend()-1)
        {
            ret+=*bi;
            if(ad)ret.back()+=1;
            ad=false;
            bi++;
        }
        if(ad)ret+='1';
        ret+='-';
    }else if(a[0]=='-')
    {
        auto ai=a.rbegin();
        auto bi=b.rbegin();
        bool ad=false;
        while(ai!=a.rend()-1&&bi!=b.rend()-1)
        {
            if(*ai+*bi-'0'-'0'>=10)
            {
                ret+=*ai+*bi-'0'-10;
                if(ad)ret.back()+=1;
                ad=true;
            }else{
                ret.back()+=*ai+*bi-'0';
                if(ad)ret.back()+=1;
                ad=false;
            }
            ai++;
            bi++;
        }
        while(ai!=a.rend()-1)
        {
            ret+=*ai;
            if(ad)ret.back()+=1;
            ad=false;
            ai++;
        }
        while(bi!=b.rend()-1)
        {
            ret+=*bi;
            if(ad)ret.back()+=1;
            ad=false;
            bi++;
        }
        if(ad)ret+='1';
        ret+='-';
    }else if(b[0]=='-')
    {

    }else{
        auto ai=a.rbegin();
        auto bi=b.rbegin();
        bool ad=false;
        cout<<"+"<<endl;
        while(ai!=a.rend()&&bi!=b.rend())
        {
            // cout<<ret<<endl;
            if(*ai+*bi-'0'-'0'>=10)
            {
                ret+=*ai+*bi-'0'-10;
                if(ad)*(ret.end()-1)+=1;
                ad=true;
            }else{
                ret+=*ai+*bi-'0';
                if(ad)*(ret.end()-1)+=1;
                ad=false;
            }
            ai++;
            bi++;
        }
        while(ai!=a.rend())
        {
            ret+=*ai;
            if(ad)ret.back()+=1;
            ad=false;
            ai++;
        }
        while(bi!=b.rend())
        {
            ret+=*bi;
            if(ad)ret.back()+=1;
            ad=false;
            bi++;
        }
        if(ad)ret+='1';
    }
    // 翻转
    string ans;
    for(auto i=ret.rbegin();i!=ret.rend();i++)
    {
        ans+=*i;
    }
    return ans;
}


int main()
{
    string a("123"),b("123");
    cout<<a<<"+"<<b<<endl;
    string ans=add_long(a,b);
    cout<<ans<<endl;
    return 0;
}