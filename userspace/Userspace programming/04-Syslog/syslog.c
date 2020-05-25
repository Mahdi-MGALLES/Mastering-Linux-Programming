#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
 #include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
int main()
{
	FILE *f;
	f = fopen("file.txt","r");
	if(!f)
		syslog(LOG_ERR|LOG_USER,"oops mahdi mgalles log - %m\n");
	else {
		setlogmask (LOG_UPTO (LOG_NOTICE));
		openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
		syslog (LOG_NOTICE, "Program started by User %d", getuid ());
		syslog (LOG_INFO, "A tree falls in a forest");

		closelog ();
	}
	exit(0);
}    
