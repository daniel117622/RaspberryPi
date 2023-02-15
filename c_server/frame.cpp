#include <stdint.h> // uint8_t
#include <stdbool.h>
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


//void generateCheckSum(sFrame*);
//void writePreamble(sFrame*);
//bool validateCheckSum(sFrame*);


void generateCheckSum(sFrame *s) // GENERATE A CHECKSUM FOR THE GIVEN STRUCT
{
    char * ptr = (char*) s; //START OF FRAME
    char * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    char * tmp = ptr; // ITERATOR

    uint8_t acc = 0;
    while(tmp != endPtr)
    {
        acc +=  *((uint8_t*)tmp); // accumlate individual bytes values
        tmp++;
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
    char * ptr = (char*) s; //START OF FRAME
    char * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    char * tmp = ptr; // ITERATOR

    uint8_t acc = 0;
    while(tmp != endPtr)
    {
        acc +=  *((uint8_t*)tmp);
        tmp++;
    }

    sFrame* ss = (sFrame*)ptr;
    printf("\nMeasured checksum: 0x%X \nActual checksum: 0x%X\n\n",(char)ss->checkSum,acc);
    if (ss->checkSum == acc) { return true; } else { return false; }
}
