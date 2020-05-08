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

# define PORT 1337
# define PING_PKT_SZIE 64

void ping(int);

#endif
