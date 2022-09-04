#include <stdio.h>		// 필요한 header file 추가 가능
#include <string.h>
#include <stdbool.h>
#include "student.h"

//
// 함수 readRecord()는 학생 레코드 파일에서 주어진 rrn에 해당하는 레코드를 읽어서 
// recordbuf에 저장하고, 이후 unpack() 함수를 호출하여 학생 타입의 변수에 레코드의
// 각 필드값을 저장한다. 성공하면 1을 그렇지 않으면 0을 리턴한다.
// unpack() 함수는 recordbuf에 저장되어 있는 record에서 각 field를 추출하는 일을 한다.
//
int readRecord(FILE *fp, STUDENT *s, int rrn);
void unpack(const char *recordbuf, STUDENT *s);

//
// 함수 writeRecord()는 학생 레코드 파일에 주어진 rrn에 해당하는 위치에 recordbuf에 
// 저장되어 있는 레코드를 저장한다. 이전에 pack() 함수를 호출하여 recordbuf에 데이터를 채워 넣는다.
// 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int writeRecord(FILE *fp, const STUDENT *s, int rrn);
void pack(char *recordbuf, const STUDENT *s);

//
// 함수 appendRecord()는 학생 레코드 파일에 새로운 레코드를 append한다.
// 레코드 파일에 레코드가 하나도 존재하지 않는 경우 (첫 번째 append)는 header 레코드를
// 파일에 생성하고 첫 번째 레코드를 저장한다. 
// 당연히 레코드를 append를 할 때마다 header 레코드에 대한 수정이 뒤따라야 한다.
// 함수 appendRecord()는 내부적으로 writeRecord() 함수를 호출하여 레코드 저장을 해결한다.
// 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email);

//
// 학생 레코드 파일에서 검색 키값을 만족하는 레코드가 존재하는지를 sequential search 기법을 
// 통해 찾아내고, 이를 만족하는 모든 레코드의 내용을 출력한다. 검색 키는 학생 레코드를 구성하는
// 어떤 필드도 가능하다. 내부적으로 readRecord() 함수를 호출하여 sequential search를 수행한다.
// 검색 결과를 출력할 때 반드시 printRecord() 함수를 사용한다. (반드시 지켜야 하며, 그렇지
// 않는 경우 채점 프로그램에서 자동적으로 틀린 것으로 인식함)
//
void searchRecord(FILE *fp, enum FIELD f, char *keyval);
void printRecord(const STUDENT *s);

//
// 레코드의 필드명을 enum FIELD 타입의 값으로 변환시켜 준다.
// 예를 들면, 사용자가 수행한 명령어의 인자로 "NAME"이라는 필드명을 사용하였다면 
// 프로그램 내부에서 이를 NAME(=1)으로 변환할 필요성이 있으며, 이때 이 함수를 이용한다.
//
enum FIELD getFieldID(char *fieldname);

//
// 학생 레코드 파일에서 "학번" 키값을 만족하는 레코드를 찾아서 이것을 삭제한다.
// 참고로, 검색 조건은 반드시 학번(ID)만을 사용한다. 레코드의 검색은 searchRecord() 함수와
// 유사한 방식으로 구현한다. 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int deleteRecord(FILE *fp, enum FIELD f, char *keyval);

//
// 학생 레코드 파일에 새로운 레코드를 추가한다. 과제 설명서에서 언급한 대로, 삭제 레코드가
// 존재하면 반드시 삭제 레코드들 중 하나에 새로운 레코드를 저장한다. 삭제 레코드 리스트 관리와
// 삭제 레코드의 선택은 교재 방식을 따른다. 새로운 레코드의 추가는 appendRecord() 함수와 비슷한
// 방식으로 구현한다. 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int insertRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email);

