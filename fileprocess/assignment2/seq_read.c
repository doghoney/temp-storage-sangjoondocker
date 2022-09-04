#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define RECORD_SIZE 200

int main(int argc, char **argv)
{
    int fd;
    struct timeval curtime;
    long startTime, endTime;
    char buf[RECORD_SIZE];
    int num;

    if(argc!=2){
	fprintf(stderr, "usage : a.out <record_file_name>\n");
	exit(1);
    }

    if((fd = open(argv[1],O_RDONLY)) < 0){
	fprintf(stderr, "error : open error for %s\n", argv[2]);
	exit(1);
    }

    num = lseek(fd,0,SEEK_END)/RECORD_SIZE;
    lseek(fd,0,SEEK_SET);
    
    gettimeofday(&curtime, NULL);
    startTime = curtime.tv_usec;
    for(int i=0; i<num; i++){
	if(!read(fd, buf, RECORD_SIZE)){
		fprintf(stderr, "error : read error for %ds record\n", i+1);
		exit(1);
	}
    }
    gettimeofday(&curtime, NULL);
    endTime = curtime.tv_usec;

   
    printf("%ld usec\n",endTime-startTime);
    return 0;
}
