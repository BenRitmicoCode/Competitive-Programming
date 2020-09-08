#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
int timer;
int tin[MAXN];
bool visited[MAXN];
int low[MAXN];
vector<pair<int,int>> v1[MAXN];
bool is_bridge[MAXN];
void dfs1(int curr,int par){
    timer++;
    tin[curr] = timer;
    visited[curr] = true;
    low[curr] = timer;
    for(auto x:v1[curr]){
        int y = x.first;
        int ind = x.second;
        if(y == par){
            continue;
        }
        if(visited[y]){
            low[curr] = min(low[curr],tin[y]);
        }else{
            dfs1(y,curr);
            low[curr] = min(low[curr],low[y]);
            if(low[y]>tin[curr]){
                is_bridge[ind] = true;
            }
        }
    }
}
int main(){
    
}
