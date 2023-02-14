#include <stdint.h> // uint8_t
#define MAGNETOMETER 1
#define ACCELEROMETER 2
#define GYROSCOPE 4

// preamble is always a const
// checksum before launching the frame
typedef struct 
{
    char preamble;
    char type;
    char time[4];
    char v1[4]; 
    char v2[4];
    char v3[4];
    char checkSum;
} sFrame;

void generateCheckSum(sFrame *s) // GENERATE A CHECKSUM FOR THE GIVEN STRUCT
{
    void * ptr = (void*) s; //START OF FRAME
    void * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    void * tmp = ptr; // ITERATOR

    uint8_t acc = 0;
    while(tmp != endPtr)
    {
        acc +=  *((uint8_t*)tmp) % 4; // accumlate individual bytes values
        tmp+1;
    }

    sFrame* ss = (sFrame*)ptr;
    ss->checkSum = (char) acc;
}

void writePreamble(sFrame *s)
{
    s->preamble = 0x69;
}

bool validateCheckSum(sFrame *s)
{
    void * ptr = (void*) s; //START OF FRAME
    void * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    void * tmp = ptr; // ITERATOR

    uint8_t acc = 0;
    while(tmp != endPtr)
    {
        acc +=  *((uint8_t*)tmp) % 4;
        tmp+1;
    }

    sFrame* ss = (sFrame*)ptr;
    if (ss->checkSum == acc) { return true; } else { return false; }

}
