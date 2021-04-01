#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 1e6+5;
map<long long,long long> compress;
const long long MOD = 998244353;
struct s{
    long long sum;long long lazyadd;long long lazymul;long long len;
};
s seg[4*MAXN];
long long arr[MAXN];
long long arr2[MAXN];
void push(long long curr){
    seg[2*curr].sum = (1LL*seg[2*curr].sum*seg[curr].lazymul) + (1LL*seg[curr].lazyadd*seg[2*curr].len);
    seg[2*curr].sum%=MOD;
    seg[2*curr+1].sum = (1LL*seg[2*curr+1].sum*seg[curr].lazymul) + (1LL*seg[curr].lazyadd*seg[2*curr+1].len);
    seg[2*curr+1].sum%=MOD;
    
   
    seg[curr*2].lazymul=(1ll*seg[curr*2].lazymul*seg[curr].lazymul)%MOD;
    seg[curr*2+1].lazymul=(1ll*seg[curr*2+1].lazymul*seg[curr].lazymul)%MOD;
    
    seg[curr*2].lazyadd=(1ll*seg[curr].lazymul*seg[2*curr].lazyadd+seg[curr].lazyadd)%MOD;
    seg[curr*2 + 1].lazyadd=(1ll*seg[curr].lazymul*seg[2*curr+1].lazyadd+seg[curr].lazyadd)%MOD;
    seg[curr].lazyadd = 0;
    seg[curr].lazymul = 1;
}
void build(long long curr,long long l,long long r){
    seg[curr].lazymul= 1;
    if(l==r){
        seg[curr].len = arr2[l]-arr2[l-1];
        seg[curr].len%=MOD;
        //cout<<seg[curr].len<<endl;
        return;
    }
    long long mid = (l+r)/2;
    build(2*curr,l,mid);
    build(2*curr+1,mid+1,r);
    seg[curr].len = (seg[2*curr].len + seg[2*curr+1].len)%MOD;
    seg[curr].sum = (seg[2*curr].sum + seg[2*curr+1].sum)%MOD;

}
void add(long long curr,long long l,long long r,long long tl,long long tr,long long val){
    if(l>tr||r<tl){
        return;
    }
    
    if(l>=tl && r<=tr){
        
        seg[curr].lazyadd = (seg[curr].lazyadd+val)%MOD;
        seg[curr].sum = (seg[curr].sum + 1LL*seg[curr].len*val)%MOD;
        
        return;
    }
    push(curr);
    long long mid = (l+r)/2;
    if(mid>=tl){
        add(2*curr,l,mid,tl,tr,val);
    }
    if(mid<tr){
        add(2*curr+1,mid+1,r,tl,tr,val);
    }
    
    
    
    seg[curr].len = (seg[2*curr].len + seg[2*curr+1].len)%MOD;
    seg[curr].sum = (seg[2*curr].sum + seg[2*curr+1].sum)%MOD;
    
}
void mul(long long curr,long long l,long long r,long long tl,long long tr,long long val){
    if(l>tr||r<tl){
        return;
    }
    push(curr);
    if(l>=tl && r<=tr){
        seg[curr].lazyadd=(1ll*seg[curr].lazyadd*val)%MOD;
        seg[curr].lazymul=(1ll*seg[curr].lazymul*val)%MOD;
        seg[curr].sum=(1ll*seg[curr].sum*val)%MOD;
        return ;
    }
    
    long long mid=(l+r)/2;
    mul(2*curr,l,mid,tl,tr,val);
    mul(2*curr+1,mid+1,r,tl,tr,val);
    
    seg[curr].len = (seg[2*curr].len + seg[2*curr+1].len)%MOD;
    seg[curr].sum = (seg[2*curr].sum + seg[2*curr+1].sum)%MOD;
}
long long query(long long curr,long long l,long long r,long long tl,long long tr){
    if(l>tr||r<tl){
        return 0;
    }
    push(curr);
    if(l>=tl && r<=tr){
        
        return seg[curr].sum;
        
    }
  
    
    long long mid=(l+r)/2;
    
    long long q1= query(2*curr,l,mid,tl,tr);
    long long q2 = query(2*curr+1,mid+1,r,tl,tr);
   
    seg[curr].len = (seg[2*curr].len + seg[2*curr+1].len)%MOD;
    seg[curr].sum = (seg[2*curr].sum + seg[2*curr+1].sum)%MOD;
    
    return (q1+q2)%MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    cin>>n;
    for(long long i=1;i<=n;i++){
        cin>>arr[i];
        arr2[i] = arr[i];
    }
    
    sort(arr2+1,arr2+n+1);
    long long cnt = 1;
    for(long long i=1;i<=n;i++){
        if(!compress[arr2[i]]){
            compress[arr2[i]] = cnt;
            cnt++;
        }
    }
    
    cnt--;
    for(long long i=1;i<=n;i++){
        arr[i] = compress[arr[i]];
        
    }
    long long ind = 1;
    for(long long i=1;i<=n;i++){
        if(arr2[i] == arr2[i-1]){
            continue;
        }
        arr2[ind] = arr2[i];
        ind++;
    }
    build(1,1,cnt);
    
    add(1,1,cnt,1,arr[1],1);
    
    for(long long i=2;i<=n;i++){
        long long tot = seg[1].sum;
      //  cout<<tot<<" "<<arr[i]<<" "<<cnt<<endl;
        if(arr[i]<cnt){
            mul(1,1,cnt,arr[i]+1,cnt,0);
        }
        mul(1,1,cnt,1,arr[i],-1+MOD);
        add(1,1,cnt,1,arr[i],tot);
        
    }
    long long res = 0;
    for(long long i=1;i<=cnt;i++){
        res+=query(1,1,cnt,i,i);
        res%=MOD;
    }
    cout<<res<<"\n"<<endl;
}