void main(int argc, char *argv[])
{
	FILE *fp;			// 모든 file processing operation은 C library를 사용할 것
	char fieldname[6];
	char fieldvalue[21];
	bool field = false;

	if(!strcmp(argv[1], "-a")){
		if((fp = fopen(argv[2], "r+"))==NULL)
			fp = fopen(argv[2], "w+");
		appendRecord(fp, argv[3], argv[4], argv[5], argv[6], argv[7]);
	}
	else if(!strcmp(argv[1], "-s")){
		fp = fopen(argv[2], "r");
		strcpy(fieldname, strtok(argv[3], "="));
		strcpy(fieldvalue, strtok(NULL, "="));
		searchRecord(fp, getFieldID(fieldname),fieldvalue);
	}
	else if(!strcmp(argv[1], "-d")){
		if((fp = fopen(argv[2], "r+"))==NULL)
			fp = fopen(argv[2], "w+");
		strcpy(fieldname, strtok(argv[3], "="));
		strcpy(fieldvalue, strtok(NULL, "="));
		deleteRecord(fp, getFieldID(fieldname),fieldvalue);
	}
	else if(!strcmp(argv[1], "-i")){
		if((fp = fopen(argv[2], "r+"))==NULL)
			fp = fopen(argv[2], "w+");
		insertRecord(fp, argv[3], argv[4], argv[5], argv[6], argv[7]);
	}
}

int readRecord(FILE *fp, STUDENT *s, int rrn){
	int ret = 0;
	char recordbuf[RECORD_SIZE];

	fseek(fp, HEADER_SIZE+RECORD_SIZE*rrn, SEEK_SET);
	ret += fread(recordbuf, RECORD_SIZE, 1, fp);
	if(recordbuf[0]=='*')
		return 0;
	unpack(recordbuf, s);
	return ret>0;
}

void unpack(const char *recordbuf, STUDENT *s){
	char buf[RECORD_SIZE];
	strcpy(buf, recordbuf);
	strcpy(s->id,strtok(buf, "#"));
	strcpy(s->name,strtok(NULL, "#"));
	strcpy(s->dept,strtok(NULL, "#"));
	strcpy(s->addr,strtok(NULL, "#"));
	strcpy(s->email,strtok(NULL, "#"));
}

int writeRecord(FILE *fp, const STUDENT *s, int rrn){
	char recordbuf[85];
	int ret = 0;
	
	pack(recordbuf, s);

	fseek(fp, HEADER_SIZE+RECORD_SIZE*rrn, SEEK_SET);
	ret += fwrite(recordbuf, RECORD_SIZE, 1, fp);

	return ret>0;
}

void pack(char *recordbuf, const STUDENT *s){
	int ptr = 0;

	memcpy(recordbuf+ptr, s->id, strlen(s->id));
	ptr += strlen(s->id);
	recordbuf[ptr++] = '#';
	memcpy(recordbuf+ptr, s->name, strlen(s->name));
	ptr += strlen(s->name);
	recordbuf[ptr++] = '#';
	memcpy(recordbuf+ptr, s->dept, strlen(s->dept));
	ptr += strlen(s->dept);
	recordbuf[ptr++] = '#';
	memcpy(recordbuf+ptr, s->addr, strlen(s->addr));
	ptr += strlen(s->addr);
	recordbuf[ptr++] = '#';
	memcpy(recordbuf+ptr, s->email, strlen(s->email));
	ptr += strlen(s->email);
	recordbuf[ptr++] = '\0';
}

int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email){
	STUDENT student;
	char header[HEADER_SIZE];
	int rrn=0;
	int rsvn;
	int ret = 0;
	
	strncpy(student.id, id, 8);
	strncpy(student.name, name, 10);
	strncpy(student.dept, dept, 12);
	strncpy(student.addr, addr, 30);
	strncpy(student.email, email, 20);

	fseek(fp, 0, SEEK_END);
	if(ftell(fp)==0){
		rrn = 0;
		rsvn = -1;
		memcpy(header+sizeof(int), &rsvn, HEADER_SIZE-sizeof(int));
	}
	else{
		fseek(fp, 0, SEEK_SET);
		ret += fread(header, HEADER_SIZE, 1, fp);
		memcpy(&rrn, header, sizeof(int));
	}
	ret += writeRecord(fp, &student, rrn);

	//update header
	rrn += 1;
	memcpy(header, &rrn, sizeof(int));
	fseek(fp, 0, SEEK_SET);
	ret += fwrite(header, HEADER_SIZE, 1, fp);

	return ret>0;
}

