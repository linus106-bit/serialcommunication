#include <QCoreApplication>
#include "serial.h"

int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

int main() // int argc, char *argv[]
{
    //QCoreApplication a(argc, argv);
    serial serialComm;
    serialComm.serialOpen();
    serialComm.serialSet();

    float VLmm_s = 50;
    float VRmm_s = 50;

    int stop = 1;
    int key;

    while(stop == 1){
        cout << "Press Key: 1,2,3,4,5,0 \n[Forward: 1 Backward: 2 Left: 3 Right: 4 Stop: 5  END: 6]" << endl;
        key = getch();
        switch(key){
            case 119: // Forward
                serialComm.sendCDIFFVControl(VLmm_s, VRmm_s);
                serialComm.readCDIFFVControl();
                break;
            case 120: // Backward
                serialComm.sendCDIFFVControl(-VLmm_s, -VRmm_s);
                serialComm.readCDIFFVControl();
                break;
            case 97: // Left
                serialComm.sendCDIFFVControl(VLmm_s, 0);
                serialComm.readCDIFFVControl();
                break;
            case 100: // Right
                serialComm.sendCDIFFVControl(0, VRmm_s);
                serialComm.readCDIFFVControl();
                break;
            case 115: // Stop
                serialComm.sendCDIFFVControl(0, 0);
                serialComm.readCDIFFVControl();
                break;
            case 113: // END
                serialComm.sendCDIFFVControl(0, 0);
                serialComm.serialClose();
                stop = 0;
                break;
            default: // Error
                cout << "Press Again!" << endl;
                break;
        }
    }
    //return a.exec();
    return 0;
}
