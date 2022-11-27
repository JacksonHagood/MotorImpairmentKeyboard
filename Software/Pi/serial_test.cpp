#include <iostream>

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include<termios.h>
#include <unistd.h>


int main() {

    // Serial read
    int fds[2];


    int serial_port = open("/dev/ttyACM0", O_RDWR);

    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    
    dup2(STDOUT_FILENO, serial_port);

    while (true);
}