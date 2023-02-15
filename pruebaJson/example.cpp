#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
int main()
{
    std::ifstream f("data.json");
    json data = json::parse(f);
    string name = data.value("name", "not found");
    string grade = data.value("grade", "not found");
    string email = data.value("email", "not found");
    cout << "Name: " << name << endl;
    cout << "Grade: " << grade << endl;
    cout << "Email: " << email << endl;
    return 0;
}
