#include "global.h"
#include "routing_table.h"

int sht_delay[150][150];

//Calculate the shortest delays for all links
void calc_table(){
	int n;

    
	//initialize sht_delay
	for (int i=0; i < N; i++){
		sht_delay[i][i] = 0;
		for (int j=0; j < N; j++){
			if (i != j) sht_delay[i][j] = 999;
			for (int v=0; v < L; v++)
				if ((lnk[v].node_1==i && lnk[v].node_2==j)||(lnk[v].node_2==i && lnk[v].node_1==j))
					sht_delay[i][j]=lnk[v].delay;
		}
	}
	//calculate the shortest delay
	for (int k=0; k < N; k++)
		for (int i=0; i < N; i++)
			for (int j=0; j < N; j++)
				if (sht_delay[i][k]+sht_delay[k][j] < sht_delay[i][j])
					sht_delay[i][j] = sht_delay[i][k]+sht_delay[k][j];
	//calculate next path--routing table
	for (int i=0; i < N; i++){//src
		for (int j=0; j < N; j++){//dst
			if (i == j) continue; //avoid useless calc
			for (int v=0; v < L; v++){//nodes that linked to src
				if (lnk[v].node_1 == i){
					n = lnk[v].node_2;
					if (sht_delay[i][n]+sht_delay[n][j]==sht_delay[i][j]){//find the shortest path
						node[i].routing_table[j] = n;
						if (n != j) break;
					}
				}
				if (lnk[v].node_2 == i){
					n = lnk[v].node_1;
					if (sht_delay[i][n]+sht_delay[n][j]==sht_delay[i][j]){
						node[i].routing_table[j] = n;
						break;
					}
				}
			}
		}
	}
}	
