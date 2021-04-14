//
// Created by wangyangyang on 2021-04-12.
//

#ifndef SMARTCARV4_PROTOCOL_H
#define SMARTCARV4_PROTOCOL_H

#define FLAG_HEAD0 0xce
#define FLAG_HEAD1 0xfa
#define FLAG_TAIL 0xad

#define TYPE_UPLOAD 0x01
#define TYPE_RECEIVE 0x02
#define TYPE_UPDATE_VEL 0x03

#pragma pack(1)
struct TXProtocol {
    // 帧头信息
    uint8_t head0;
    uint8_t head1;
    uint8_t type;
    uint8_t len;

    short temperature;

    short ax;
    short ay;
    short az;

    short gx;
    short gy;
    short gz;

    short mx;
    short my;
    short mz;

    short velocity;
    short angular;
    
    // 帧尾信息
    uint8_t tail;

};

#endif //SMARTCARV4_PROTOCOL_H
