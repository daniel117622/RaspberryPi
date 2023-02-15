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

    char acc = 0;
    while(tmp != endPtr)
    {
        acc +=  *((char*)tmp); // accumlate individual bytes values
        tmp++;
    }

    //STORE THE CHECKSUM
    s->checkSum = (char) acc;
}

void writePreamble(sFrame *s)
{
    s->preamble = 0x69;
}

bool validateCheckSum(sFrame *s)
{
    // THIS CODE RECALCULATE CHECKSUM
    char * ptr = (char*) s; //START OF FRAME
    char * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    char * tmp = ptr; // ITERATOR

    char acc = 0;
    while(tmp != endPtr - 1) // TO NOT CONSIDER THE CHECKSUM AGAIN
    {
        acc +=  *((char*)tmp);
        tmp++;
    }
    
    if (s->checkSum == acc) { return true; } else { return false; }
}
