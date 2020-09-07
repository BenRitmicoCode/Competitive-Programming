#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
int lazy[4*MAXN];
int seg[4*MAXN];
void push(int curr,int l,int r){
    if(lazy[curr]){
        if(l!=r){
            lazy[2*curr]+=lazy[curr];
            lazy[2*curr+1]+=lazy[curr];
            seg[2*curr]+=lazy[curr];
            seg[2*curr+1]+=lazy[curr];
        }
        lazy[curr] = 0;
    }
}
void build(int curr,int l,int r){
    if(l==r){
        seg[curr] = 0;
        lazy[curr] = 0;
        return;
    }
    int mid = (l+r)/2;
    build(2*curr,l,mid);
    build(2*curr+1,mid+1,r);
    seg[curr] = max(seg[2*curr],seg[2*curr+1]);
}
int findpos(int curr,int l,int r,int val){
    if(lazy[curr]){
        push(curr,l,r);
    }
    if(l==r){
        return l;
    }
    int mid = (l+r)/2;
    push(2*curr,l,mid);
    push(2*curr+1,mid+1,r);
    seg[curr] = max(seg[2*curr],seg[2*curr+1]);
    if(seg[2*curr+1]>=val){
        return findpos(2*curr+1,mid+1,r,val);
    }else{
        return findpos(2*curr,l,mid,val);
    }
}
void update(int curr,int l,int r,int tl,int tr){
    if(lazy[curr]){
        push(curr,l,r);
    }
    
    if(l>tr||r<tl){
        return;
    }
    if(tl<=l && r<=tr){
        seg[curr]++;
        lazy[curr]++;
        return;
    }
    int mid =(l+r)/2;
    update(2*curr,l,mid,tl,tr);
    update(2*curr+1,mid+1,r,tl,tr);
    seg[curr] = max(seg[2*curr],seg[2*curr+1]);
}
int query(int curr,int l,int r,int tl,int tr){
    if(lazy[curr]){
        push(curr,l,r);
    }
    
    if(l>tr||r<tl){
        return -1e9;
    }
    if(tl<=l && r<=tr){
        return seg[curr];
    }
    int mid =(l+r)/2;
    int q1= query(2*curr,l,mid,tl,tr);
    int q2 = query(2*curr+1,mid+1,r,tl,tr);
    seg[curr] =max(seg[2*curr],seg[2*curr+1]);
    return max(q1,q2);
}
int valat(int curr,int l,int r,int pos){
    if(lazy[curr]){
        push(curr,l,r);
    }
    if(l==r){
        return seg[curr];
    }
    int mid = (l+r)/2;
    if(pos<=mid){
        return valat(2*curr,l,mid,pos);
    }else{
        return valat(2*curr+1,mid+1,r,pos);
    }
}
