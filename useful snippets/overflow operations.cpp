#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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

int main(){
  
}
