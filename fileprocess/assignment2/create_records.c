#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define RECORD_SIZE 200

int main(int argc, char **argv)
{
    int fd;
    int recordnum;
    char record[RECORD_SIZE];

    
    if(argc!=3){
	fprintf(stderr, "usage : a.out <#records> <record_file_name>\n");
        exit(1);
    }

    if((fd = open(argv[2],O_RDWR|O_CREAT|O_EXCL, 0666)) < 0){
	fprintf(stderr, "error : open error for %s\n", argv[2]);
        exit(1);
    }

    //record에 a로 채움 (마지막은 널 문자)
    for(int i=0; i<RECORD_SIZE-1; i++){
	record[i] = 'a';
    }
    record[RECORD_SIZE] = '\0';

    recordnum = atoi(argv[1]);

    for(int i=0; i<recordnum; i++){
       if(write(fd, record, RECORD_SIZE)<RECORD_SIZE){
	       fprintf(stderr, "error : write error for %ds record\n", i+1);
       }
    }

    close(fd);
    return 0;
}
