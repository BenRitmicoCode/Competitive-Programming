#include <iostream>

using namespace std;
long long gcd(long long a, long long b){
    if (a < b){
        return gcd(b, a);
    }
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}
long long extgcd(long long a, long long b, long long &x, long long &y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    long long d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long mod_inv(long long a, long long p){
    if (gcd(a, p) != 1){
        return -1;
    }
 
    long long x, y;
    extgcd(a, p, x, y);
 
    x %= p;
    if (x < 0){
        x += p;
    }
    return x;
}
int main() {
    
}
