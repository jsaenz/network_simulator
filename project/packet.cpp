#include "random.h"
#include "packet.h"
#include "global.h"

//function to create all of our packets
packets create_packet(int src, int dst)
{
	class packets packet;
	packet.size = uniformDouble();
	packet.src = src;
	packet.dst = dst;
	packet.create_t = t;
	return packet;
}
