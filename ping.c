#  include "ping.h"


int main(int argc, char **argv)
{

	char *ip_address;
	struct sockaddr_in soc_add;
	int sockfd;
	struct sockaddr_in sock;
	
	if (argc == 1)
	{
		printf("./ft_ping host port\n");
		exit(1);
	}


	//sock.sin_port = hthol(1337);
	// must check for if ip address conrect 
	// here use inet_pton  -- persintaion to netowrk , now i will kept like that becuse i am lazy
	sock.sin_addr.s_addr = inet_addr(argv[1]);
	sock.sin_family =  AF_INET;



	// AF_INET ==>  interent socket 
	// it's RAW SOCKET is not tcp or ude
	// IPPROTO_ICMP   use  ICMP  protocl
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	printf("%d\n", sockfd);
	if (sockfd < 0)
	{
		perror("die :");
		return 1;
	}

	ft_ping(sockfd, &sock);

	


	return 0;
}

