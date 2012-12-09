#ifndef PACKET_H
#define PACKET_H
//our packet struct
class packets {
public:
	double size;
	int src, dst;
	int create_t;
};

packets create_packet(int src, int dst); //function prototype

#endif

