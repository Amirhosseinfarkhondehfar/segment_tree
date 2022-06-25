#include <bits/stdc++.h>
using namespace std;
long long inf = 1e12;
struct node
{
    long long m, l, r, p;
    node(){
        m=0;
    }
};

struct nodea{
    long long m, l, r, p;
    nodea(){
        m=inf;
    }
};

vector<vector<node>> sega;
vector<vector<nodea>>seg;
long long n, q;
pair<long long, long long> solve(long long i, long long j, long long l, long long r)
{
    if (seg[i][j].l >= l && seg[i][j].r <= r)
    {
        return {seg[i][j].m, seg[i][j].p};
    }
    if (seg[i][j].l > r || seg[i][j].r < l)
    {
        return {inf, 0};
    }
    pair<long long , long long> a = solve(i + 1, j * 2 + 1, l, r), b = solve(i + 1, j * 2, l, r);
    if (a.first < b.first)
    {
        return a;
    }
    else
    {
        return b;
    }
}

pair<long long, long long> solve2(long long i, long long j, long long l, long long r)
{
    if (sega[i][j].l >= l && sega[i][j].r <= r)
    {
        return {sega[i][j].m, sega[i][j].p};
    }
    if (sega[i][j].l > r || sega[i][j].r < l)
    {
        return {0, 0};
    }
    pair<long long, long long> a = solve2(i + 1, j * 2 + 1, l, r), b = solve2(i + 1, j * 2, l, r);
    if (a.first > b.first)
    {
        return a;
    }
    else
    {
        return b;
    }
}

nodea build(long long i, long long j)
{
    // cout<<i<<" "<<j<<endl;
    if (i == seg.size() - 1)
    {
        return seg[i][j];
    }
    nodea ghably = build(i + 1, j * 2), bady = build(i + 1, j * 2+1);
    seg[i][j].l = min(ghably.l, bady.l);
    seg[i][j].r = max(ghably.r, bady.r);
    if (ghably.m < bady.m)
    {
        seg[i][j].m = ghably.m;
        seg[i][j].p = ghably.p;
    }
    else
    {
        seg[i][j].m = bady.m;
        seg[i][j].p = bady.p;
    }
    return seg[i][j];
}

node build2(long long i, long long j)
{
    if (i == sega.size() - 1)
    {
        return sega[i][j];
    }
    node ghably = build2(i + 1, j * 2), bady = build2(i + 1, j * 2 + 1);
    sega[i][j].l = min(ghably.l, bady.l);
    sega[i][j].r = max(ghably.r, bady.r);
    if (ghably.m > bady.m)
    {
        sega[i][j].m = ghably.m;
        sega[i][j].p = ghably.p;
    }
    else
    {
        sega[i][j].m = bady.m;
        sega[i][j].p = bady.p;
    }
    return sega[i][j];
}

long long mainsolve(long long j,long long i){
    if(i==j){
        return 0;
    }
    bool f=0;
    long long result=1;
    while(j!=0){
        result++;
        if(f==0){
            j=solve(0,0,0,j).second;
            f=1;
        }
        else{
            j=solve2(0,0,0,j).second;
            f=0;
        }
    }
    f=1;
    while(i!=n-1){
        result++;
        if(f==0){
            i=solve(0,0,i,n-1).second;
            f=1;
        }
        else{
            i=solve2(0,0,i,n-1).second;
            f=0;
        }
    }
    return result;
}

long long mainsolve2(long long j,long long i){
    if(i==j){
        return 0;
    }
    bool f=1;
    long long result=1;
    while(j!=0){
        result++;
        if(f==0){
            j=solve(0,0,0,j).second;
            f=1;
        }
        else{
            j=solve2(0,0,0,j).second;
            f=0;
        }
    }
    f=0;
    while(i!=n-1){
        result++;
        if(f==0){
            i=solve(0,0,i,n-1).second;
            f=1;
        }
        else{
            i=solve2(0,0,i,n-1).second;
            f=0;
        }
    }
    return result;
}

int main()
{
    long long t;
    cin >> t;
    for (long long i = 0; i < t; i++)
    {
        seg.clear();
        sega.clear();
        cin >> n;
        vector<long long> all(n), alla(n);
        long long fn=n;
        for (long long i = 0; i < n; i++)
        {
            cin >> all[i];
            alla[i] = all[i];
        }
        while (__builtin_popcount(n) != 1)
        {
            n++;
            all.push_back(inf);
            alla.push_back(0);
        }
        long long ml = 1, sz = 1;
        while (ml <= n)
        {
            ml *= 2;
            sz++;
        }
        seg.resize(sz);
        sega.resize(sz);
        for (long long i = 0; i < sz; i++)
        {
            node n;
            nodea nn;
            vector<nodea>ita((1<<i)+1,nn);
            vector<node> it((1 << i) + 1, n);
            seg[i] = ita;
            sega[i] = it;
        }
        for (long long i = 0; i < n; i++)
        {
            seg[sz - 1][i].m = all[i];
            seg[sz - 1][i].l = i;
            seg[sz - 1][i].r = i;
            seg[sz - 1][i].p = i;
            sega[sz - 1][i].m = alla[i];
            sega[sz - 1][i].l = i;
            sega[sz - 1][i].r = i;
            sega[sz - 1][i].p = i;
        }
        n=fn;
        build(0, 0);
        build2(0, 0);
        long long result = 0;
        pair<long long , long long>mina,maxa;
        mina=solve(0,0,0,n-1),maxa=solve2(0,0,0,n-1);
        if(mina.second<maxa.second){
            result=mainsolve2(mina.second,maxa.second);
        }
        else{
            result=mainsolve(maxa.second,mina.second);
        }
        cout<<result<<endl;
    }
} 
