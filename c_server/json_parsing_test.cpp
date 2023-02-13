#include "json.cpp"
using namespace std;

int main(void)
{
    GenericData r1(1,"magnetometer",(float)10.6);
    
    /*
    FILE * fp; char * lineBuffer;
    fp = fopen("./data/examples.json","r");
    if (fp == NULL) { cout << "Could not open file" << endl; }

    size_t BUFFSIZE;
    lineBuffer = (char *) malloc(BUFFSIZE * sizeof(char));

    fseek(fp,0L,SEEK_END);
    cout << "Number of bytes is:  " << ftell(fp) << endl;
    fseek(fp,0L,SEEK_SET);
    

    for (int i = 0 ; i <= 1024 ; i++)
    {
        ssize_t n = getline(&lineBuffer,&BUFFSIZE,fp);
        if (n == -1) {  cout << endl; break ; }
        std::cout<<lineBuffer;
    }
    */ 
    list<GenericData> c1;
    list<GenericData> c2;
    list<GenericData> c3;
    unordered_map<string,list<GenericData> > dict;
    

    dict.insert(make_pair("hola",c1));

    string filepath("./data/example.json");

    Parser::populateDictionary(dict,filepath);

    return 0;
}