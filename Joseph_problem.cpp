#include<iostream>
using namespace std;
//Joseph problem 
//Node include password("data"),order("xuhao"),and the next node's pointer *next. 
//Node代表一个节点，每个节点包含data(密码)，xuhao（序号）和pointer *next（下一个节点）
class Node 
{
public:
    int data;
    int xuhao; 
    Node* next;
    
    Node(int _data,int _xuhao)
    {
    	xuhao = _xuhao;
        data = _data;
        next = NULL;
    }
    
};

//LinkList is the Joesph circle,and it doesn't has the head node,pointer *head is the first node
//LinkList是约瑟夫环，无头结点，head指向第一个节点
class LinkList 
{
public:
    Node* head;  
	Node* tail;  
    LinkList() 
    {
    	tail = NULL;
        head = NULL;
    }
    
    void insert(Node *node) //insert a node to the tail  从尾部插入一个节点
    {
        if (head == NULL)//If the head is NULL,then the first node is head  如果head为空，head则指向第一个节点
        {
        	tail = node;
            head = node;
            head->next = head;
            return;
        }
        else
        {
        	tail->next = node;
        	tail = tail->next;
        	node->next = head;
        	return;
		}
    }
    
    void output()
    {
    	Node* current_node = head;
    	while(current_node->next != head)
    	{
    		cout<<"The order is"<<current_node->xuhao<<"and the password is"<<current_node->data<<endl; 
    		current_node = current_node->next;
    	}
    	cout<<"The order is"<<current_node->xuhao<<"and the password is"<<current_node->data<<endl;
    	return;
    }
    
    void delete_node(int password)//to solve the Joseph problem  解决约瑟夫环问题，弹出
    {
    	Node* pre_node = NULL;
    	Node* current_node = tail;
    	for(;;)
    	{
    		if(current_node == current_node->next)
    		{
    			cout<<" "<<current_node->xuhao<<endl;
    			break;
    		}
    		for(int j = 1 ;j < password; j++)
    		{
    			current_node = current_node->next;//current_node is the pre_node of the delete_node currently 当前current_node指向要出列的前一个节点
			} 
			//then the pre_node is the pre node of the delete_node and then current_node is the delete_node  pre_node指向出列前一个节点，然后current_node指向出列节点
    		pre_node = current_node;
    		current_node = current_node->next;
    		
    		password = current_node->data;
    		
    		cout<<" "<<current_node->xuhao;
    		pre_node->next = current_node->next;
    		Node* deletenode=current_node;
    		delete deletenode;
    		current_node = pre_node;
    	}
    	return;
    }
    
};

int main()
{
    LinkList linklist;
    int n,m;
    cout<<"Please input the inital password m:"<<endl;
    cin>>m;
    cout<<"Please input the nodes number n:"<<endl;
	cin>>n; 
    for(int i =1;i<=n;i++)
    {
    	int t;
    	cout<<"Please input the "<<i<<" node's password'"<<endl; 
    	cin>>t;
        Node* node=new Node(t,i);
        linklist.insert(node);
	} 
	cout<<"Now the Joseph circle's situation is :"<<endl;
	linklist.output();
	cout<<"The correct order of nodes out of the Joseph circle is :"<<endl;
	linklist.delete_node(m);
    return 0;
}
