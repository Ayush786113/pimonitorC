
#define SIZE 255
#define THREADS 5

#define TEMPERATURE "/data/sys/class/thermal/thermal_zone0/temp"

#define MEMORY "/data/proc/meminfo"
#define MEMTOTAL "MemTotal: "
#define ACTIVE "Active: "
#define INACTIVE "Inactive: "

#define COOLER "/data/sys/class/thermal/cooling_device0/cur_state"

#define ARCH "/data/sys/devices/system/cpu/modalias"

#define HOSTNAME "/data/etc/hostname"

#define UPTIME "/data/proc/uptime"

#define TIMEZONE "/data/etc/timezone"

#define CLEAR system("clear")
#define goto(x, y) printf("\e[%d;%dH", x, y)

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define BACKSPACE "\e[2K"

#define BRIGHTWHITE "\e[97m"
#define BRIGHTYELLOW "\e[93m"
#define BRIGHTRED "\e[91m"
#define BRIGHTBLUE "\e[94m"
#define BRIGHTMAGENTA "\e[95m"

void *temperature();
void memoryData(char data[SIZE], float *value); 
//void *memory(float *total, float *active, float *inactive); 
void *memory(); 
void *cooler(); 
void architecture(char arch[SIZE]); 
void hostname(char hostname[SIZE]); 
void *uptime(); 
void zoneinfo(char zone[SIZE]);
void *date(); 
