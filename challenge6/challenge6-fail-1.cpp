#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>

using namespace std;
using namespace std::filesystem;
//DECLARATIONS
void calculate(string, string, vector<string>&, vector<double>&, vector<bool>&) ;
int search(string, vector<string>&);
bool is_integer(double);
int double_to_int(double);
bool is_variable(string);
//math functions
string add(string, vector<string>&, vector<double>&,  vector<bool>&);
string substract(string, vector<string>&, vector<double>&, vector<bool>&);
string multiply(string, vector<string>&, vector<double> &, vector<bool>&);
string divide(string , vector<string>&, vector<double>&, vector<bool>&);
//function for detect precedense with paranthesis
string paranthesis(string , vector<string>&, vector<double>&, vector<bool>&);

int main(){

    path p(".\\");

    vector<string> variable_names;
    vector<double> variable_values;
    vector<bool> is_double;

    stringstream stream;
    string input_string;

    ifstream InputFile;
    ofstream TempFile;

    if(is_directory(p)){
        for(const auto& entry : directory_iterator(p)){
            if (!is_directory(entry))//checking if entry is a file
            {
                if(entry.path().extension() == ".inp"){//checking if extension of file is .inp
                    
                    InputFile.open(entry.path().filename());//opening file
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

                    TempFile.close();

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
                        calculate(filename, input_string, variable_names, variable_values, is_double);
                    }
                    
                    InputFile.close();
                    variable_names.clear();
                    variable_values.clear();
                    is_double.clear();

                    remove("temp.inp");
                }
            }
            
        }
    }
    system("PAUSE");
}


void calculate(string filename, string input, vector<string>& name_vec, vector<double>& value_vec, vector<bool> &is_double){
    
    ofstream OutputFile(filename);
    stringstream convert;
    double value;
    string left_side;
    string right_side;

   
    if(input.find('=') != string::npos){

        left_side = input.substr(0, input.find('='));
        right_side = input.substr(input.find('=') + 1);

        while(right_side.find('(') != string::npos || right_side.find('+') != string::npos ||
            right_side.find('-') != string::npos || right_side.find('*') != string::npos ||
            right_side.find('/') != string::npos){

            if(right_side.find('(') != string::npos){
                right_side = paranthesis(right_side, name_vec, value_vec, is_double);
            }
            else if(right_side.find('*') != string::npos){
                right_side = multiply(right_side, name_vec, value_vec, is_double);
            }
            else if(right_side.find('/') != string::npos){
                right_side = divide(right_side, name_vec, value_vec, is_double);
            }
            else if(right_side.find('+') != string::npos){
                right_side = add(right_side, name_vec, value_vec, is_double);
            }
            else if(right_side.find('-') != string::npos){
                right_side =substract(right_side, name_vec, value_vec, is_double);
            }else{
                break;
            }
        }
            //convert right_side string to a double
            for(int i = 0; i< right_side.size(); i++){
                if(right_side[i] >='0' && right_side[i] <='9'){
                    convert.str(right_side);
                    convert>>value;
                    convert.clear();
                }
            }
            //create variable if does not exist
            if(search(left_side, name_vec) == -1){
                name_vec.push_back(left_side);
                value_vec.push_back(value);
                //determine if input is double
                if(right_side.find('.') != string::npos){
                    is_double.push_back(true);
                }else{
                    is_double.push_back(false);
                }
            }else{
                value_vec[search(left_side, name_vec)] = value;
                if(right_side.find('.') != string::npos){
                    is_double[search(left_side, name_vec)] = true;
                }else{
                    is_double[search(left_side, name_vec)] = false;
                }
            }


            /*for(int i=0; i<name_vec.size(); i++){
                cout<<"vec ["<<i<<"]"<<"  "<<name_vec[i]<<":  "<<value_vec[i]<<"  "<<is_double[i]<<endl;
            }*/
        
    }
    if(input.find("OUT") != string::npos){

        int variable_index = search(input.substr(input.find("OUT") + 3), name_vec);
        auto to_print = value_vec[variable_index];

        cout<<filename<<" "<<to_print<<endl;
        OutputFile<<to_print<<endl;

    }


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

string paranthesis(string input, vector<string> &name_vec, vector<double> &value_vec,  vector<bool>& is_double){
    
    int first_index = input.find('(');
    int last_index = input.find(')');
    int length = last_index - first_index + 1;
    string ready = input.substr(first_index + 1, length - 2);
    
    while(ready.find('(') != string::npos || ready.find('+') != string::npos ||
        ready.find('-') != string::npos || ready.find('*') != string::npos ||
            ready.find('/') != string::npos){

        if(ready.find('(') != string::npos){
            ready = paranthesis(ready, name_vec, value_vec, is_double);
        }
         else if(ready.find('*') != string::npos){
            ready = multiply(ready, name_vec, value_vec, is_double);
            }
         else if(ready.find('/') != string::npos){
            ready = divide(ready, name_vec, value_vec, is_double);
        }
        else if(ready.find('+') != string::npos){
            ready = add(ready, name_vec, value_vec, is_double);
        }
        else if(ready.find('-') != string::npos){
            ready =substract(ready, name_vec, value_vec, is_double);
        }else{
                break;
        }
    }

    //modify the input string
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;


}

string add(string input, vector<string> &name_vec, vector<double> &value_vec,  vector<bool>& is_double){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('+');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0.0; int sumi;
    int first_index;
    int last_index;

    //getting right side of '+'
    for(int i = index + 1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '+'
    for(int i = index-1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }
    //check if left is a variable. if it is, get it's value. if not, read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
        
    }

    //check if right is a variable. if it is, get it's value. if not, read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        
        convert.str(right_str);
        
        convert >> right_value;
        

    }

    //calculate
    sum = left_value + right_value;



    if(search(left_str, name_vec) != -1 || search(right_str, name_vec) != -1){
        if(is_double[search(left_str, name_vec)] || is_double[search(right_str, name_vec)]){
            //turn sum into a string
            ready.clear();
            convert.clear();
            convert<<sum;
            convert>>ready;
        }
        else{
            ready.clear();
            sumi = sum;
            //turn sum into a string
            convert.clear();
            convert<<sumi;

        }
    }else{
            ready.clear();
            convert.clear();
            convert<<sum;
    }
    //modify the input string
    int length = last_index - first_index + 1;
    
    input.erase(first_index, length);
    input.insert(first_index, convert.str());

     return input;
    
}

