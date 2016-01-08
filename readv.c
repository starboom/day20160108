#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

typedef struct iovec
{
	void *iov_base; /*Start address of buffer*/

	size_t iov_len; /* Number of bytes to transfer 
						from/to buffer*/

}iov;

/*
	参数:
		fd:file descriptor
		iov:iovec strcut
		iovcnt: count of iov
*/
ssize_t my_writev(int fd,const struct iovec *iov,int iovcnt)
{
	int i;
	int LenCount;
	LenCount = 0;
	for(i = 0;i < iovcnt;i++)
	{
		if(write(fd,iov[i].iov_base,iov[i].iov_len) != iov[i].iov_len)
		{
			printf("write fail\n");
		}
		LenCount = iov[i].iov_len + LenCount;
	}
	return LenCount;
}

int main(int argc, char const *argv[])
{
	
	char *buffer0 = "----";
	char *buffer1 = "555";	
	char *buffer2 = "666\n";

	int iovcnt;
	int fd;
	fd = open(argv[1],O_RDWR|O_CREAT|O_APPEND,0777);
	if(fd == -1)
	{
		perror("file open ");
		_exit(-1);
	}

	iov IovGroup[3];

	iovcnt = sizeof(IovGroup) / sizeof(iov);
	printf("%d\n",iovcnt);

	IovGroup[0].iov_base = buffer0;
	IovGroup[1].iov_base = buffer1;
	IovGroup[2].iov_base = buffer2;

	IovGroup[0].iov_len = strlen(buffer0);
	IovGroup[1].iov_len = strlen(buffer1);
	IovGroup[2].iov_len = strlen(buffer2);

	// printf("LenCount = %d\n", IovGroup[2].iov_len + IovGroup[1].iov_len + IovGroup[0].iov_len);

	// int size;

	my_writev(fd,IovGroup,iovcnt);

	// printf("LenCount = %d\n",size);
	return 0;
}


