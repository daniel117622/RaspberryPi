#include "json.cpp"

int main(void)
{
    GenericData r1(1,"magnetometer",(float)10.6);
    std::string s = r1.get();
    std::cout<<s<<std::endl;
    return 0;
}