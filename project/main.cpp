//main.cpp

#include "global.h"
#include "packet.h"
#include "routing_table.h"
#include "random.h"
#include "initialize.h"
#include "routing.h"

//initialize with max values
int N = 150, L = 150*150;
int t = 0;
double total_pkt=0, succ_pkt=0, pkt_drop[150], avg_trans = 0, min_trans = 1000, max_trans = 0;
class nodes node[150];
class links lnk[150*150];

void do_statistics();
	
int main(int argc, char *argv[])
{

  //set seed
  srand((unsigned)atoi(argv[1]));
  //initalize all structs with information
	int x = initialize(argv[2]);
	
  if(x == 1)
    return 0;
  //initialize number of packets dropped to 0	
	for(int i=0;i<150;i++)
		pkt_drop[i]=0;
  //create our 20 packets with random src and dest
  select();

  //calculate our routing table
  calc_table();
  //Return an error if our graph is not connected
  for(int i = 0 ; i < N ; i++){
    for(int j = 0; j< N; j++){
      if(sht_delay[i][j] == 999){
        cout << "Graph is not connected. Please choose a connected graph."<<endl;
        return 0;
      }
    }
  }
// Loop to run network.
	for(; t<1000; t++)
	{
		for(int i=0; i < N; i++){
      //run our network
			routing(i);
    }
	}
  //print all statistics
	do_statistics();
	return 0;
}

//collect all statistics and print them to screen
void do_statistics(){
	double percent = ((double)succ_pkt)/((double)total_pkt);
	percent *= 100;
	int max_drop = pkt_drop[0], min_drop = pkt_drop[0]; double avg_drop = 0.0;
	avg_trans /=  succ_pkt;
	for (int i=0; i < N; i++){
		if (pkt_drop[i] > max_drop)
			max_drop = pkt_drop[i];
		if (pkt_drop[i] < min_drop)
			min_drop = pkt_drop[i];
		avg_drop += pkt_drop[i];
	}
	avg_drop /= N;
	cout<<"Total number of packets generated:  "<<total_pkt<<endl;
	cout<<"Total number of packets that reached the destination successfully:  "<<succ_pkt<<endl;
	cout<<"Percentage of successfully received packets:  "<<percent<<"%"<<endl;
	cout<<"Average packet transmission time for each transmission:  "<<avg_trans<<endl;
	cout<<"Time for completion for the transmissions:  "<<"Max: "<<max_trans<<endl;
	cout<<"                                            "<<"Min: "<<min_trans<<endl;
	cout<<"                                            "<<"Avg: "<<avg_trans<<endl;
	cout<<"Number of packets dropped at a router:  "<<"Max: "<<max_drop<<endl;
	cout<<"                                        "<<"Min: "<<min_drop<<endl;
	cout<<"                                        "<<"Avg: "<<avg_drop<<endl;
	
	//cout<<node[3].service_time<<"  "<<node[0].dst<<endl;
}