string substract(string input, vector<string> &name_vec, vector<double> &value_vec,  vector<bool>& is_double){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('-');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0.0; int sumi;
    int first_index;
    int last_index;

    //getting right side of '-'
    for(int i = index + 1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '-'
    for(int i = index-1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }
    //check if left is a variable. if it is, get it's value. if not, read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not, read the number
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

    if(search(left_str, name_vec) != -1 || search(right_str, name_vec) != -1){
        if(is_double[search(left_str, name_vec)] || is_double[search(right_str, name_vec)]){
            //turn sum into a string
            convert.clear();
            convert<<sum;
            convert>>ready;
        }
        else{
            sumi = sum;
            //turn sum into a string
            convert.clear();
            convert<<sumi;
            convert>>ready;
        }
    }else{
            convert.clear();
            convert<<sum;
            convert>>ready;
    }

    //modify the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;

}


string multiply(string input, vector<string> &name_vec, vector<double> &value_vec,  vector<bool>& is_double){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('*');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0.0; int sumi;
    int first_index;
    int last_index;

    //getting right side of '+'
    for(int i = index + 1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '*'
    for(int i = index-1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }
    //check if left is a variable. if it is, get it's value. if not, read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not, read the number
    if(search(right_str, name_vec) != -1){
        
        int var_index = search(right_str, name_vec);
        right_value = value_vec[var_index];

    }else{

        convert.clear();
        convert.str(right_str);
        convert >> right_value;

    }

    //calculate
    sum = left_value * right_value;

    if(search(left_str, name_vec) != -1 || search(right_str, name_vec) != -1){
        if(is_double[search(left_str, name_vec)] || is_double[search(right_str, name_vec)]){
            //turn sum into a string
            convert.clear();
            convert<<sum;
            convert>>ready;
        }
        else{
            sumi = sum;
            //turn sum into a string
            convert.clear();
            convert<<sumi;
            convert>>ready;
        }
    }else{
            convert.clear();
            convert<<sum;
            convert>>ready;
    }

    //modify the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;

}


string divide(string input, vector<string> &name_vec, vector<double> &value_vec,  vector<bool>& is_double){

    stringstream convert;

    string temp;
    string left_str;
    string right_str;
    string ready;
    int index = input.find('/');

    double left_value = 0;
    double right_value = 0;
    auto sum = 0.0; int sumi;
    int first_index;
    int last_index;

    //getting right side of '/'
    for(int i = index + 1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i++){
        right_str.push_back(input[i]);
        last_index = i;
    }
    
    //getting left side of '/'
    for(int i = index-1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i--){
        temp.push_back(input[i]);
        first_index = i;
    }
    for(int i = temp.size()-1; i>=0; i--){
        left_str.push_back(temp[i]);
    }
    //check if left is a variable. if it is, get it's value. if not, read the number
    if(search(left_str, name_vec) != -1){

        int var_index = search(left_str, name_vec);
        left_value = value_vec[var_index];
 
    }else{

        convert.clear();
        convert.str(left_str);
        convert >> left_value;
    }

    //check if right is a variable. if it is, get it's value. if not, read the number
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

    if(search(left_str, name_vec) != -1 || search(right_str, name_vec) != -1){
        if(is_double[search(left_str, name_vec)] || is_double[search(right_str, name_vec)]){
            //turn sum into a string
            convert.clear();
            convert<<sum;
            convert>>ready;
        }
        else{
            sumi = sum;
            //turn sum into a string
            convert.clear();
            convert<<sumi;
            convert>>ready;
        }
    }else{
            convert.clear();
            convert<<sum;
            convert>>ready;
    }

    //modify the input string
    int length = last_index - first_index + 1;
    input.erase(first_index, length);
    input.insert(first_index, ready);

    return input;

}
