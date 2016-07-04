#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#define MAX_BUF 0x100

int main(){
  int fd;
  char buf[MAX_BUF]; 

  // Use gpio port number 3
  int gpio = 3;

  // Create timespec structure, for 0.5 s delay
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 500000000;


  // Enable gpio3
  fd = open("/sys/class/gpio/export", O_WRONLY);
  sprintf(buf, "%d", gpio); 
  write(fd, buf, 1);
  close(fd);

  // Set output direction in gpio3
  sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
  fd = open(buf, O_WRONLY);
  write(fd, "out", 3); 
  close(fd);

  // Blink with 0.5 s delay
  sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
  fd = open(buf, O_WRONLY);

  while(1){
    printf("Led high\n");
    write(fd, "1", 1); // High value
    lseek(fd, 0, SEEK_SET);
    nanosleep(&ts, NULL);
    printf("Led low\n");
    write(fd, "0", 1); // Low value
    lseek(fd, 0, SEEK_SET);
    nanosleep(&ts,NULL);
  }

  close(fd);
  return 0;
}
