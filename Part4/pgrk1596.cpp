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
    double errorrate=0;
    vector<double> prev(v, 0.0);
    vector<double> cur(v, 0.0);
    double inval;
    cout.precision(4);
   	
    if(v>10)
    {
        iter=0;
        ival=0;
    }

   
    inval=0;
    for(int i=0;i<v;i++)
    {
        prev[i]=inval;
    }
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
        else errorrate=0.00001;

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

}


int grphgen(int V, int mod){
	int n,m;
	n=V;
	int maxout=(n*mod)/100;
	m=maxout*n;
	//cout<<n<<" "<<maxout<<" "<<m<<endl;

	ofstream outfile;
	outfile.open("graph.txt");
	outfile<<n<<" "<<m<<endl;
		
	if(m<=n*(n-1)&&m>=n-1)
	{
		int i,j=0;
		srand(time(NULL)); 
		int cnt=0;

		for(i=0;i<n;/**/){
			for(j=0;j<n;j++){
				if(rand() % 2 == 1){
					if(cnt<maxout){
							outfile<<i<<" "<<j<<endl;
							cnt++;	
					}
				}
			}
			if(cnt>=maxout){
				i++;
				cnt=0;			

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
	int v[5]={100, 500, 1000, 1500, 3000};
	int od[5]={20, 40, 60, 80, 90};
	cout<<"====================================================="<<endl;
	cout<<"RUN"<<setw(15)<<"NODES"<<setw(15)<<"MAXOUTDEGREE"<<setw(15)<<"RUNTIME"<<endl;
	cout<<"====================================================="<<endl;
		
	int c=0;
	int crun=0;
	double time;
	int run=20;
	double a[5][5];
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			
			crun=0;
			grphgen(v[i],od[j]);
			//for(int k=run;k--;){
				
				clock_t begin=clock();
				pgrk1596();
		 		clock_t end=clock();
		 		double duration= double(end - begin) / CLOCKS_PER_SEC;
		 		time=(duration);

		 		cout<<"\t\t""Last Run : "<< crun <<" Time Taken : "<<duration<<'\r';
		 		crun++;
		 	//}

	 		//time=time/run;
	 		a[i][j]=time;
	 		cout<<c<<setw(15)<<v[i]<<setw(15)<<od[j]<<setw(18)<<setprecision(5)<<time<<endl;
			c++;
		}	

	}
	ofstream outfile;
	outfile.open("performance.txt",ios::app);
	outfile<<"RUN,NODES,OutDgre,Runtime"<<endl;
	
	cout<<"===================================================================================================================================="<<endl;
	cout<<"Nodes"<<setw(15)<<"OD-20"<<setw(15)<<"OD-40"<<setw(15)<<"OD-60"<<setw(15)<<"OD-80"<<setw(15)<<"OD-90"<<endl;
	cout<<"===================================================================================================================================="<<endl;
	for(int i=0;i<5;i++){
		cout<<v[i];
		c=0;
		for(int j=0;j<5;j++){
			cout<<setw(15)<<a[i][j];
			outfile<<c<<","<<v[i]<<","<<od[j]<<","<<a[i][j]<<endl;
			c++;
		}
		cout<<endl;
	}
	outfile.close();

	return 0;

}

