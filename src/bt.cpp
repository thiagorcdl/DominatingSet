#include <iostream>
#include <list>
#include <stdio.h>
#include <math.h>

#define MAX 1024
#define DEBUG 0
#define pushback push_back

using namespace std;

typedef struct adjList{
	int d;			//degree
	int nChoice;		// number of chocies
	int nDom;		// number of times dominated
	list<int> n;		//neighbors
} adjList;

void read(int nV,int *sizeMin,int *maxDg,adjList *adj){
	int n;
	*sizeMin = nV;
	for(int i=0; i < nV; i++){
		cin >> adj[i].d;
		adj[i].nChoice = adj[i].d + 1;
		adj[i].nDom = 0;
		*maxDg = adj[i].d > *maxDg? adj[i].d : *maxDg;
		for(int j = 0; j < adj[i].d; j++){
			cin >> n;
			adj[i].n.pushback(n);
		}
	}
	(*maxDg)++;
	return;
}


void printList(list<int> *lis){
	for(list<int>::iterator it = lis->begin(); it != lis->end(); it++){
		cout << " " << *it;
	}
	return;
}

void check(int level, int size, int nV,int nDom,int *sizeMin,int maxDg,adjList *adj,list<int> *dom,list<int> *domMin){
	#if DEBUG
		printf("\nLevel %d\nMin so far (%d):",level,*sizeMin);
		printList(domMin);
		printf("\nDominated %d/%d (%d):",nDom,nV,size+1);
		printList(dom);
		printf("\nVertices:\n");
		for(int i =0; i<nV; i++)
			cout<< "c: " << adj[i].nChoice << " \t|\td: " << adj[i].nDom << "\n";
	#endif
	/* Stopping Criteria */
	if(size + ceil((nV-nDom)/(maxDg)) >= *sizeMin)
		return;
	if(level == nV){
		if( size < *sizeMin){
			printf("\nFOUND SMALLER (%d):\n",size);
			printList(dom);
			domMin->clear();
			copy(dom->begin(), dom->end(), back_inserter(*domMin));
			*sizeMin = size;
		}
		return;
	}

	list<int>::iterator n;
	int can=1;
	/* Assumes vertex is not in Dominating Set */
	adj[level].nChoice--;
	if(!adj[level].nChoice) can=0;
	if(can) {
		for(n = adj[level].n.begin(); n != adj[level].n.end(); n++){
			adj[*n].nChoice--;
			if(!adj[*n].nChoice) 
				can=0;
		}

		if(can) check(level+1, size,nV,nDom,sizeMin,maxDg,adj,dom,domMin);

		for(n = adj[level].n.begin(); n != adj[level].n.end(); n++)
			adj[*n].nChoice++;
	}
	adj[level].nChoice++;

	/* Tests with vertex in the Dominating Set */
	for(n = adj[level].n.begin(); n != adj[level].n.end(); n++){
		if(!adj[*n].nDom) nDom++; // Only counts if wasn't dominated by others before
		adj[*n].nDom++;
	}
	if(!adj[level].nDom) nDom++;
	adj[level].nDom++;
	dom->pushback(level);

	check(level+1,size+1,nV,nDom,sizeMin,maxDg,adj,dom,domMin);

	dom->remove(level);
	adj[level].nDom--;
	if(!adj[level].nDom) nDom--; 
	for(n = adj[level].n.begin(); n != adj[level].n.end(); n++){
		adj[*n].nDom--;
		if(!adj[*n].nDom) nDom--;
	}
}


void init(int nV, int *maxDg, adjList *adj, list<int> *dom,list<int> *domMin){
	dom->clear();
	domMin->clear();
	*maxDg = 0;
	for(int i=0; i<nV; i++)
		adj[i].n.clear();
	return;
}

int main(){
	adjList adj[MAX];
	list<int> dom, domMin;
	int nV, nDom=0, sizeMin, maxDg=0;
	cin >> nV;
	for(int graph=1; !cin.eof(); graph++){
		init(nV,&maxDg,adj,&dom,&domMin);
		printf("# Graph %d\n",graph);
		read(nV,&sizeMin,&maxDg,adj);
		check(0,0,nV,nDom,&sizeMin,maxDg,adj,&dom,&domMin);
		printf("\n\nMinimum Dominating Set (%d):",sizeMin);
		printList(&domMin);
		cout<<"\n\n####################################\n\n";
		cin >> nV;
	}
	return 0;
}
