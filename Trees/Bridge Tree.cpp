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
pair<int,int> edges[MAXN];
int cmpnum[MAXN];
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

void dfs2(int curr,int cmp){
    cmpnum[curr] = cmp;
    for(auto x:v1[curr]){
        int y = x.first;
        int ind = x.second;
        if(!is_bridge[ind] && !cmpnum[y]){
            dfs2(y,cmp);
        }
        
    }
}
void buildtree(){
    int tmp = 0;
    for(int i=1;i<=n;i++){
        if(!cmpnum[i]){
            tmp++;
            dfs2(i,tmp);
            
        }
    }
    for(int i=1;i<=m;i++){
        if(is_bridge[i]){
            v2[cmpnum[edges[i].first]].push_back(make_pair(cmpnum[edges[i].second],i));
            v2[cmpnum[edges[i].second]].push_back(make_pair(cmpnum[edges[i].first],i));
        }
    }
}
int main(){
    
}
