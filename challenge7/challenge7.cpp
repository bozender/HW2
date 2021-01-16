#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

using namespace std;
using namespace std::filesystem;
//DECLARATIONS
void calculate(string, vector<string>&, vector<double>&, vector<bool>&) ;
void decide(string, vector<string>&, vector<double>&, vector<bool>&);
void print_out(string, string, vector<string>&, vector<double>&);
int search(string, vector<string>&);
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
                        if(input_string.find("=") != string::npos){
                            if(input_string.find("IF") != string::npos){
                                decide(input_string, variable_names, variable_values, is_double);
                            }
                            else if(input_string.find("LOOP") != string::npos){
                                  
                            }
                            else{
                                calculate(input_string, variable_names, variable_values, is_double);
                            }

                            if(input_string.find("OUT") != string::npos){
                                print_out(filename, input_string, variable_names, variable_values);
                            }                            
                        }
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


void calculate(string input, vector<string>& name_vec, vector<double>& value_vec, vector<bool> &is_double){
    
    stringstream convert;
    double value;
    string left_side;
    string right_side;


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
    //if right side is an existing variable, get it's value. if right side is numerical, convert it to a double
    if(search(right_side, name_vec) != -1){
        value = value_vec[search(right_side, name_vec)];
    }
    else{
        for(int i = 0; i< right_side.size(); i++){
            convert.clear();
            convert.str(right_side);
            convert>>value;
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
}

void decide(string input, vector<string>& name_vec, vector<double>& value_vec, vector<bool>& is_double){

    if(input.find('(') != string::npos){
        input = paranthesis(input, name_vec, value_vec, is_double);
    }

    bool condition;
    
    string temp;
    string condition_left;
    string condition_right;
    string condition_str = input.substr(input.find("IF") + 2, input.find("THEN")- input.find("IF") - 3);
    string then_str = input.substr(input.find("THEN") + 4, input.find("ELSE") - input.find("THEN")  -5);
    string else_str = input.substr(input.find("ELSE") + 4);

    //getting right side of condition
    for(int i = 0; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i++){
        condition_right.push_back(input[i]);
    }  
    //getting left side of condition
    for(int i = condition_str.size()-1; (input[i] >='A' && input[i] <='Z') || (input[i] >='0' && input[i] <='9') || input[i]=='.'; i--){
        temp.push_back(input[i]);
    }
    for(int i = temp.size()-1; i>=0; i--){
        condition_left.push_back(temp[i]);
    }
    
    if(condition_str.find("<") != string::npos){
        if(condition_str.find("=") != string::npos){
            if(value_vec[search(condition_left, name_vec)] <= value_vec[search(condition_left, name_vec)]){
                condition = true;
            }
            else{
                condition = false;
            }
        }
        else{
            if(value_vec[search(condition_left, name_vec)] < value_vec[search(condition_left, name_vec)]){
                condition = true;
            }
            else{
                condition = false;
            }
        }
    }

    if(condition_str.find(">") != string::npos){
        if(condition_str.find("=") != string::npos){
            if(value_vec[search(condition_left, name_vec)] >= value_vec[search(condition_left, name_vec)]){
                condition = true;
            }
            else{
                condition = false;
            }
        }
        else{
            if(value_vec[search(condition_left, name_vec)] > value_vec[search(condition_left, name_vec)]){
                condition = true;
            }
            else{
                condition = false;
            }
        }
    }

    if(condition_str.find("==") != string::npos){
        if(value_vec[search(condition_left, name_vec)] == value_vec[search(condition_left, name_vec)]){
            condition = true;
        }
        else{
            condition = false;
        }
    }

    if(condition){
        calculate(then_str, name_vec, value_vec, is_double);
    }
    else{
        calculate(else_str, name_vec, value_vec, is_double);
    }

}

void print_out(string filename, string input, vector<string>& name_vec, vector<double>& value_vec){
    
    ofstream OutputFile(filename);

    int variable_index = search(input.substr(input.find("OUT") + 3), name_vec);
    auto to_print = value_vec[variable_index];

    cout<<filename<<" "<<to_print<<endl;
    OutputFile<<to_print<<endl;
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
        }
        else{
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



    if( (search(left_str, name_vec) != -1 && is_double[search(left_str, name_vec)]) || (search(right_str, name_vec) != -1 && is_double[search(right_str, name_vec)]) ){
        
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

    if( (search(left_str, name_vec) != -1 && is_double[search(left_str, name_vec)]) || (search(right_str, name_vec) != -1 && is_double[search(right_str, name_vec)]) ){
        
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
    //modify the input string
    int length = last_index - first_index + 1;
    
    input.erase(first_index, length);
    input.insert(first_index, convert.str());

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

    //getting right side of '*'
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

    if( (search(left_str, name_vec) != -1 && is_double[search(left_str, name_vec)]) || (search(right_str, name_vec) != -1 && is_double[search(right_str, name_vec)]) ){
        
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

    //modify the input string
    int length = last_index - first_index + 1;
    
    input.erase(first_index, length);
    input.insert(first_index, convert.str());

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

    if( (search(left_str, name_vec) != -1 && is_double[search(left_str, name_vec)]) || (search(right_str, name_vec) != -1 && is_double[search(right_str, name_vec)]) ){
        
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
    //modify the input string
    int length = last_index - first_index + 1;
    
    input.erase(first_index, length);
    input.insert(first_index, convert.str());

    return input;

}
