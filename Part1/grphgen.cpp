#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include <sstream>
#include <math.h>
#include<bits/stdc++.h> 
#include <sstream>

using namespace std;

int graphgen(int V,int E);
int main(int argc, char* argv[])
{
	if(argc==3)
	{
		stringstream vstr(argv[1]);
	    stringstream estr(argv[2]);
	    int Vertices ,Edges = 0;
	    vstr>>Vertices;
	    estr>>Edges;
	  	graphgen(Vertices, Edges);
    }
    else{
    	cout<<"Wrong Arguments Passed";
    }
    return 0;
}

int graphgen(int V,int E){

	int n,m;
	n=V;
	m=E;
	if(m<=n*(n-1)&&m>=n-1)
	{
		int graph[n][n]={};
		int i,j=0;
		srand(time(NULL)); 

		for(int k=0;k<m;k++){
			cout<<"Enter Edge :"<< endl<<"From :";
			cin>>i;
			if(i>n-1){
				while(i>n-1){
				cout<<"node doesn't exist"<<endl;
				cout<<"From :";
				cin>>i;
				}
			}
			cout<<"To ";
			cin>>j;
			if(j>n-1){
				while(j>n-1){
				cout<<"node doesn't exist"<<endl;
				cout<<"To :";
				cin>>j;
				}
			}
			cout<<endl;
			if(graph[i][j]!=1){				
				graph[i][j]=1;
			}
			else{
				cout<<"Edge Already Exists..."<<endl;
			}
			
		}
		/*for(int k=0;k<n*0.2;k++){
		for(int i=0;i<n;i++){
				j= (rand()%n);
				if(i!=j){
					if(graph[i][j]!=1){				
						graph[i][j]=1;
					}				
				}		
			}
		}*/
		cout<<"Checking For Sink Node ... "<<endl;
		int sum=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				sum=sum+graph[i][j];
			}
			if(sum==0){
				cout<<"Sink Node is: "<<i<<endl;
				cout<<"Generating Edges from Sink Node ... "<<endl;
				for(int j=0;j<n;j++){
					graph[i][j]=1;
					graph[i][i]=0;
				}

			}
			sum=0;
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				sum=sum+graph[i][j];
			}
		}
		m=sum;

		ofstream outfile;
		outfile.open("graph.txt",ios::app);
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
}