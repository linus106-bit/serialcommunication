#ifndef SERIAL_H
#define SERIAL_H

#define BAUDRATE 115200;


#include <iostream>
#include <termios.h> // Terminal
#include <fcntl.h> // Open Serial Port
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

using namespace std;

class serial
{
public:
    int serial_port;
    struct termios newtio;
    int read_bytes;

    serial();
    ~serial();
    void serialOpen();
    void serialSet();
    void serialClose();
    void sendCVWControl(float V_mm_s, float W_mrad_s);
    void sendCDIFFVControl(float VLmm_s, float VRmm_s);
    void readCDIFFVControl();
};

#endif // SERIAL_H
