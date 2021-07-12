#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const long long MOD = 998244353;
long long fact[MAXN];

long long modpow(long long a, long long b){
	long long ans = 1;
	while (b > 0){
		if (b % 2 == 1){
			ans *= a;
			ans %= MOD;
		}
		a *= a;
		a %= MOD;
		b /= 2;
	}
	return ans;
}
long long modinv(long long a){
	return modpow(a, MOD - 2);
}
int main() {
      fact[0] = 1;
      for(int i=1;i<=2*n;i++){
          fact[i] = 1LL*fact[i-1]*i;
          fact[i]%=MOD;
      }
      cout<<(1LL*((1LL*fact[n]*modinv(fact[r]))%MOD)*modinv(fact[n-r]))%MOD<<endl;
}
