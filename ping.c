#  include "ping.h"


int main(int argc, char **argv)
{

	char *ip_address;
	struct sockaddr_in soc_add;
	size_t sockfd;





	// AF_INET ==>  interent socket 
	// it's RAW SOCKET is not tcp or ude
	// IPPROTO_ICMP   use  ICMP  protocl
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("die :");
		return 1;
	}

	


	return 0;
}

