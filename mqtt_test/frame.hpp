#include <stdint.h>

#pragma pack(push,1)
typedef struct {
 uint16_t wLen;
 uint8_t bProtocol;
 char* cName;  
 uint8_t bFlags;
 uint16_t bKeepA;
} fConnect;
#pragma pack(pop)

typedef struct{
    uint16_t wLen;
    char* cName;
    uint16_t wId;
} fPublish;

typedef struct{
    uint8_t bType;
    uint8_t wLen;
    uint8_t bFlag;
    uint8_t bCode;
}fConnack;

typedef struct{
    uint16_t wLenA;
    char* cName;
    uint8_t bQosA;
    uint16_t wLenB;
    uint8_t bQosB;
}fSubscribe;

typedef struct{
    uint16_t wLenA;
    char* cNameA;
    uint16_t wLenB;
    char* cNameB;
}fUnsubscribe;

typedef struct{
    uint8_t bQosA;
    uint8_t bQosB;
    uint8_t bFail;
}fSuback;

typedef struct{
    uint8_t bType;
    uint16_t wLen;
}fDisconnect;

typedef struct{
    uint8_t bType;
    uint16_t wLen;
}fPingresp;

typedef struct{
    uint8_t bType;
    uint16_t wLen;
}fPingreq;