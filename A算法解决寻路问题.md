# A*算法解决寻路问题

## 1.问题引入

​		对于当前点到目标点的最优路径选择，常使用 A\*（启发式搜索）算法解决。

​		从游戏中npc的移动，到人工智能对问题的处理，以及自动化设备路径选择，都可用到 A* 算法。

​		现使用A\*算法解决机器人走迷宫问题。

## 2.模型建立

​		设迷宫为一个$N*M$的矩形。

​		矩形上每个格子有0和1两种状态，0代表不可通行，1代表可通行。

​		机器人起始位置在点$(a,b)$，目标位置在点$(c,d)$。

​		机器人只能向上，下，左，右移动。

​		求最优路径。

## 3.算法介绍

​		A\*算法，是一种在图形平面上，对于有多个节点的路径求出最低通过成本的算法。

### 3.1.$Dijkstra$的缺点

<img src="http://theory.stanford.edu/~amitp/game-programming/a-star/dijkstra-trap.png?2017-11-17-16-52-52" alt="img" style="zoom: 67%;" />

​		$Dijkstra$	算法，能保证得出最优解。

​		但$Dijkstra$算法没有明确的方向性，

​		因此在找最短路时时间花费过多。

### 3.2.BFS的缺点

<img src="http://theory.stanford.edu/~amitp/game-programming/a-star/best-first-search-trap.png?2017-11-17-16-52-06" alt="img" style="zoom:67%;" />

​		相比于$Dijstra$,BFS的优点在于它贪心的寻找离目标点距离最近的位置。

​		但当面对如图的凹形“陷阱”时，BFS的缺陷就会体现出来。

​		BFS在搜索时只考虑目标距离，不考虑已走距离。

​		不能做到较为智能的选路。

### 3.3.A*算法

<img src="http://theory.stanford.edu/~amitp/game-programming/a-star/a-star-trap.png?2017-11-17-16-51-38" alt="img" style="zoom:67%;" />

​		此时A*算法的好处便体现出来。

​		A*算法结合了$Dijkstra$算法和BFS算法的优点，

​		即同时考虑了接近起点的距离和接近终点的距离。

​		在A\*算法中，我们设计一个函数$h(x)$表示对目标路径的估计值，

​		$g(x)	$表示从起点到当前位置的实际值。

​		因此在每个点上，有估价函数$f(x)=g(x)+h(x)$,

​		在每次操作时，我们取出$f(x)$最小的一点，并更新与之相关的状态。

​		第一次取出终点时的答案即为最优解

### 3.3.关于$h(x)$函数的设计

- 当$h(x)=0$时，此时只考虑到起点距离，等价于优先队列优化的BFS

- 当$h(x)<=h'(x)$时，此时A*算法能保证找到**最短路**，且$h(x)$的值越接近$h'(x)$，算法效率越高

- 当$h(x)>h'(x)$时，此时将**不能**保证最优解,但算法的效率会进一步提高。

  在信息学竞赛中，我们一般选择不大于实际值的估价函数$h(x)$,

  但在实际应用中，可以使用大于实际值的函数以找到较优解。

  这个问题中，我们将$h(x)$设为两点间**曼哈顿距离**，即
  $$
  h(x)=(abs(x-goal.x)+abs(y-goal.y))
  $$
  

  显然，$h(x)$满足不大于实际距离的条件

## 4.代码实现

​		

```c++
#include<bits/stdc++.h>
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
} block;

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
	read();
	Astar();
	return 0;
}
```

​	

## 5.代码分析

经过测试,代码在类似如下数据中运行速度明显快于普通最短路算法

```
5 5
1 0 0 0 1
1 1 1 0 1
1 1 1 0 1
1 0 0 0 1
1 1 1 1 1
1 5
1 1
```

​		考虑实际应用问题，将机器人行走路程中障碍转化为坐标表示

​		能在1s内处理$n*m=1e6$左右的数据

​		同时算法时间复杂度稳定性较强

​		适合用于实际应用中

##6.实际应用的设想与计划
		
​		

