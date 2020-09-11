//https://codeforces.com/contest/1279/problem/E

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 100;
long long fact[MAXN];
long long dp[MAXN][MAXN];
long long tot[MAXN];
long long ans[MAXN];
bool blocked[MAXN];
long long add(long long x,long long y){
    x+=y;
    if(x>(1e18+5)){
        return 1e18+5;
    }
    return x;
}
long long mult(long long x,long long y){
    if(x<=(long long)(1e18+5)/y){
        return 1LL*x*y;
    }
    return 1e18+5;
}
long long calcfact(long long x){
    if(x-2<0){
        return 1;
    }
    return fact[x-2];
}
int main() {
    long long t;
    cin>>t;
    fact[0] = 1;
    for(long long i=1;i<=50;i++){
        fact[i] = mult(fact[i-1],i);
    }
    while(t--){
        long long n,k;
        cin>>n>>k;
        for(long long i=1;i<=50;i++){
            ans[i] = 0;
            for(long long j=1;j<=50;j++){
                dp[i][j] = 0;
                tot[i] = 0;
            }
        }
        tot[n+1] = 1;
        for(long long i=n;i>=1;i--){
            blocked[i] = false;
            for(long long j=i;j<=n;j++){
                if(j-i-1>=0){
                    dp[i][j] = mult(tot[j+1],fact[(j-i-1)]);
                }else{
                    dp[i][j] = tot[j+1];
                }
                tot[i] = add(tot[i],dp[i][j]);
            }
            
        }
       
        if(tot[1]<k){
            cout<<-1<<endl;
            continue;
        }
       
        for(long long i=1;i<=n;i++){
            long long len = 1;
            if(tot[i+len]<k){
                k-=tot[i+len];
                len++;
            }
            
            while(len-2>=0 && mult(fact[len-2],tot[i+len])<k){
                k-=mult(fact[len-2],tot[i+len]);
                len++;
                
            }
            ans[i] = i+len-1;
            blocked[i+len-1] = true;
            for(long long j=i+1;j<=i+len-1;j++){
                
                long long v= i;
                while(true){
                    
                    if(blocked[v]){
                        //already assigned v
                        v++;
                        continue;
                    }
                    
                    if(j == i+len-1){
                        //only one possible value to assign
                        break;
                    }
                    long long t=v;
                    while(ans[t]){
                        //if it forms a cycle, can't assign v
                        t = ans[t];
                    }
                    if(t==j){
                        v++;
                        continue;
                    }
                    if(k>mult(tot[i+len],calcfact(len-(j-i)))){
                        //if we assign v, the number of possible permutations with p_j = v set is less than k, so p_j>v
                        k-=mult(tot[i+len],calcfact(len-(j-i)));
                        v++;
                        continue;
                    }
                    break;
                }
                blocked[v] = true;
                ans[j] = v;
               
            }
            i+=len;
            i--;
        }
        for(long long i=1;i<=n;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
}
