#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

void read(istream& is, double& v, string& m, char& opr){
    char c;
    m = "";
    is >> v;
    is >> c;
    while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        if(c != ' '){ m += c;}
        if(!(is >> c)){ break;}
    }
    opr = c;
}

void read(istream& is, string& m, char& opr){
    char c;
    m = "";
    is >> c;
    while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        if(c != ' '){ m += c;}
        if(!(is >> c)){ break;}
    }
    opr = c;
}

int main(int argc, char *argv[]){
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            ifstream file{argv[i]};
            NumberWithUnits::read_units(file);
        }
    }
    cout << "please enter the values:\n";
    string input;
    cin >> input;
    istringstream is_input(input);
    double value;
    string measure;
    char opr;
    read(is_input, value, measure, opr);
    NumberWithUnits nwu(value, measure);
    while(true){
        if(opr == '='){
            read(is_input, measure, opr);
            cout << "Solution: " << NumberWithUnits(0, measure) + nwu << endl;
            return 0;
        }
        else if(opr == '+'){
            read(is_input, value, measure, opr);
            nwu += NumberWithUnits(value, measure);
        }
        else if(opr == '-'){
            read(is_input, value, measure, opr);
            nwu -= NumberWithUnits(value, measure);
        }
        else if(opr == '*'){
            read(is_input, value, measure, opr);
            nwu *= value;
        }
        else{
            cout << "error bad operators in input";
            return 1;
        }
    }
}
