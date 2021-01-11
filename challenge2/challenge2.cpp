#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

using namespace std;
using namespace std::filesystem;

void calculate(string, vector<string>&, vector<double>&);
int search(string, vector<string>&);
bool is_integer(double);
int double_to_int(double);

int main(){

    path p(".\\");

    vector<string> variable_names;
    vector<double> variable_values;

    stringstream stream;
    string input_string;

    ifstream InputFile;
    ofstream TempFile;

    if(is_directory(p)){
        for(const auto& entry : directory_iterator(p)){
            if (!is_directory(entry))//checking if entry is a file
            {
                if(entry.path().extension() == ".inp"){//checking if extension of file is .inp
                    
                    InputFile.open(path().filename());//opening file
                    TempFile.open("temp.inp");//creating a temp.inp file that wil be used for erasing space(' ') characters

                    while(getline(InputFile, input_string)){//reading file line by line

                        string temp;

                        stream.clear();
                        stream.str(input_string);//putting input string in a string stream in order to erase spaces

                        while(stream >> temp){//putting contents of stream into another string
                            TempFile<<temp;//writing contents of temp string into our temp file
                        }
                        TempFile<<endl;

                    }
                    //reading from temp.inp which has same contens as our first file but wihout any space(' ') character
                    InputFile.close();
                    InputFile.open("temp.inp");

                    while(getline(InputFile, input_string)){
                        calculate(input_string, variable_names, variable_values);
                    }

                    system("PAUSE");

                }
            }
            
        }
    }

}


void calculate(string a, vector<string>& name_str, vector<double>& value_str){
    
}

int double_to_int(){

}