//routing.cpp

#include "global.h"
#include "packet.h"
#include "routing.h"

void output(int);
void input(int);
void forward(int,int,packets);

//Step through one second of the network
void routing(int n){
	if (node[n].src && (t >= (int)(node[n].last_create_t+node[n].create_time))){
		class packets packet;
		packet = create_packet(n,node[n].dst);
		total_pkt++;//total no.++
		forward(n,n,packet);
		node[n].last_create_t = t;
	}
	if (t >= (int)(node[n].last_service_t+node[n].service_time)){
		output(n);
		input(n);
		node[n].last_service_t = t;
	}
}

//if output is called a packet is ready to be forwarded to next node
void output(int n){
    class packets packet;
    for(int i = 0; i < N; i++){
	if (node[n].queue[i].no_of_out == 0) continue;
      packet = node[n].queue[i].output[0];
      int next = node[n].routing_table[packet.dst];
	forward(n,next,packet);
      for(int j = 1; j < node[n].queue[i].no_of_out; j++){
        node[n].queue[i].output[j-1] = node[n].queue[i].output[j];
      }

      //reduce count of output queue by 1
      node[n].queue[i].no_of_out--;
      //node[n].queue[i].output[node[n].queue[i].no_of_out] = NULL;
    }
}

 //take a packet from input queues to output 
 // if this is destination ….//also size&bandwidth
void input(int n){	
  int next;
	double bandwidth;
	class packets packet;
	for (int i=0; i < N; i++){
		if (node[n].queue[i].no_of_in == 0) continue;
		packet = node[n].queue[i].input[0];
		for (int j=1; j < node[n].queue[i].no_of_in; j++)
			node[n].queue[i].input[j-1] = node[n].queue[i].input[j];
		node[n].queue[i].no_of_in--;
		if (packet.dst == n){
			succ_pkt++;
			avg_trans += t - packet.create_t;
			if((t- packet.create_t) > max_trans)
				max_trans = t - packet.create_t;
			if((t - packet.create_t) < min_trans)
				min_trans = t - packet.create_t;
			continue;//need to check unpacked???//destination//receive no.++
		}
		next = node[n].routing_table[packet.dst];
		for (int j=0; j < L; j++)//find bandwidth
			if ((lnk[j].node_1==n && lnk[j].node_2==next)||(lnk[j].node_2==n && lnk[j].node_1==next)){
				bandwidth = lnk[j].bandwidth;
				break;
			}
		while(packet.size > bandwidth){//unpacked
			double size = packet.size;
			packet.size = bandwidth;
			if (node[n].queue[next].no_of_out < 30){
				node[n].queue[next].output[node[n].queue[next].no_of_out] = packet;
				node[n].queue[next].no_of_out++;
			}else{
				pkt_drop[n]++;//drop no.++
			}
			packet.size = size - bandwidth;
			total_pkt++;//total no.++
		}
		if (node[n].queue[next].no_of_out < 30){
			node[n].queue[next].output[node[n].queue[next].no_of_out] = packet;
			node[n].queue[next].no_of_out++;
		}else{
			pkt_drop[n]++;//drop no.++
		}
	}
}

//Packet needs to be sent to next node in path
void forward(int from, int next, packets packet){
        if (node[next].queue[from].no_of_in < 30){
		node[next].queue[from].input[node[next].queue[from].no_of_in] = packet;
  		node[next].queue[from].no_of_in++;
	}else{
		pkt_drop[from]++;//drop no.++
	}
}
