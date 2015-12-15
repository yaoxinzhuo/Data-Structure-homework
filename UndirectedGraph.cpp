#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
const int MAX=26;//节点数目为n-1 
using namespace std;
//无向图

class Node
{
public:
	int point;
	Node* nextNode;
	Node()
	{
		nextNode=NULL;
	} 
}; 

class Graph
{
public:
	Node *Nodes[MAX];//定义指针数组，从1开始为对应节点所相关联的边
	bool DFSvisited[MAX];
	bool BFSvisited[MAX];
	int BFSdepth[MAX];
	int DFSdepth[MAX];
	
	Graph()
	{
		for(int i=0;i<(MAX);i++)
		{
			Nodes[i]=NULL;
			DFSvisited[i]=false;
			BFSvisited[i]=false;
			BFSdepth[i]=0;
			DFSdepth[i]=0;
		}
	}
	
	void Connect(int a,int b)
{
		Node *pb = new Node();
		if(pb==NULL)
	{
			cout<<"Error!Overflow!"<<endl;
			return;
	}
		else
	{
			pb->point=b;
			
			//建立a->b 
		{
			if(Nodes[a]==NULL)
			{
				Nodes[a]=pb;
				return;
			}
			else//Nodes[a]!=NULL，第一个节点不空 
			{
				bool f=true;
				Node *pp = Nodes[a];//pp指向第一个连接节点 
				while(pp->nextNode!=NULL)
				{
					if(pp->nextNode->point==b)
					{
						f=false;
					}
					pp=pp->nextNode;
				}
				if(pp->point==b)//有重合 
				{
					f=false;
				}
				pp=Nodes[a];//pp为第一个节点 
				//没有重合，则进行排序插入操作 
				if(f)
				{
					if(pp->nextNode==NULL)//如果该节点只有一个节点 
					{
						if((pb->point) < (pp->point))
						{
							pb->nextNode=pp;
							Nodes[a]=pb;	
							return;
						}
						else
						{
							pp->nextNode=pb;//直接连接
							return; 
						}
					}
					else//该节点连接了两个及以上节点的情况 
					{
						Node* t = pp;
						if( (pb->point) < (t->point) )
						{
							pb->nextNode=t;
							Nodes[a]=pb;
							return;
						}
						else
						{
							while(t->nextNode!=NULL)
							{
								if(( pb->point > t->point )&&( pb->point < t->nextNode->point ))
								{
									pb->nextNode=t->nextNode;
									t->nextNode=pb;
									return;
								}
								t=t->nextNode;
							}
							//到这里则说明要连接的节点为最大的节点
							if((pb->point)>(t->point))
							{ 
								t->nextNode=pb;
								return;
							}
							
						}
					}
				}
				return;
			}
		
		}
	}
}
	
	void OutputAll()
	{
		int i;
		Node *p=NULL;
		
		for(i=1;i<MAX;i++)
		{
			p=Nodes[i];
			cout<<"与第"<<i<<"个节点相连的点有:";
			if(p==NULL)
			{
				cout<<"无";
			}
			while(p!=NULL)
			{
				cout<<p->point<<" "; 
				
				p=p->nextNode; 
			}
			cout<<endl;
		}
		cout<<"\n";
	}
	
	void DFS(int n)//非递归实现深度优先遍历 
	{
		stack<int> S;
		
		int visitednum=1;
		int depth=0;
		
		DFSvisited[n]=true;
		DFSdepth[n]=depth;
		cout<<"\n深度优先遍历的顺序为:\n";
		
		S.push(n);
		cout<<n<<" ";
		int v;
		bool f;
		while(visitednum<MAX-1)
		{
			v=S.top();
			Node *node=Nodes[v];
			f=false;//表示这个点有用仍然留在栈中，默认没用 
			while(node!=NULL)
			{
				if(DFSvisited[node->point]==false)
				{
					f=true;
					S.push(node->point);
					DFSvisited[node->point]=true;
					cout<<node->point<<" ";
					visitednum++;
					depth++;
					DFSdepth[node->point]=depth;
					break;
				}
				else
				{
					node=node->nextNode;
				}
			}
			if(f==false)
			{
				S.pop();
				depth--;
			}
		}
		cout<<"\n\n";
		cout<<"现在开始打印深度优先生成树的凹凸表\n";
		for(int i=1;i<MAX;i++)
		{
			int left=MAX-DFSdepth[i];
			while(DFSdepth[i]--)
			{
				cout<<"  ";
			}
			cout<<i;
			
			while(left--)
			{
				cout<<"--";
			}
			cout<<endl;
		}
		cout<<endl;
		return;	
	}
	
