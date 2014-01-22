#include <iostream>
#include <list>
#include <stdio.h>
#include <math.h>

#define MAX 1024
#define DEBUG 0
#define pushback push_back

using namespace std;

int adj[MAX][MAX];
int nV;
list<int> dom;

void read(){
	int degree,neigh;
	cin >> nV;
	for(int i=0; i < nV; i++){
		adj[i][i]=1;
		cin >> degree;
		for(int j = 0; j < degree; j++){
			cin >> neigh;
			adj[i][neigh]=1;
			adj[neigh][i]=1;
		}
	}
	return;
}


int check(){
	int d, nDom;
	cin >> nDom;
	for(int i=0; i < nDom; i++){
		cin >> d;
		for(int n = 0; n < nV; n++)
			if(adj[d][n]==1)
				dom.push_back(n);
	}
	dom.sort();
	dom.unique();
	return dom.size();
}

int main(){
		read();
		if(nV!=check())
			printf("Not a ");
		printf("Dominating set.\n");
	return 0;
}
