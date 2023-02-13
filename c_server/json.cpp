#include <iostream> 
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>

#include <unordered_map>
#include <string>


class GenericData
{
    private:
        float magnet_v;
        std::string _type;

        float accel_x;
        float accel_y;
        float accel_z;
        
        float gyro_x;
        float gyro_y;
        float gyro_z;

        unsigned int _time;

        bool is_valid;
    public:
        GenericData(unsigned int time,std::string tipo,float v)
        {
            this->_type = tipo;
            this->_time = time;
            if (tipo.compare("magnetometer") == 0)
            {
                this->magnet_v = v;
                is_valid = true;
            }
            else
            {
                is_valid = false;
            }            
        }
        GenericData(unsigned int time,std::string tipo,float x,float y, float z)
        {
            this->_type = tipo;
            this->_time = time;
            if (tipo.compare("accelerometer") == 0)
            {
                this->accel_x = x;
                this->accel_y = y;
                this->accel_z = z;
                is_valid = true;
            }
            else if (tipo.compare("gyroscope") == 0)
            {
                this->gyro_x = x;
                this->gyro_y = y;
                this->gyro_z = z;
                is_valid = true;
            }
            else
            {
                is_valid = false;
            }
        }
        std::string get()
        {
            if (!is_valid) {return "invalid";}

            if (this->_type.compare("magnetometer") == 0)
            {
                std::stringstream s;
                s<<this->magnet_v;
                return std::string(s.str());     
            }
            else if (this->_type.compare("accelerometer") == 0)
            {
                std::stringstream s;
                s<<"(";
                s<<this->accel_x;
                s<<",";
                s<<this->accel_y;
                s<<",";
                s<<this->accel_z;
                s<<")";                
                return std::string(s.str());    
            }
            else if (this->_type.compare("gyroscope") == 0)
            {
                std::stringstream s;
                s<<"(";
                s<<this->gyro_x;
                s<<",";
                s<<this->gyro_y;
                s<<",";
                s<<this->gyro_z;
                s<<")";                
                return std::string(s.str());  
            }
        }

};

class Parser // Returns a generic Data object when it reads. Only static methods
{
    private:
        std::ifstream _infile;
    public:
        // Usage: First Load a file
        int loadFile(char* filename)
        {

            return 0;
        }
        int populateDictionary(std::unordered_map<std::string,std::list<GenericData*>> &dict,std::string filePath)
        {
            enum state
            {
                EXPECTING_JSON
                EXPECTING_CATEGORY,
                READ_INVALID,
                READ_ACCEL,
                READ_GYRO,
                READ_MAGNET
            } STATE;

            size_t BUFFSIZE = 1024;
            char * lineBuffer;
            char * token;

            FILE * fp = fopen(filePath,"w");
            // START STATE MACHINE
            STATE = EXPECTING_JSON;
            while(true)
            {
                ssize_t n = getline(&lineBuffer,&BUFFSIZE,fp);
                if (n == -1) {break;}
                // TOKENIZE EACH LINE 
                char * token = strtok(lineBuffer," :");
                while (token)
                {
                    // DO SOMETHING CONSIDERING STATE
                    switch(STATE)
                    {
                        case EXPECTING_JSON:
                        {
                            if (strcmp(token,"{")) { STATE = EXPECTING_CATEGORY; }
                            else { return -1; }
                            break;
                        }
                        case EXPECTING_CATEGORY:
                        {
                            if      ( strcmp(token,"\"magnetometer\"") == 0  ) { STATE = READ_MAGNET; }
                            else if ( strcmp(token,"\"accelerometer\"") == 0 ) { STATE = READ_ACCEL;  }
                            else if ( strcmp(token,"\"gyroscope\"") == 0     ) { STATE = READ_GYRO;   }
                            else { STATE = READ_INVALID ; return -1; }
                            break;
                        }
                        case READ_INVALID: { return -1; }
                        case READ_ACCEL:
                        {
                            char * ptr  = strstr(token,"[{\"timestamp\"")
                            if (ptr != NULL) {return -1;}
                            break;
                        }
                        case READ_GYRO:
                        {

                            break;
                        }
                        case READ_MAGNET:
                        {

                            break;
                        }
                    }
                    // 
                    token = strtok(NULL," ");
                }
            }

            return 0;
        }

};

// Magnetometro. {Escalar}
// Gyroscopio {_x,_y,_z}
// Accelerometro {Escalar}
