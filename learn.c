# include "ping.h"


# define RECV_TIMEOUT 1
# define PING_SLEEP_RATE 1000000
# define BUF_SIZE  1024

# define PING_PKT_S 64

struct ping_pkt {
	
	struct icmphdr hdr;
	char msg[PING_PKT_S - sizeof(struct icmphdr)];
};



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
int main(int argc, char argv) {

	struct sockaddr_in sock, claddr; 
	int sfd, j;
	ssize_t numBytes;
	socklen_t len;
	char buf[BUF_SIZE];
	char claddrstr[INET_ADDRSTRLEN];
	
	struct ping_pkt  pckt;
	struct sockaddr_in retaddr;
	struct timespec time_start, time_end, tfs, tfe;
	long double rtt_mesc =0,total_mesc;
	struct timeval tv_out;
	int flag = 0, msg_count  =0;

	int ttl = 64; 
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;


	sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sfd == -1)
	{
		perror("socket");
		exit(1);
	}

	clock_gettime(CLOCK_MONOTONIC, &tfs);
	memset(&sock, 0, sizeof(struct sockaddr_in) );
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");
	//sock.sin_port = htons(1337);


	int err = 0;
	err = setsockopt(sfd, SOL_IP, IP_TTL , &ttl, sizeof (ttl));
	if (err)
	{
		perror("dasf");
		exit(1);
	}
	 err = setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv_out, sizeof(tv_out));
	if (err)
	{
		perror("adf");
		exit(1);
	}

//bind(sfd, (struct sockadd *)&sock, sizeof(struct sockaddr_in));
	int i = 0;
	while (1)
	{
		flag  =1;

		bzero(&pckt,sizeof(pckt));

		pckt.hdr.type =  ICMP_ECHO;
		pckt.hdr.un.echo.id = getpid();

		
		for (i = 0; i < sizeof (pckt.msg) -1 ;i++)
				pckt.msg[i] = i+ '0';
		pckt.msg[i] = 0;
		pckt.hdr.un.echo.sequence = msg_count++;
		pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
		printf("send\n");
		usleep(PING_SLEEP_RATE);
	


		clock_gettime(CLOCK_MONOTONIC, &time_start);
		err =sendto(sfd, &pckt, sizeof (pckt), 0, (struct sockaddr *)&sock, sizeof(struct sockaddr_in));
		if (err == -1)
		{
			perror("send to ");
			return 0;
		}



		len = sizeof(struct sockaddr_in);
		int 	numBytes = recvfrom(sfd, &pckt, sizeof(pckt), 0,(struct sockaddr *)&retaddr, (socklen_t *)&len);
		
		if (numBytes != -1)
		{
			clock_gettime(CLOCK_MONOTONIC, &time_end);
			printf("RECIVES");
		}
		else 
		{
			perror("hh");
			exit(1);
		}
	
	}





	return (0);
}
