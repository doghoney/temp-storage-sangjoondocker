#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define RECORD_SIZE	200
#define SUFFLE_NUM	10000	// 이 값은 마음대로 수정 가능

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);

// input parameters: 레코드 파일
int main(int argc, char **argv)
{
	int *read_order_list;
	int num_of_records;
	struct timeval curtime;
	long startTime, endTime;
	char buf[RECORD_SIZE];
	int fd;

	if(argc!=2){
	    fprintf(stderr, "usage : a.out <record_file_name>\n");
            exit(1);
	}

	if((fd = open(argv[1],O_RDONLY)) < 0){
	    fprintf(stderr, "error : open error for %s\n", argv[2]);
	    exit(1);
        }

	num_of_records = lseek(fd, 0, SEEK_END)/RECORD_SIZE;
	read_order_list = malloc(sizeof(int)*num_of_records);
	lseek(fd, 0, SEEK_SET);

	GenRecordSequence(read_order_list, num_of_records);

	gettimeofday(&curtime, NULL);
	startTime = curtime.tv_usec;
	for(int i=0; i<num_of_records; i++){
		lseek(fd, RECORD_SIZE*read_order_list[i], SEEK_SET);
		if(!read(fd, buf, RECORD_SIZE)){
			fprintf(stderr, "error : read error for %ds record\n", i+1);
			exit(1);
		}
	}
	gettimeofday(&curtime, NULL);
	endTime = curtime.tv_usec;

	printf("%ld usec\n", endTime-startTime);
	close(fd);
	return 0;
}

void GenRecordSequence(int *list, int n)
{
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++)
	{
		list[i] = i;
	}
	
	for(i=0; i<SUFFLE_NUM; i++)
	{
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}

	return;
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}
