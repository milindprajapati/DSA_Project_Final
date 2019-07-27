#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include <sstream>
#include <math.h>
#include <chrono> 
#include <ctime>
#include<iomanip>
using namespace std::chrono; 
using namespace std;
struct Node
{
    int val;
    Node* next;
};

struct AdjList
{
    Node *head;
};

struct Graph
{
    int V;
    AdjList* hub;
    AdjList* auth;
};

Node* createNode1596(int val)
{
    Node* n =(Node*) malloc(sizeof(Node));
    n->val= val;
    n->next = NULL;
    return n;
}

Graph* createGraph1596(int V)
{
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g->V = V;

    g->hub = (AdjList*) malloc(V * sizeof(AdjList));
    g->auth = (AdjList*) malloc(V * sizeof(AdjList));

    for (int i = 0; i < V; ++i)
    {
        g->hub[i].head = NULL;
        g->auth[i].head=NULL;
    }
    return g;
}

void addEdge1596(Graph* g, int a, int b)
{
    //creating hub or outdegree adj list
    Node* n=createNode1596(b);
    n->next = g->hub[a].head;
    g->hub[a].head = n;

    //creating authority or indegree adj list
    Node* nn=createNode1596(a);
    nn->next = g->auth[b].head;
    g->auth[b].head = nn;
}

void authorityList1596(Graph* g,int v,vector<int>& authList)
{
    Node* n=g->auth[v].head;
    while(n)
    {
        authList.push_back(n->val);
        n=n->next;
    }
}

int Outdegree1596(Graph* g,int v)
{
    Node* n=g->hub[v].head;
    int cnt=0;
    while(n)
    {
        cnt++;
        n=n->next;
    }
    return cnt;
}

void iterate1596(Graph* g,int v,int t,vector<double>& prev, vector<double>& cur,float damp)
{
    for(int i=0;i<v;i++)
    {
        double res=0.15/v;
        vector<int> authlist;
        authorityList1596(g,i,authlist);
        for(int j=0;j<authlist.size();j++)
        {
            res+=(prev[authlist[j]]*damp)/Outdegree1596(g,authlist[j]);
        }
        cur[i]=res;
    }

    //printing
    if(v<=1)
    {
        //printing
        cout.precision(5);
        cout<<"Iter  : "<<t<<" :";
        for(int i=0;i<v;i++)
        {
            cout<<"P["<<i<<"]="<<fixed<<cur[i]<<" ";
        }
        cout<<endl;
    }

}


void printGraph(Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        int cnt=0;
        Node* n = graph->hub[v].head;
        cout<<"\n"<<"Adjacency list(hub) of vertex "<<v;
        while (n)
        {
            cout<<" ->"<<n->val;
            n= n->next;
            cnt++;
        }
        cout<<endl;
        cout<<"outdegree: "<<cnt<<endl;
        n = graph->auth[v].head;
        cout<<"\n"<<"Adjacency list(authority) of vertex "<<v;
        while (n)
        {
            cout<<" <-"<<n->val;
            n= n->next;
        }
        cout<<endl;
    }
}


