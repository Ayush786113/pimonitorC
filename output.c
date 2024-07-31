#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "functions.h"

void handler(int signal){
	CLEAR;
	exit(0);
}

int main(){
	signal(SIGTERM, handler);
	signal(SIGINT, handler);

	float temp;
	float totalmemory;
	float activememory;
	float inactivememory;
	int fan;
	char arch[SIZE];
	char host[SIZE];
	float on;
	char zone[SIZE];
	pthread_t threads[THREADS];

	CLEAR;

	architecture(arch);
	hostname(host);
	zoneinfo(zone);
	
	//goto(0, 0);	
	//printf("Hostname:  %s\n", host);
	//goto(0, 32);
	//printf("Architecture: %s\n", arch);
	//goto(0, 64);
	//printf("Timezone: %s\n", zone);
	
	pthread_create(threads+0, NULL, temperature, NULL);
	pthread_create(threads+1, NULL, cooler, NULL);
	pthread_create(threads+2, NULL, memory, NULL);
	pthread_create(threads+3, NULL, uptime, NULL);
	pthread_create(threads+4, NULL, date, NULL);

	while(1) {
		goto(0, 0);	
		printf(BACKSPACE BOLD BRIGHTWHITE "Hostname:  %s\n" RESET, host);
		sleep(3);
		goto(0, 0);
		printf(BACKSPACE BOLD BRIGHTWHITE "Architecture: %s\n" RESET, arch);
		sleep(3);
		goto(0, 0);
		printf(BACKSPACE BOLD BRIGHTWHITE "Timezone: %s\n" RESET, zone);
		sleep(3);
	}

	for(int i = 0; i<THREADS; i++){
		pthread_join(threads[i], NULL);
	}

//	while(1){
//		printf("Hostname:  %s\n", host);
//		printf("Architecture: %s\n", arch);
//		printf("Timezone: %s\n", zone);
//		temperature(&temp);
//		//printf("Temperature: %.2f\n", temp/1000);
//		cooler(&fan);
//		//printf("Fan: %d\n", fan);
//		memory(&totalmemory, &activememory, &inactivememory);
//		//printf("Total: %.2f, Active: %.2f, Inactive: %.2f\n", totalmemory/(1024*1024), activememory/(1024*1024), inactivememory/(1024*1024));
//		uptime(&on);
//		//printf("Uptime: %.2f\n", on/86400);
//	//	sleep(1);
//	}
	return 0;
}
