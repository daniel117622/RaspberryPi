#include <stdint.h> // uint8_t
#include <stdbool.h>
#define MAGNETOMETER 1
#define ACCELEROMETER 2
#define GYROSCOPE 4

#define REQ_MAGNET 0x1
#define REQ_ACCEL 0x2
#define REQ_GYRO 0x3
#define REQ_ALL 0xFF

#define X_AXIS 0x01
#define Y_AXIS 0x02
#define Z_AXIS 0x03
#define ALL_AXIS 0x04
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
} sFrame; // 19 BYTES


typedef struct 
{
    char preamble;
    char sensor;
    char datasize;
    char axis;
    char checksum;
} rFrame;
//void generateCheckSum(sFrame*);
//void writePreamble(sFrame*);
//bool validateCheckSum(sFrame*);

typedef struct 
{
    char preamble;
    char sensor;
    char datasize;
    char timestamp[4];
    char sData[4];   
    char checkSum;
} SingleAxisSingleDataFrame;

typedef struct 
{
    char preamble;
    char sensor;
    char datasize;
    char timestamp[4];

    char xData[4];
    char yData[4];
    char zData[4];

    char checkSum;
} XyzSingleDataFrame;

typedef struct 
{
    char preamble;
    char sensor;
    char datasize;
    char timestamp[4];

    char x1Data[4];
    char x2Data[4];  
    char x3Data[4];    

    char checkSum;
} AllSensorsSingleDataFrame;

typedef struct 
{
    char preamble;
    char sensor;
    char datasize;
    char timestamp[4];

    char x1Data[4];
    char y1Data[4];
    char z1Data[4];

    char x2Data[4];
    char y2Data[4];
    char z2Data[4]; 

    char x3Data[4];
    char y3Data[4];
    char z3Data[4]; 

    char checkSum;
} XyzAllSensorsDataFrame;

void generateCheckSum(void *s) // GENERATE A CHECKSUM FOR THE GIVEN STRUCT
{
    char * ptr = (char*) s; //START OF FRAME

    char * endPtr = ptr + *(ptr + 2); // CONSULTING THE VALUE OF DATA SIZE. FRAMES MUST HAVE THIS FIELD DEFINED AT ALL TIMES
    //char * endPtr = ptr + sizeof(sFrame); // END OF FRAME
    
    char * tmp = ptr; // ITERATOR
    char acc = 0;

    while(tmp != endPtr)
    {
        acc +=  *((char*)tmp); // accumlate individual bytes values
        tmp++;
    }

    //STORE THE CHECKSUM
    *endPtr = (char) acc; // LAST BIT
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