void pgrk1596()
{

    ifstream in("graph.txt");
    int v,e;
    if(in.is_open())
    {
        in>>v>>e;
    }
    Graph* g=createGraph1596(v);
    int a,b;
    for(int i=0;i<e;i++)
    {
        in>>a>>b;
        addEdge1596(g,a,b);
    }
   
    int iter=0,ival=0;
    float damp=0.00;
    iter=10;
    ival=0;
    damp=0.85;
    //cout<<"Iteration Value :"<<iter<<endl;
    //cout<<"Initial Value :"<<ival<<endl;
    //cout<<"Dampling Value :"<<damp<<endl;
    double errorrate=0;
    vector<double> prev(v, 0.0);
    vector<double> cur(v, 0.0);
    double inval;
    cout.precision(7);
   	
    if(v>10)
    {
        iter=0;
        ival=0;
    }

   /* if(ival==1) inval=1;
    else if(ival==-1)
        inval=(double)1/v;
    else if(ival==-2)
        inval=(double)1/sqrt(v);
    else inval=0;
*/
    inval=0;
    for(int i=0;i<v;i++)
    {
        prev[i]=inval;
    }
    //printing the base line
  /*  if(v<=1)
    {
        cout<<"Base  : 0 :";
        for(int i=0;i<v;i++)
        {
            cout<<"P["<<i<<"]="<<fixed<<prev[i]<<" ";
        }
        cout<<endl;
    }*/

    int t=1;
    if(iter>0)
    {
        for(t=1;t<=iter;t++)
        {
            iterate1596(g,v,t,prev,cur,damp);
            for(int i=0;i<v;i++)
            {
                prev[i]=cur[i];
            }
        }
    }
    else
    {
        if(iter==0) errorrate=pow(10,-5);
        else errorrate=pow(10,iter);

        while(1)
        {
            iterate1596(g,v,t,prev,cur,damp);
            bool brk=true;
            for(int i=0;i<v;i++)
            {
                double diff=fabs(prev[i]-cur[i]);
                if(diff<errorrate) continue;
                else
                {
                    brk=false;
                    break;
                }
            }
            if(brk) break;
            for(int i=0;i<v;i++)
            {
                prev[i]=cur[i];
            }
            t++;
        }
    }

   /* if(v>1)
    {
        cout<<"Iter  : "<<t<<endl;
        for(int i=0;i<v;i++)
        {
            cout<<"P["<<i<<"]="<<fixed<<cur[i]<<endl;
        }
    }
    */

    //printGraph(g);
}


int grphgen(int V, int mod){
	int n,m;
	n=V;
	int maxout=(n*mod)/100;
	m=maxout*n;
	//cout<<n<<" "<<maxout<<" "<<m<<endl;
	if(m<=n*(n-1)&&m>=n-1)
	{
		double graph[n][n]={};
		int i,j=0;
		srand(time(NULL)); 

		for(int i=0;i<n;i++){
			
			int cnt=0;

			for(int j=0;j<n;j++){

				if(rand() % 2 == 1){

					if(cnt<maxout){
						if(graph[i][j]!=1){				
							graph[i][j]=1;
							cnt++;
						}				
					}
				}
			}		
		}
		if(n==800){
			cout<<"Did it pass"<<endl;;
		}		
		int sum=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				sum=sum+graph[i][j];
			}
		}
		m=sum;

		ofstream outfile;
		outfile.open("graph.txt");
		outfile<<n<<" "<<m<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(graph[i][j]==1){
					outfile<<i<<" "<<j<<endl;
				}
			}
		}
		outfile.close();
	}
	else{
		cout<<"Error : Edges are too many or too less, Please Try Again!!"<<endl;;
	}
	return 0;
}


int main(){
	int v[5]={50, 100, 200, 500, 600};
	int od[5]={20, 40, 60, 80, 90};
	ofstream outfile;
	outfile.open("performance.csv",ios::app);
	outfile<<"RUN,NODES,OutDgre,Runtime"<<endl;
	cout<<"====================================================="<<endl;
	cout<<"RUN"<<setw(15)<<"NODES"<<setw(15)<<"MAXOUTDEGREE"<<setw(15)<<"RUNTIME"<<endl;
	cout<<"====================================================="<<endl;
		
	int c=0;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			//cout<<"============================== RUN "<< c <<" ==============================="<<endl;
			//cout<<"No of Nodes: "<<v[j]<<endl<<"Max Out Degree(%)"<<od[i]<<endl;
			double time;
			int run=25;
			for(int k=0;k<run;k++){
				grphgen(v[i],od[j]);
				clock_t begin=clock();
				pgrk1596();
		 		clock_t end=clock();
		 		double duration= double(end - begin) / CLOCKS_PER_SEC;
		 		time=(time+duration);
	 		}
	 		time=time/run;
	 		cout.precision(3);
	 		cout<<c<<setw(15)<<v[i]<<setw(15)<<od[j]<<setw(18)<<time<<endl;
			outfile<<c<<","<<v[i]<<","<<od[j]<<","<<time<<endl;
			c++;
		}	
	}
	outfile.close();
	return 0;

}

