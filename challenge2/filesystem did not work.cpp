#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>

using namespace std;
namespace fs = std::filesystem;

void calculate(string, string, vector<string>&, vector<double>&);
int search(string, vector<string>&);
bool is_integer(double);
int double_to_int(double);
bool is_variable(string);

//math functions
string add(string);
string substract(string);
string multiply(string);
string divide(string);


int main(){

    fs::path p(".\\");

    vector<string> variable_names;
    vector<double> variable_values;

    stringstream stream;
    string input_string;

    ifstream InputFile;
    ofstream OutputFile;

    if(is_directory(p)){
        for(const auto& entry : fs::directory_iterator(p)){
            if (!fs::is_directory(entry))//checking if entry is a file
            {
                if(entry.path().extension() == ".inp"){//checking if extension of file is .inp
                    
                    InputFile.open(entry.path().filename());//opening file
                    OutputFile.open("temp.inp");//creating a temp.inp file that wil be used for erasing space(' ') characters

                    while(getline(InputFile, input_string)){//reading file line by line

                        string temp;

                        stream.clear();
                        stream.str(input_string);//putting input string in a string stream in order to erase spaces

                        while(stream >> temp){//putting contents of stream into another string
                            OutputFile<<temp;//writing contents of temp string into our temp file
                        }
                        OutputFile<<endl;

                    }

                    OutputFile.close();

                    //setting the name of output file
                    string filename = entry.path().stem().string();
                    string out = ".out";
                    for(int i = 0; i < out.size(); i++){
                        filename.push_back(out[i]);
                    }
                    cout<<filename;
                    //read from temp.inp which has same contens as our first file but wihout any space(' ') character
                    InputFile.close();
                    InputFile.open("temp.inp");
                    
                    while(getline(InputFile, input_string)){
                    //do all the calculations
                        calculate(filename, input_string, variable_names, variable_values);
                    }
                    
                    remove("temp.inp");
                }
            }
            
        }
    }

}


void calculate(string filename, string input, vector<string>& name_vec, vector<double>& value_vec){
    
    

}

bool is_integer(double a){
    
    int b = a;
    if(a-b == 0){
        return 1;
    }
    return 0;    

}

int double_to_int(double a){
    return a;
}

int search(string a, vector<string>& vec){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i]==a){ 
            return i;
        }
    }
    return -1;
}