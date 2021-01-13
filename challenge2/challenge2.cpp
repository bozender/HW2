#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>

using namespace std;
using namespace std::filesystem;
//DECLARATIONS
void calculate(string, string, vector<string>&, vector<double>&);
int search(string, vector<string>&);
bool is_integer(double);
int double_to_int(double);
bool is_variable(string);

//math functions
string add(string input, vector<string> &name_vec, vector<double> &value_vec);
string substract(string input, vector<string> &name_vec, vector<double> &value_vec);
string multiply(string input, vector<string> &name_vec, vector<double> &value_vec);
string divide(string input, vector<string> &name_vec, vector<double> &value_vec);


int main(){

    path p(".\\");

    vector<string> variable_names;
    vector<double> variable_values;

    stringstream stream;
    string input_string;

    ifstream InputFile;
    ofstream OutputFile;

    if(is_directory(p)){
        for(const auto& entry : directory_iterator(p)){
            if (!is_directory(entry))//checking if entry is a file
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
                    //read from temp.inp which has same contens as our first file but wihout any space(' ') character
                    InputFile.close();
                    InputFile.open("temp.inp");
                    
                    while(getline(InputFile, input_string)){
                    //do all the calculations
                        calculate(filename, input_string, variable_names, variable_values);
                    }
                    
                    InputFile.close();
                    remove("temp.inp");
                }
            }
            
        }
    }
    system("PAUSE");
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

string add(string input, vector<string> &name_vec, vector<double> &value_vec){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('+');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0;
    int first_index;
    int last_index;

    //getting right side of '+'
    for(int i = index + 1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '+'
    for(int i = index-1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }

    //check if left is a variable. if it is, get it's value. if not read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        convert.str(right_str);
        convert >> right_value;

    }

    //calculate
    sum = right_value + left_value;

    //check if sum is integer or double
    if(is_integer(sum)){
        sum = double_to_int(sum);
    }

    //turn sum into a string
    convert.clear();
    convert<<sum;
    convert>>ready;
    //modifi the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;

}

string substract(string input, vector<string> &name_vec, vector<double> &value_vec){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('-');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0;
    int first_index;
    int last_index;

    //getting right side of '-'
    for(int i = index + 1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '+'
    for(int i = index-1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }

    //check if left is a variable. if it is, get it's value. if not read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        convert.str(right_str);
        convert >> right_value;

    }

    //calculate
    sum = left_value - right_value;

    //check if sum is integer or double
    if(is_integer(sum)){
        sum = double_to_int(sum);
    }

    //turn sum into a string
    convert.clear();
    convert<<sum;
    convert>>ready;
    //modifi the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;
}

string multiply(string input, vector<string> &name_vec, vector<double> &value_vec){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('*');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0;
    int first_index;
    int last_index;

    //getting right side of '*'
    for(int i = index + 1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '*'
    for(int i = index-1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }

    //check if left is a variable. if it is, get it's value. if not read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        convert.str(right_str);
        convert >> right_value;

    }

    //calculate
    sum = right_value * left_value;

    //check if sum is integer or double
    if(is_integer(sum)){
        sum = double_to_int(sum);
    }

    //turn sum into a string
    convert.clear();
    convert<<sum;
    convert>>ready;
    //modifi the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;
}

string divide(string input, vector<string> &name_vec, vector<double> &value_vec){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('/');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0;
    int first_index;
    int last_index;

    //getting right side of '/'
    for(int i = index + 1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '/'
    for(int i = index-1; input[i] >=( int)'A' && input[i] <= (int)'Z' || input[i] >= '0' && input[i] <='9'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }

    //check if left is a variable. if it is, get it's value. if not read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        convert.str(right_str);
        convert >> right_value;

    }

    //calculate
    sum = left_value / right_value;

    //check if sum is integer or double
    if(is_integer(sum)){
        sum = double_to_int(sum);
    }

    //turn sum into a string
    convert.clear();
    convert<<sum;
    convert>>ready;
    //modifi the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;
}