#include <stdint.h>

typedef struct{
 uint8_t bType;
 uint16_t wLen;
 char* cName;
 uint8_t bProtocol;
 uint8_t bCleanS;
 uint16_t bKeepA;
}mConnect;