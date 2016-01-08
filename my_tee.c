#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


#define SIZE 1024
int main(int argc, char const *argv[])
{
	
	int fd;
	//int len;
	fd = open(argv[1],O_RDWR|O_CREAT|O_APPEND,0777);
	if(!fd)
	{
		perror("file open ");
	}
	char buf[SIZE];

	// gets(buf);

	read(0,buf,SIZE);
	
	write(1,buf,strlen(buf));
//	read(1,buf,strlen(buf));

	dup2(fd,1);
	// len = strlen(buf);
	// buf[len + 1] = '\n';
	write(fd,buf,strlen(buf));



	close(fd);



	return 0;
}