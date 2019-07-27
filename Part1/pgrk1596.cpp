#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include <sstream>
#include <math.h>
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
        cout.precision(7);
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
        cout<<"\n"<<"Outgoing edge from vertex "<<v<<"-->{";
        while (n)
        {
            cout<<" "<<n->val;
            n= n->next;
            cnt++;
        }
        cout<<"}"<<endl;
        cout<<"outdegree: "<<cnt<<endl;
        n = graph->auth[v].head;
        cout<<"\n"<<"Incoming Edge vertex "<<v<<"-->{";
        while (n)
        {
            cout<<" "<<n->val;
            n= n->next;
        }
        cout<<"}"<<endl;;
    }
}


void pgrk1596(int argc,char* argv[])
{
    vector<string> arguments(argv,argv+argc);
    
    if(arguments.size()<5)
    {
        cout<<"Input file missing from command line"<<endl;
    }
    
    ifstream in(argv[5]);
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
    stringstream it(arguments[1]);
    stringstream init(arguments[2]);
    stringstream idamp(arguments[3]);
    stringstream ierr(arguments[4]);

    int iter=0,ival=0;
    float damp=0.00;
    double errorrate=0;
    
    it>>iter;
    init>>ival;
    idamp>>damp;
    ierr>>errorrate;
    cout<<"Iteration Value :"<<iter<<endl;
    cout<<"Initial Value :"<<ival<<endl;
    cout<<"Dampling Value :"<<damp<<endl;
    vector<double> prev(v, 0.0);
    vector<double> cur(v, 0.0);
    double inval;
    cout.precision(7);
    if(v>10)
    {
        iter=0;
        ival=-1;
    }

    if(ival==1) inval=1;
    else if(ival==-1)
        inval=(double)1/v;
    else if(ival==-2)
        inval=(double)1/sqrt(v);
    else inval=0;

    for(int i=0;i<v;i++)
    {
        prev[i]=inval;
    }

    //printing the base line
    if(v<=1)
    {
        cout<<"Base  : 0 :";
        for(int i=0;i<v;i++)
        {
            cout<<"P["<<i<<"]="<<fixed<<prev[i]<<" ";
        }
        cout<<endl;
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

    if(v>1)
    {
        cout<<"Iter  : "<<t<<endl;
        for(int i=0;i<v;i++)
        {
            cout<<"P["<<i<<"]="<<fixed<<cur[i]<<endl;
        }
    }

    printGraph(g);
}


int main(int argc, char* argv[])
{
    pgrk1596(argc,argv);
    return 0;
}
