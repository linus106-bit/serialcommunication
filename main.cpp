#include <QCoreApplication>
#include "serial.h"

int main() // int argc, char *argv[]
{
    //QCoreApplication a(argc, argv);
    serial serialComm;
    serialComm.serialOpen();
    serialComm.serialSet();

    float VLmm_s = 10;
    float VRmm_s = 10;

    int stop = 1;
    int key;

    while(stop == 1){
        cout << "Press Key: w,x,a,d,x \n[Forward: w Backward: x Left: a Right: d Stop:  END: q]" << endl;
        cin >> key;
        switch(key){
            case 1: // Forward
                serialComm.sendCDIFFVControl(VLmm_s, VRmm_s);
                break;
            case 2: // Backward
                serialComm.sendCDIFFVControl(-VLmm_s, -VRmm_s);
                break;
            case 3: // Left
                serialComm.sendCDIFFVControl(VLmm_s, 0);
                break;
            case 4: // Right
                serialComm.sendCDIFFVControl(0, VRmm_s);
                break;
            case 5: // Stop
                serialComm.sendCDIFFVControl(0, 0);
                break;
            case 0: // END
                stop = 0;
                serialComm.serialClose();
                break;
            default: // Error
                cout << "Press Again!" << endl;
                break;
        }
    }
    //return a.exec();
    return 0;
}
