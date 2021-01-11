#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
// string:: find ve string::substr bak
using namespace std;

void calculate(ofstream, string, vector<string> &vec1, vector<int> &vec2);
void add(string, vector<string>&, vector<int>&);
int search(string, vector<string>&);
int search(string, vector<int>&);
void out(ofstream&, string, vector<string>&, vector<int>&);
int main(){

    vector<string> variable_names;
    vector<int> variable_values;

    stringstream stream;
    string input_string;
    ifstream InputFile("deneme.inp");
    ofstream TempFile("temp.inp"), OutputFile("deneme.out");

    while(getline(InputFile, input_string)){
        string temp;

        stream.clear();
        stream.str(input_string);

        while(stream >> temp){
            TempFile<<temp;
        }
        TempFile<<endl;
    }

    InputFile.close();
    InputFile.open("temp.inp");

    while(getline(InputFile, input_string)){
        calculate(OutputFile, input_string, variable_names, variable_values);
        }
    
    InputFile.close();
    OutputFile.close();

}

void calculate(ofstream &Output, string a, vector<string> &vec1, vector<int> &vec2){

    if(a.find('=') != string::npos){

        string left_side = a.substr(0,a.find('=')); //ISOLATING VARIABLE NAME
        string right_side;
        if(search(left_side, vec1)==-1){//CHECK IF VARIABLE EXIST
            vec1.push_back(left_side);//VARIABLE NAME ASSIGNMENT

            if(a.find('+') != string::npos){
                add(right_side, left_side, vec1, vec2);
            }
            else{ 
                right_side = a.substr(a.find('=')+1, a.length());
                vec2[search(left_side, vec1)] = stoi(right_side);

            }
        }        
    }
    if(a.find("OUT") != string::npos){
        out(Output, a, vec1, vec2);
    }
}

int search(string a, vector<string> &vec){
    for(auto i = 0; i < vec.size(); i++){
        if(vec[i]==a){ 
            return i;
        }
    }
    return -1;
}

void add(string a, vector<string>& vec1, vector<int>& vec2){
    string var1, var2;
    var1 = a.substr(0, a.find('+'));
    var2 = a.substr(a.find('+')+1, a.length());

     vec2[search(b, vec1)]= vec2[search(var1, vec2)] + vec2[search(var2, vec2)];
}

void out(ofstream File, string a, vector<string>& vec1, vector<int>& vec2){
    string temp = a.substr(a.find("OUT")+3, a.length());
    cout<<vec2[search(temp, vec1)];
    File<<vec2[search(temp, vec1)]<<endl;
}