#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<map>
using namespace std;
#define MAX 101
int n;
struct HTreeNode		//Huffman tree node type.
{  char data;				
   int weight;				
   int parent;			
   int lchild;				
   int rchild;				
};
HTreeNode ht[MAX];			//Store Huffman Tree.
map<char,string> htcode;		//Store Huffman codes.
struct NodeType			//Priority queue node type.
{  int no;				
   char data;				
   int  weight;			
   bool operator<(const NodeType &s) const
   {					//Used to create a small root heap.
	return s.weight<weight;
   }
};
void CreateHTree()			//Construct Huffman Tree.
{  NodeType e,e1,e2;
   priority_queue<NodeType> qu;
   for (int k=0;k<2*n-1;k++)		//Set the pointer field of all nodes.
      ht[k].lchild=ht[k].rchild=ht[k].parent=-1;
   for (int i=0;i<n;i++)		//Join n nodes into the team qu.
   {  e.no=i; e.data=ht[i].data;
      e.weight=ht[i].weight; qu.push(e);
   }
   for (int j=n;j<2*n-1;j++)		//Construct n-1 non-leaf nodes of Huffman tree.
   {  e1=qu.top();  qu.pop();		
      e2=qu.top();  qu.pop();		
      ht[j].weight=e1.weight+e2.weight;	
      ht[j].lchild=e1.no;
      ht[j].rchild=e2.no;
      ht[e1.no].parent=j;		
      ht[e2.no].parent=j;		
      e.no=j;				
      e.weight=e1.weight+e2.weight;
      qu.push(e);
   }
}
void CreateHCode()		      //Constructing Huffman codes.
{  string code;
   code.reserve(MAX);
   for (int i=0;i<n;i++)	     //Constructing the Huffman code of leaf node i.
   {  code="";
      int curno=i;
      int f=ht[curno].parent;
      while (f!=-1)		      
      {  if (ht[f].lchild==curno)  
            code='0'+code;
         else			      
            code='1'+code;
         curno=f; f=ht[curno].parent;
      }
      htcode[ht[i].data]=code;     
   }
}
void DispHCode(){ // output the huffman code
	map<char,string>::iterator it;
	for (it=htcode.begin();it!=htcode.end();++it)
	cout << "    " << it ->first << ": " << it ->second <<    endl;
}
void DispHTree(){ //output the huffman tree
	for(int i=0; i<2*n-1;i++){
		printf("data=%c, weight=%d, lchild=%d, rchild=%d, parent=%d\n",ht[i].data,ht[i].weight,ht[i].lchild,ht[i].rchild,ht[i].parent);
	}
}

int WPL(){ //Calculate the WPL for the huffman tree
	int wps=0;
	for(int i=0; i<n;i++)
	wps+=ht[i].weight*htcode[ht[i].data].size();
	return wps;
}

int main(void){
	n=5;
	ht[0].data='a'; ht[0].weight=4; // defining each character and the weight for each character
	ht[1].data='b'; ht[1].weight=2;
	ht[2].data='c'; ht[2].weight=1;
	ht[3].data='d'; ht[3].weight=7;
	ht[4].data='e'; ht[4].weight=3;
	CreateHTree();
	printf("the created huffman tree is:\n");
	DispHTree();
	CreateHCode();
	printf("the resulting huffman code is as follows:\n");
	DispHCode();
	printf("WPL=%d\n", WPL());
}






