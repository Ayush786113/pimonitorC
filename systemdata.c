#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"


void *temperature(){
	char temp[255], prev[255];
	float heat;
	FILE *fp;
	while(1){
		fp = fopen(TEMPERATURE, "r");
		fgets(temp, 255, fp);
		temp[strlen(temp)-1] = '\0';
		heat = atof(temp);
		if(strcmp(temp, prev) != 0) {
			goto(5, 0);
			printf(BRIGHTRED "Temperature: %.2f C\n" RESET, heat/1000);
		}
		strcpy(prev, temp);
		sleep(1);
	}
}

void memoryData(char data[255], float *value){
	char *string = strtok(data, " ");
	string = strtok(NULL, " ");
	*value = atof(string);
}

void *memory(){
	char data[255];
	float total, active, inactive, prev;
	FILE *fp;
	while(1){
		fp = fopen(MEMORY, "r");
		while(fgets(data, sizeof(data), fp)){
			data[strlen(data)-1] = '\0';
			if(strncmp(data, MEMTOTAL, strlen(MEMTOTAL)) == 0)
				memoryData(data, &total);
			else if(strncmp(data, ACTIVE, strlen(ACTIVE)) == 0)
				memoryData(data, &active);
			else if(strncmp(data, INACTIVE, strlen(INACTIVE)) == 0)
				memoryData(data, &inactive);
		}
		if((active/(1024*1024)) != (prev/(1024*1024))) {
			goto(7, 0);
			printf(BRIGHTMAGENTA "Total Memory: %.2f GB, Active Memory: %.2f GB, Inactive Memory: %.2f GB\n" RESET, total/(1024*1024), active/(1024*1024), inactive/(1024*1024));
		}
		prev = active;
		sleep(1);
	}
}

void *cooler(){
	char cur[255], prev[255];
	FILE *fp;
	while(1){
		fp = fopen(COOLER, "r");
		fgets(cur, sizeof(cur), fp);
		cur[strlen(cur)-1] = '\0';
		//*current = atoi(cur);
		if(strcmp(prev, cur) != 0) {
			goto(5, 40);
			printf(BRIGHTBLUE "Fan Level: %s\n" RESET, cur);
		}
		strcpy(prev, cur);
		sleep(1);
	}
}

void architecture(char arch[SIZE]){
	char data[255];
	FILE *fp = fopen(ARCH, "r");
	fgets(data, sizeof(data), fp);
	strtok(data, ":");
	strtok(NULL, ":");
	char *aarch = strtok(NULL, ":");
	strcpy(arch, aarch);
	//arch[strlen(arch)-1] = '\0';
}

void hostname(char hostname[SIZE]){
	FILE *fp = fopen(HOSTNAME, "r");
	fgets(hostname, SIZE, fp);
	//hostname[strlen(hostname)-1] = '\0';
}

void *uptime(){
	char data[255];
	float time;
	int days, hours, minutes, seconds, prev;
	char *string;
	FILE *fp;
	while(1){
		fp = fopen(UPTIME, "r");
		fgets(data, sizeof(data), fp);
		string = strtok(data, " ");
		time = atof(string);
		days = (int)time/86400;
		hours = ((int)time % 86400) / 3600;
		minutes = ((int)time % 3600) / 60;
		seconds = (int)time % 60;
		if(seconds != prev) {
			goto(3, 40);
			printf(BRIGHTYELLOW "Uptime: %d:%d:%d:%d\n" RESET, days, hours, minutes, seconds);
		}
		prev = seconds;
		sleep(1);
	}
}

void zoneinfo(char zone[SIZE]){
	FILE *fp = fopen(TIMEZONE, "r");
	fgets(zone, SIZE, fp);
	//zone[strlen(zone)-1] = '\0';
}

void *date(){
	char date[255], prev[255];
	FILE *fp;
	while(1){
		fp = popen("date", "r");
		fgets(date, sizeof(date), fp);
		if(strcmp(prev, date) != 0){
			goto(3, 0);
			printf(BRIGHTYELLOW "Date: %s\n" RESET, date);
		}
		strcpy(prev, date);
		sleep(1);
	}
}

//int main(){
//	float temp;
//	float totalmemory;
//	float activememory;
//	float inactivememory;
//	int fan;
//	int arch;
//	char host[HOSTNAMESIZE];
//	
//	architecture(&arch);
//	hostname(host);
//
//	while(1){
//		temperature(&temp);
//		printf("Temperature: %.2f\n", temp/1000);
//		memory(&totalmemory, &activememory, &inactivememory);
//		printf("Total: %.2f, Active: %.2f, Inactive: %.2f\n", totalmemory/(1024*1024), activememory/(1024*1024), inactivememory/(1024*1024));
//		cooler(&fan);
//		printf("Fan: %d\n", fan);
//		printf("Architecture: %d\n", arch);
//		printf("Hostname:  %s\n", host);
//		sleep(1);
//	}
//	return 0;
//}
