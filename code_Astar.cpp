#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int a[1001][1001],x,y,n,m;
int x_step[4]= {-1,0,1,0}, y_step[4]= {0,1,0,-1};
int h(int a,int b) {
	return abs(a-x)+abs(b-y);
}
struct node {
	int x,y,val;
	bool operator<(node a) const {
		return val+h(x,y)>a.val+h(a.x,a.y);
	}
}
block;
priority_queue<node>q;
void Astar() {
	node st;
	cin>>st.x>>st.y;
	q.push(st);
	while(!q.empty()) {
		node now=q.top();
		q.pop();
		if(!h(now.x,now.y)) {
			printf("%d",now.val);
			return;
		}
		for (int i=0;i<4;++i) {
			node nxt;
			nxt.x=now.x+x_step[i];
			nxt.y=now.y+y_step[i];
			if(!a[nxt.x][nxt.y])continue;
			nxt.val=now.val+1;
			q.push(nxt);
		}
	}
	printf("No Solution");
}
void read() {
	cin>>n>>m;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
		cin>>a[i][j];
	cin>>x>>y;
}
int main() {
	int t=GetTickCount();
	read();
	Astar();
	int dt=GetTickCount()-t;
	cout<<endl<<dt;
	return 0;
}
