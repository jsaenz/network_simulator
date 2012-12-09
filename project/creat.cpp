//Create a connected graph with 150 nodes.
//output result to a file

#include<stdio.h>
#include<iostream>
#include<time.h>
#include<fstream>
#include <cstdlib>
using namespace std;
#define N 150  //assume there are N nodes

//define link structure
class links {
public:
	int delay;
	int node_1, node_2;
};

//define node structure
class nodes {
public:
	int name;
	
};

//To calculate max no. of links
int permutation(int n){	
  if (n<=2) return 1;
	return (n*(n-1))/2;
}

	
int main(){
	int l, n,node1,node2, i=0, j, flag=0;
	n = permutation(N)-N+2;
	srand((unsigned)time(NULL));
	l = rand()%n + N-1;//number of links range from N-1 to n-1+N-1 so that we can make sure that it is connect
	class nodes node[N];
	class links lnk[l];
	while (i < l){   //create links, avoid the links whose both sides are same node and that are created already
		node1 = rand()%N;
		node2 = rand()%N;
		if (node1==node2) continue;
		for (j=0;j<l;j++) 
			if ((lnk[j].node_1==node1 && lnk[j].node_2==node2)||(lnk[j].node_1==node2 && lnk[j].node_2==node1)){
				flag = 1;
				break;
			}
		if (flag){
			flag = 0;
			continue;
		}
		lnk[i].node_1 = node1;
		lnk[i].node_2 = node2;
		i++;
	}
	//write into file
	ofstream fout ("Graph.txt");
	if(!fout) cout<<"file open error!!"<<endl;
	fout<<N<<" "<<l<<endl;
	for (i=0;i<l;i++)
		fout<<lnk[i].node_1<<" "<<lnk[i].node_2<<endl;
	fout<<"**";
	fout.close();
	return 0;
}