void searchRecord(FILE *fp, enum FIELD f, char *keyval){
	STUDENT student;
	char buf[HEADER_SIZE];
	int rrn;
	char record[RECORD_SIZE];
	int idx[6]={0, 9, 20, 33, 64, 85};
	
	fseek(fp, 0, SEEK_SET);
	fread(buf, HEADER_SIZE, 1, fp);
	memcpy(&rrn, buf, 4);
	for(int i=0; i<rrn; i++){
		if(readRecord(fp, &student, i) == 0)
			continue;
		memcpy(record, &student, RECORD_SIZE);
		for(int i=0; i<5; i++){
			record[idx[i+1]-1] = '\0';
		}
		if(!strcmp(&record[idx[f]],keyval))
				printRecord(&student);
	}
}

int deleteRecord(FILE *fp, enum FIELD f, char *keyval){
	STUDENT student;
	char buf[HEADER_SIZE];
	int rrn;
	int rsvn;
	char tombstone[TOMBSTONE_SIZE];
	char record[RECORD_SIZE];
	int idx[6]={0, 9, 20, 33, 64, 85};
	
	fseek(fp, 0, SEEK_SET);
	fread(buf, HEADER_SIZE, 1, fp);
	memcpy(&rrn, buf, 4);
	memcpy(&rsvn, buf+4, 4);
	for(int i=0; i<rrn; i++){
		readRecord(fp, &student, i);
		memcpy(record, &student, RECORD_SIZE);
		for(int i=0; i<5; i++){
			record[idx[i+1]-1] = '\0';
		}
		if(!strcmp(&record[idx[f]],keyval)){
			tombstone[0] = '*';
			memcpy(&tombstone[1], &rsvn, sizeof(int));
			rsvn = i;
			fseek(fp, HEADER_SIZE+RECORD_SIZE*i, SEEK_SET);
			fwrite(tombstone, TOMBSTONE_SIZE, 1, fp);
		}
	}
	//rsvn update
	fseek(fp, 0, SEEK_SET);
	memcpy(buf+4, &rsvn, 4);
	fwrite(buf, HEADER_SIZE, 1, fp);
}

int insertRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email){
	STUDENT student;
	char buf[HEADER_SIZE];
	char tombstone[TOMBSTONE_SIZE];
	int rsvn=0;
	int next;
	int ret = 0;

	fseek(fp, 0, SEEK_END);
	if(ftell(fp)==0){	//no record
		ret += appendRecord(fp, id, name, dept, addr, email);
		return ret;
	}
	else{
		//check rsvn
		fseek(fp, 0, SEEK_SET);
		ret += fread(buf, HEADER_SIZE, 1, fp);
		memcpy(&rsvn, buf+4, sizeof(int));
		if(rsvn == -1){ //no reserved area
			ret += appendRecord(fp, id, name, dept, addr, email);
			return ret;
		}
		//update rsvn
		fseek(fp, HEADER_SIZE+RECORD_SIZE*rsvn, SEEK_SET);
		fread(tombstone, TOMBSTONE_SIZE, 1, fp);
		if(tombstone[0]!='*')
			return 0;
		memcpy(&next, &tombstone[1], sizeof(int));
		memcpy(buf+sizeof(int), &next, sizeof(int));
		fseek(fp, 0, SEEK_SET);
		fwrite(buf, HEADER_SIZE, 1, fp);
	}

	strncpy(student.id, id, 8);
	strncpy(student.name, name, 10);
	strncpy(student.dept, dept, 12);
	strncpy(student.addr, addr, 30);
	strncpy(student.email, email, 20);

	ret += writeRecord(fp, &student, rsvn);

	return ret>0;
}

void printRecord(const STUDENT *s)
{
	printf("%s | %s | %s | %s | %s\n", s->id, s->name, s->dept, s->addr, s->email);
}

enum FIELD getFieldID(char *fieldname){
	enum FIELD field;
	if(!strcmp(fieldname, "ID"))
		field = ID;
	else if(!strcmp(fieldname, "NAME"))
		field = NAME;
	else if(!strcmp(fieldname, "DEPT"))
		field = DEPT;
	else if(!strcmp(fieldname, "ADDR"))
		field = ADDR;
	else if(!strcmp(fieldname, "EMAIL"))
		field = EMAIL;
	return field;
}