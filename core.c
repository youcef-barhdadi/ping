# include "ping.h"


/*
 *
 * 
 * set ttl to 64,   tll time  time to live how many router the packet will go through , ttl exist on ip header
 *	set time out to 1's 
 *  
 */

void _error(const char *str)
{
	perror(str);
	exit(1);
}

unsigned short checksum(void *b, int len)
{
	
	// sizeof (short) 2

	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;
	int i = 0;
	for(sum = 0; len > 1 ; len -= 2)
		sum += *buf++;

	if (len == -1)
		sum = *(unsigned char *)buf;
	sum = (sum >> 16 ) + (sum & 0xffff);
	sum  +=(sum >> 16);
	result  = ~sum;
	return result;


}



double getduration(struct timeval start, struct timeval end)
{
	return (double)(start.tv_sec - end.tv_sec) ;
}


int ft_ping(const int sfd, struct sockaddr_in  *addr_in)
{
	int ttl = TIME_TO_LIVE, time_out;	
	t_ping ping;
	struct timeval tv_out;
	struct timeval start;
	struct timeval end;
	int check;
	socklen_t addrlen;
	struct sockaddr_in target_addr;
	int i = 0;
	int msg_count = 0;
	tv_out.tv_sec = TIME_OUT;
	tv_out.tv_usec = 0;


	addrlen = sizeof(target_addr);
	if (setsockopt(sfd, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
	{
		_error("setsockopt :");
	}
	if (setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv_out, sizeof(tv_out)) != 0)
	{
		_error("setsockt");
	}	



	while (1)
	{


		bzero(&ping, sizeof(t_ping));
		ping.hdr.type = ICMP_ECHO;
		ping.hdr.un.echo.id = getpid();		
	
		for (i = 0; i < sizeof (ping.msg) -1 ;i++)
				ping.msg[i] = i+ '0';
		ping.msg[i] = 0;
		ping.hdr.un.echo.sequence = msg_count++;
		ping.hdr.checksum = checksum(&ping, sizeof(ping));
		printf("send\n");
		usleep(PING_SLEEP_RATE);

		gettimeofday(&start, NULL);



		check = sendto(sfd,&ping, sizeof(t_ping), 0, (struct sockaddr *)addr_in, sizeof (struct sockaddr_in));
		if (check == -1)
		{
		}
	

		check = recvfrom(sfd, &ping, sizeof(t_ping),0, (struct sockaddr *)&target_addr, (socklen_t *)&addrlen);

		if (check == -1)
		{
		}
		else
		{
			gettimeofday(&end, NULL);
			double  hh =  getduration(start, end);
			if (!(ping.hdr.type == 69 &&ping.hdr.type == 0))
				printf("recived %d %lf\n", ping.hdr.type, hh);
			
		}







	}




	return 0;
}
