#include "initialize.h"
#include "global.h"
#include "random.h"
#include "packet.h"


//Function to read in from Graph file and initialize all values for links 
//and number of nodes
int initialize(char *x){

	//Code to read from file
  ifstream infile;
  infile.open(x);

  if (!infile)
  {
    cout << "There was a problem opening " << x << " for reading."<< endl;
    return 1;
  }
  //Get the number of nodes from Graph.txt
  infile >> N;

  //Get number of links from Graph.txt
  infile >> L;
 
  //set all node names
  	for(int i = 0; i < N; i++){
		node[i].name = i;
		node[i].service_time = exponential(1.0);
	}

  //create all links with proper information.
  for(int i = 0; i < L; i++)
  {
   
 	  lnk[i].delay = uniformInt();
    lnk[i].bandwidth = uniformDouble();
    infile >> lnk[i].node_1;
    infile >> lnk[i].node_2;
  }
  
	//close Graph.txt
  infile.close();

  return 0;
}

//Create 20 random src-dst pairs 
void select()
{
  int srce, dstn, i=0;
  while(i < 20)
  {
    srce = rand() % N;
    dstn = rand() % N;
    if ((dstn == srce)||(node[srce].src && (node[srce].dst == dstn)))
    	continue;
    node[srce].dst = dstn;
    node[srce].src = true;
    node[srce].create_time = exponential(0.5);
    i++;
  }
 }