		void DFS(int n,int unneed)//非递归实现深度优先遍历 
	{
		stack<int> S;
		
		int visitednum=1;
		int depth=0;
		
		for(int i=0;i<MAX;i++)
		{
			DFSvisited[i]=false;
		}
		DFSvisited[unneed]=true;
		
		DFSvisited[n]=true;
		DFSdepth[n]=depth;
		cout<<"\n深度优先遍历的顺序为:\n";
		
		S.push(n);
		cout<<n<<"  ";
		int v;
		bool f;
		while(visitednum<MAX-2)
		{
			v=S.top();
			Node *node=Nodes[v];
			f=false;//表示这个点有用仍然留在栈中，默认没用 
			while(node!=NULL)
			{
				if(DFSvisited[node->point]==false)
				{
					f=true;
					S.push(node->point);
					DFSvisited[node->point]=true;
					cout<<node->point<<"  ";
					visitednum++;
					depth++;
					DFSdepth[node->point]=depth;
					break;
				}
				else
				{
					node=node->nextNode;
				}
			}
			if(f==false)
			{
				S.pop();
				depth--;
			}
		}
		cout<<"\n\n";
		cout<<"现在开始打印深度优先生成树的凹凸表\n";
		for(int i=1;i<MAX;i++)
		{
			if(i==unneed)
			{
				continue;
			}
			int left=MAX-DFSdepth[i];
			while(DFSdepth[i]--)
			{
				cout<<"  ";
			}
			cout<<i;
			
			while(left--)
			{
				cout<<"--";
			}
			cout<<endl;
		}
		cout<<endl;
		return;	
	}
	
	void BFS(int n)
	{
		queue<int> Q;
		
		int visitednum=1;
		int depth=0;
		
		BFSvisited[n]=true;
		cout<<"\n广度优先遍历的顺序为:\n";
		
		BFSdepth[n]=depth;
		Q.push(n);
		cout<<n<<" ";
		int v;
		
		while(visitednum<MAX-1)
		{
			v=Q.front();
			Node *node=Nodes[v];
			depth++;
			//f=false;//表示这个点有用仍然留在栈中，默认没用 
			while(node!=NULL)
			{
				if(BFSvisited[node->point]==false)
				{
					BFSvisited[node->point]=true;
					Q.push(node->point);
					BFSdepth[node->point]=depth;
					cout<<node->point<<" ";
					visitednum++;
					node=node->nextNode; 
				}
				else
				{
					node=node->nextNode;
				}
			}
			//node==NULL,则这个节点广度优先搜索完了 
			Q.pop();
		}
		cout<<"\n\n";
		cout<<"现在开始打印广度优先生成树的凹凸表\n";
		for(int i=1;i<MAX;i++)
		{
			int left=MAX-BFSdepth[i];
			while(BFSdepth[i]--)
			{
				cout<<"  ";
			}
			cout<<i;
			
			while(left--)
			{
				cout<<"--";
			}
			cout<<endl;
		}
		cout<<endl;
		return;
	}
	
	void BFS(int n,int unneed)
	{
		queue<int> Q;
		
		int visitednum=1;
		int depth=0;
		
		for(int i=0;i<MAX;i++)
		{
			BFSvisited[i]=false;
		}
		BFSvisited[unneed]=true;
		
		BFSvisited[n]=true;
		cout<<"\n新的广度优先遍历的顺序为:\n";
		
		BFSdepth[n]=depth;
		Q.push(n);
		cout<<n<<"  ";
		int v;
		
		while(visitednum<MAX-2)
		{
			v=Q.front();
			Node *node=Nodes[v];
			depth++;
			//f=false;//表示这个点有用仍然留在栈中，默认没用 
			while(node!=NULL)
			{
				if(BFSvisited[node->point]==false)
				{
					BFSvisited[node->point]=true;
					Q.push(node->point);
					BFSdepth[node->point]=depth;
					cout<<node->point<<"  ";
					visitednum++;
					node=node->nextNode; 
				}
				else
				{
					node=node->nextNode;
				}
			}
			//node==NULL,则这个节点广度优先搜索完了 
			Q.pop();
		}
		cout<<"\n\n";
		cout<<"现在开始打印新的生成树的凹凸表\n";
		for(int i=1;i<MAX;i++)
		{
			if(i==unneed)
			{
				continue;
			}
			int left=MAX-BFSdepth[i];
			while(BFSdepth[i]--)
			{
				cout<<"  ";
			}
			cout<<i;
			
			while(left--)
			{
				cout<<"--";
			}
			cout<<endl;
		}
		cout<<endl;
		return;
	}
	
};

int main()
{
	Graph G;
	
	int edges;
	int DFSorder[MAX];
	int BFSorder[MAX];
	
	cout<<"请输入边的个数:"<<endl;
	cin>>edges;
	cout<<endl;
	
	int pa,pb;
	for(int i=1;i<=edges;i++)//可重复，自带排序s 
	{
		cout<<"请输入第"<<i<<"条无向边连接的两点:"<<endl;
		scanf("%d %d",&pa,&pb);
		G.Connect(pa,pb);
		G.Connect(pb,pa);
	} 
	cout<<"\n";
	
	G.OutputAll();//打印目前存储所有信息  
	
	int DFSnode;
	cout<<"请输入深度优先遍历(非递归)开始节点"<<"(从1到"<<MAX-1<<"):"<<endl;
	cin>>DFSnode;
	G.DFS(DFSnode);
	
	int BFSnode;
	cout<<"请输入广度优先遍历(非递归)开始节点"<<"(从1到"<<MAX-1<<"):"<<endl;
	cin>>BFSnode;
	G.BFS(BFSnode); 
	
	int unneed;
	cout<<"请输入BFS遍历全图后开始的节点和不想经过的点:"<<endl;
	cin>>BFSnode>>unneed;
	
	G.BFS(BFSnode,unneed);
	
	cout<<"请输入DFS遍历全图后开始的节点和不想经过的点:"<<endl;
	cin>>DFSnode>>unneed;
	
	G.DFS(DFSnode,unneed);
	
	return 0;
} 
