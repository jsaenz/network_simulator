#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include "packet.h"
using namespace std;

extern int N,L;//global amount of nodes and links
extern int t;//global clock
extern double total_pkt, succ_pkt, pkt_drop[150], avg_trans, min_trans, max_trans; //global stats values
extern int sht_delay[][150];//delays for all links

class queues{
public:
	int no_of_in;//number of packets in input queue
	int no_of_out;//number od packets in output queue
	class packets input[30];
	class packets output[30];
};

class links {
  public:
	int delay;
    	double bandwidth;
  	int node_1, node_2;
  };

class nodes {
  public:
  	int name;
   	class queues queue[150];
  	int routing_table[150];//N-1 next nodes
  	double service_time;
  	int last_service_t;
  	bool src;//is this node a src
  	double create_time;
  	int last_create_t;
  	int dst;// for the src-dst pair
  };

extern class nodes node[];
extern class links lnk[];


#endif
