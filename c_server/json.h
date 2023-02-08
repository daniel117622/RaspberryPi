#include <iostream>
#include <map>  
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

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

        bool is_valid;
    public:
        GenericData(std::string tipo,float v)
        {
            this->_type = tipo;
            if (tipo.compare("magnetometer"))
            {
                this->magnet_v = v;
                is_valid = true;
            }
            else
            {
                is_valid = false;
            }            
        }
        GenericData(std::string tipo,float x,float y, float z)
        {
            this->_type = tipo;
            if (tipo.compare("accelerometer"))
            {
                this->accel_x = x;
                this->accel_y = y;
                this->accel_z = z;
                is_valid = true;
            }
            else if (tipo.compare("gyroscope"))
            {
                this->accel_x = x;
                this->accel_y = y;
                this->accel_z = z;
                is_valid = true;
            }
            else
            {
                is_valid = false;
            }
        }
        std::string GenericData::get()
        {
            if (!is_valid) {return "invalid";}

            if (this->_type.compare("magnetometer"))
            {
                std::stringstream s;
                s<<this->magnet_v;
                return std::string(s.str());     
            }
            else if (this->_type.compare("accelerometer"))
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
            else if (this->_type.compare("gyroscope"))
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



// Magnetometro. {Escalar}
// Gyroscopio {_x,_y,_z}
// Accelerometro {Escalar}
