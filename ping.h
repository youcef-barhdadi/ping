 # ifndef _PING_
#define _PING_

# include <sys/types.h> // for struct . i use like sockaddr_in
# include <sys/socket.h> 
#include <netinet/in.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>


# define  TIME_TO_LIVE 64
# define TIME_OUT 1000000 
# define PORT 1337
# define PING_PKT_SIZE 64
#define PING_SLEEP_RATE 1000000

typedef struct s_ping
{
	struct icmphdr hdr;
	char msg[PING_PKT_SIZE - sizeof(struct icmphdr)];
}				t_ping;






int ft_ping(const int sfd, struct sockaddr_in  *addr_in);
void ping(int);

#endif
