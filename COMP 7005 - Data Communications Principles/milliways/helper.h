/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	helper.h -   Common set of parameter definitions and helper functions 
--
--	DATE:			November 18, 2005
--
--	REVISIONS:	(Date and Description)
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMERS:	Sachiko Nakano
--
--	NOTES:
--	
-- 
---------------------------------------------------------------------------------------*/



#define SERVER_TCP_PORT	7000	// Default port for TCP
#define SERVER_UDP_PORT	8000	// Default port for UDP

#define TCP 0
#define UDP 1

#define BUFLEN 80  		/* buffer length */
#define DELAY 2

int get_param_clnt( char*[], int*, char*, int );
int get_param_svr( char*[], int* );
int create_socket( const int );
int init_server( const int, struct sockaddr_in*, const int );
int str_tolower( const char*, char[], const int );
int do_sleep( const int );
int atoi_plus( const char[], int* );

/* 
   gets parameters
   param (in): argv - 
   param (out): port_ptr - 
   param (out): host - 
   param (out): host_size - 
   return: protocol - 0 for TCP, 1 for UDP, -1 for error
*/ 
int get_param_clnt( char *argv[], int *port_ptr, char *host, int host_size )
{
    int flag = 0;
    int protocol = TCP;
    char usage[128] = "USAGE: ";
    char dflt[128] = "default - protocol: TCP, host:localhost, port: 7000(TCP) 8000(UDP)\n";

    strcat( usage, argv[0] );  
    strcat( usage, " [-p TCP|-p UDP] [-h host] [-t port]\n" );

    while ( *++argv != 0)
    {
        if ( ( (*argv)[0] != '-' ) || ( strlen(*argv) != 2 ) )
        {
            fprintf( stderr, "'%s' is not a valid switch format\n", *argv );
            fprintf( stderr, "%s", usage );
            return -1;
        }

        const char *swch = *argv;
        if ( (*++argv) == 0 )
        {
            fprintf( stderr, "value for '%s' is missing\n", swch );
            fprintf( stderr, "%s", usage );
            return -1;
        }

        switch( swch[1] )
        {
            case 'p':{
		int n = strlen(*argv);
                char temp[n+1];
                str_tolower( *argv, temp, n+1 );
			
                if( strcmp( temp, "udp" ) == 0 ) 
                {
                    protocol = UDP;
                    if( !flag )
                    {
                        *port_ptr = SERVER_UDP_PORT;
                    }
                }
                else if( strcmp( temp, "tcp" ) != 0 )
                {
                    fprintf( stderr, "'%s' is not a valid protocol\n", *argv );
                    fprintf( stderr, "%s", usage );
                    return -1;
                }
                break;}
            case 'h':{
                int n = strlen(*argv);
                if ( n >= host_size )
                {
                    fprintf( stderr, "host name is too long: max %d\n", host_size-1 ); 
                    return -1;
                }
                host = strncpy( host, *argv, host_size-1 ); 
                break;}
            case 't':
                if ( !atoi_plus( *argv, port_ptr ) || ( *port_ptr <= 0 ) )
                {
                    printf( "port number must be an positive integer: %s\n", *argv );
                    fprintf( stderr, "%s", usage );
                    return -1;
                }
                flag = 1;
                break;
            default:
                fprintf( stderr, "'%s' is not a valid switch\n", swch );
                fprintf( stderr, "%s%s", usage, dflt );
                return -1;
         }
    }
    return protocol;
}

int get_param_svr( char *argv[], int *port_ptr )
{
    int port_set = 0;
    int protocol = TCP;
    char usage[128] = "USAGE: ";
    char dflt[128] = "default - protocol: TCP, port: 7000(TCP) 8000(UDP)\n";

    strcat( usage, argv[0] );  
    strcat( usage, " [-p TCP|-p UDP] [-t port]\n" );

    while ( *++argv != 0)
    {
        if ( ( (*argv)[0] != '-' ) || ( strlen(*argv) != 2 ) )
        {
            fprintf( stderr, "'%s' is not a valid switch format\n", *argv );
            fprintf( stderr, "%s", usage );
            return -1;
        }

        const char *swch = *argv;
        if ( (*++argv) == 0 )
        {
            fprintf( stderr, "value for '%s' is missing\n", swch );
            fprintf( stderr, "%s", usage );
            return -1;
        }

        switch( swch[1] )
        {
            case 'p':{
                int n = strlen(*argv);
                char temp[n+1];
                str_tolower( *argv, temp, n+1 );
			
                if( strcmp( temp, "udp" ) == 0 ) 
                {
                    protocol = UDP;
                    if( !port_set )
                    {
                        *port_ptr = SERVER_UDP_PORT;
                    }
                }
                else if( strcmp( temp, "tcp" ) != 0 )
                {
                    fprintf( stderr, "'%s' is not a valid protocol\n", *argv );
                    fprintf( stderr, "%s", usage );
                    return -1;
                }
                break;}
            case 't':
                if ( !atoi_plus( *argv, port_ptr ) || ( *port_ptr <= 0 ) )
                {
                    printf( "port number must be an positive integer: %s\n", *argv );
                    fprintf( stderr, "%s", usage );
                    return -1;
                }
                port_set = 1;
                break;
            default:
                fprintf( stderr, "'%s' is not a valid switch\n", swch );
                fprintf( stderr, "%s%s", usage, dflt );
                return -1;
        }
    }
    return protocol;
}

int create_socket( const int protocol )
{
    int sock_type = SOCK_STREAM;
    int sock_fd;

    if ( protocol == UDP )
    {
        sock_type = SOCK_DGRAM;
    }

    if ( ( sock_fd = socket( AF_INET, sock_type, 0 ) ) == -1 )
    {
        perror ( "can't create a socket" );
        return -1;
    }

    printf( "socket created: socket file descripter = %d\n", sock_fd );
    sleep( DELAY );
    return sock_fd;
}

/* 
   converts a string to lower case
   param (in): s - original string to convert
   param (out): t - char array that is large enough to hold the 
                    converted string (strlen of s + 1 for '\0') 
   param (in): n - size of t
*/ 
int str_tolower( const char *s, char t[], const int n )
{

    if ( !( strlen(s) < n ) )
    {
        fprintf( stderr, "second argument is not large enough to hold the result\n" );
        return -1; 
    }
    while( *s != '\0' )
    {
        *t++ = tolower(*s++);
    }
    *t = '\0';
    return 0;
}

int do_sleep( const int duration )
{
    if ( duration <= 0 )
    {
        fprintf( stderr, "first argument must be a positive number\n" );
        return -1; 
    }
    int i = 0;
    for ( ; i < duration; i++ )
    {
        printf(".");
        fflush( stdout );
        sleep(1);
    }
    printf("\n");
    return 0;
}

/* 
   param (in): s - string to convert
   param (out): x - int converted 
   return: 1 - if s cantains only digit
           0 - otherwise                  */
int atoi_plus( const char s[], int *x )
{
    int i;
    int temp = 0;
	
    for( i = 0; s[i] >= '0' && s[i] <= '9'; ++i )
    {
        temp = 10 * temp + ( s[i] - '0' );
    }

    *x = temp;
    return ( strlen(s) == i );
}
