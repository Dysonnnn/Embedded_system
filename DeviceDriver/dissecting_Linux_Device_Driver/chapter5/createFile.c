#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define LENGTH 100

int main(int argc, char const *argv[])
{
	/* code */
	int fd, len;
	char str[LENGTH];

	fd = open("create_file.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // create file and open file

	if(fd == 0)
	{
		perror("open file error \n");

	}

	if(fd)
	{
		write(fd,"hello world", strlen("hello world"));// write string into file
		close(fd);
	}



	// read file 

	fd = open("create_file.txt", O_RDWR);
	len = read(fd, str, LENGTH);
	str[len] = '\0';
	printf("file content is %s\n", str);
	close(fd);


	return 0;
}

