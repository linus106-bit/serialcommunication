#include "serial.h"


serial::serial()
{
    cout << "Start" <<endl;
}

serial::~serial()
{
}

string get_cmd(string str,float var1, float var2){
    stringstream str1;
    str1 << var1;
    stringstream str2;
    str2 << var2;
    string cmd = str +","+ str1.str() +","+ str2.str() + "\r\n";
    return cmd;
}

void serial::serialOpen(){
    this->serial_port = open("/dev/ttyUSB0", O_RDWR);

    if (this->serial_port < 0) {
        cout << "Error Opening Serial Port = " << serial_port <<endl;
    }
}

// 시리얼 환경 설정
void serial::serialSet()
{
    memset(&newtio,0,sizeof(newtio));
    newtio.c_cflag = B115200;   // 통신 속도 115200
    newtio.c_cflag |= CS8;      // 데이터 비트가 8bit
    newtio.c_cflag |= CLOCAL;   // 외부 모뎀을 사용하지 않고 내부 통신 포트 사용
    newtio.c_cflag |= CREAD;    // 쓰기와 읽기도 가능하게
    newtio.c_iflag = 0;         // parity 비트는 없음
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 1;

    tcflush(serial_port, TCIFLUSH);
    tcsetattr(serial_port,TCSANOW,&newtio);

}
// Close Serial Port
void serial::serialClose(){
    close(serial_port);
    cout << "Serial End" << endl;
}


void serial::sendCVWControl(float V_mm_s, float W_mrad_s){
    string cmd_str = get_cmd("$CVW", V_mm_s, W_mrad_s);
    const string& cmd = cmd_str;
    // write
    write(serial_port, cmd.c_str(), sizeof(cmd));
    cout << cmd.c_str() << endl;
    // read
    memset(&read_buf, '0', sizeof(read_buf));
    int read_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    printf("Bytes: %i, Message: %s\n", read_bytes, read_buf);
}

void serial::sendCDIFFVControl(float VLmm_s, float VRmm_s){
    string cmd_str = get_cmd("$CDIFFV", VLmm_s, VRmm_s);
    const string& cmd = cmd_str;
    // write
    write(serial_port, cmd.c_str(), sizeof(cmd));
    cout << cmd.c_str() << endl;
    // read
    memset(&read_buf, '0', sizeof(read_buf));
    int read_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    printf("Bytes: %i, Message: %s\n", read_bytes, read_buf);
}
