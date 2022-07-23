#include<bits/stdc++.h>
using namespace std;
long long n,d;
struct node{
	long long sum,powtwo,adda,l,r,counta;
	node(){
		sum=0;
		powtwo=0;
		adda=0;
		counta=0;
	}
};
vector<vector<node>>seg;
vector<bool>vis;

void build(long long i,long long j){
	if(i==seg.size()-1){
		return ;
	}
	build(i+1,j*2);
	build(i+1,j*2-1);
	node ghably=seg[i+1][j*2-1],bady=seg[i+1][j*2];
	seg[i][j].r=max(ghably.r,bady.r);
	seg[i][j].l=min(ghably.l,bady.l);
}

void update(long long i,long long j){
	if(i==0){
		return ;
	}
	if(i!=seg.size()-1){
		seg[i][j].sum=seg[i+1][j*2].sum+seg[i+1][j*2-1].sum;
		seg[i][j].powtwo=seg[i+1][j*2].powtwo+seg[i+1][j*2-1].powtwo;
		seg[i][j].counta=seg[i+1][j*2].counta+seg[i+1][j*2-1].counta;
		seg[i][j].powtwo+=2ll*seg[i][j].adda*seg[i][j].sum+(seg[i][j].adda*seg[i][j].adda*seg[i][j].counta);
		seg[i][j].sum+=seg[i][j].counta*seg[i][j].adda;
	}
	update(i-1,(j+1)/2);
}

void solve(long long i,long long j,long long lh,long long rh,long long k){
	//cout<<i<<" "<<j<<" "<<seg[i][j].l<<" "<<seg[i][j].r<<" "<<lh<<" "<<rh<<endl;
	if(seg[i][j].r<lh||seg[i][j].l>rh){
		return;
	}
	if(seg[i][j].l>=lh&&seg[i][j].r<=rh){
		seg[i][j].adda+=k;
		seg[i][j].powtwo+=2ll*k*seg[i][j].sum+(k*k*seg[i][j].counta);
		seg[i][j].sum+=seg[i][j].counta*k;
		return ;
	}
	solve(i+1,j*2-1,lh,rh,k);
	solve(i+1,j*2,lh,rh,k);
	seg[i][j].sum=seg[i+1][j*2].sum+seg[i+1][j*2-1].sum;
	seg[i][j].powtwo=seg[i+1][j*2].powtwo+seg[i+1][j*2-1].powtwo;
	seg[i][j].counta=seg[i+1][j*2].counta+seg[i+1][j*2-1].counta;
	seg[i][j].powtwo+=2ll*seg[i][j].adda*seg[i][j].sum+(seg[i][j].adda*seg[i][j].adda*seg[i][j].counta);
	seg[i][j].sum+=seg[i][j].counta*seg[i][j].adda;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>d;
	vis.resize(1e6);
	seg.resize(22);
	for(long long i=0;i<seg.size();i++){
		vector<node>all(1ll<<i);
		seg[i]=all;
	}
	for(long long i=0;i<seg[seg.size()-1].size();i++){
		seg[seg.size()-1][i].l=seg[seg.size()-1][i].r=i;
	}
	build(1,1);
	for(long long i=0;i<n;i++){
		long long u;
		cin>>u;
		if(vis[u]){
			seg[seg.size()-1][u].powtwo=seg[seg.size()-1][u].sum=seg[seg.size()-1][u].counta=0;
			update(seg.size()-1,u);
			vis[u]=0;
			if(u==1){
				
			}
			else{
			solve(1,1,max(1ll,u-d),max(u-1,1ll),-1);
			}
		}
		else{
			seg[seg.size()-1][u].powtwo=seg[seg.size()-1][u].adda*seg[seg.size()-1][u].adda;
			seg[seg.size()-1][u].sum=seg[seg.size()-1][u].adda;
			seg[seg.size()-1][u].counta=1;
			update(seg.size()-1,u);
			vis[u]=1;
			if(u==1){
				
			}
			else{
			solve(1,1,max(1ll,u-d),max(u-1,1ll),+1);
	       // cout<<seg[seg.size()-1].size()<<endl;
		    }
		}
		long long res=seg[1][1].powtwo-seg[1][1].sum;
		res/=2;
		cout<<res<<endl;
	}
}
