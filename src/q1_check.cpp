#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1024
#define DEBUG 1
#define pushback push_back
#define range(a) (a % nV == abs(a)? 1 : 0)

using namespace std;

int adj[MAX][MAX];
int nV;

int error(int err, int x){
		if (!range(x)){
			printf("\nERROR: %d not in range [0,%d]\n",x,nV-1);
			return -1;
		}
		return err;
}

int read(){
	int degree,neigh, err=0;
	for(int i=0; i < nV; i++)
		for(int j = 0; j < nV; j++)
				adj[i][j]=0;
	for(int i=0; i < nV; i++){
		adj[i][i]=1;
		cin >> degree;
		err = error(err,degree);
		for(int j = 0; j < degree; j++){
			cin >> neigh;
			err = error(err,neigh);
			adj[i][neigh]=1;
			adj[neigh][i]=1;
		}
	}
	#if DEBUG
		for(int i=0; i < nV;i++){
			printf("\t%d: ",i);
			for(int j = 0; j < nV; j++)
				if(adj[i][j] && i!=j)
					cout << j << " ";
			cout << "\n";
		}
	#endif
	return err;
}


int check(){
	int d, nDom, err=0;
	list<int> dom;
	cin >> nDom;
	err = error(err,nDom);
	for(int i=0; i < nDom; i++){
		cin >> d;
		#if DEBUG
			if(!i)
				printf("# Proposed set (%d):\n\t",nDom);
			cout << d << " ";
		#endif
		err = error(err,d);
		for(int n = 0; n < nV; n++)
			if(adj[d][n]==1)
				dom.push_back(n);
	}
	#if DEBUG
		cout << "\n";
	#endif
	if (!err){
		dom.sort();
		dom.unique();
		err = dom.size();
	}
	dom.clear();
	return err; 
}

int main(){
	cin >> nV;
	for(int graph=1; !cin.eof(); graph++){
		printf("# Graph %d:\n",graph); 
		int r = read();
		int c = check();
		if(r != -1 && c != -1){
			printf("# Proposed set is ");
			if(nV!=c)
				printf("NOT ");
			printf("a Dominating Set.\n");
		}
		cout<<"\n\n####################################\n\n";
		cin >> nV;
	}
	return 0;
}
