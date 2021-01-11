#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//DECLARATIONS
void calculate(string a, vector<string> &vec1, vector<int> &vec2);
inline int add(int a, int b){ return a+b;}
int search(string, vector<string>&);
void assign(int, int, vector<int>&);


int main(){

    vector<string> variable_names;
    vector<int> variable_values;


    stringstream stream;
    string input_string;
    ifstream InputFile("deneme.inp");
    ofstream TempFile("temp.inp");

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
        calculate(input_string, variable_names, variable_values);
        }
    system("PAUSE");
}

void calculate(string a, vector<string> &vec1, vector<int> &vec2){
    
    ofstream OutputFile("deneme.out");
    
    if(a.find('=') != string::npos){

        string left_side = a.substr(0, a.find('+'));
        string right_side = a.substr(a.find('=') + 1, a.length()-1);
        //created streams to turn strings into integer in places necessary
        stringstream left_stream;
        left_stream.clear();
        stringstream right_stream;
        right_stream.clear();

        if(search(left_side, vec1) == -1){//assign left side of string as a variable if it does not already exist
            vec1.push_back(left_side);
        }

        if(right_side.find('+') != string::npos){
            string left_of_plus = right_side.substr(0, right_side.find('+'));//separate the values at left and right of the '+'
            string right_of_plus =  right_side.substr(right_side.find('+') + 1, right_side.length()-1);

            int index_left_of_plus = search(left_of_plus, vec1);
            int index_right_of_plus = search(right_of_plus, vec1);

            cout<<left_of_plus<<endl;
            cout<<right_of_plus<<endl;
            cout<<index_left_of_plus<<endl;
            cout<<index_right_of_plus<<endl;
           /* if(index_left_of_plus != -1 && index_right_of_plus != -1){
                vec2[search(right_side, vec1)] = add(vec2[index_left_of_plus], vec2[index_right_of_plus]);
            }
            else if(index_left_of_plus == -1 && index_right_of_plus != -1){
                vec2[search(right_side, vec1)] = add(stoi(left_of_plus), vec2[index_right_of_plus]);
            }
            else if(index_left_of_plus!= -1 && index_right_of_plus == -1){
                vec2[search(right_side, vec1)] = add(vec2[index_left_of_plus], stoi(right_of_plus));
            }
            else{
                vec2[search(right_side, vec1)] = add(stoi(left_of_plus), stoi(right_of_plus));
            }*/
        }
    }

    if(a.find("OUT") != string::npos){
        string output_str = a.substr(a.find("OUT") + 3, a.length()-1);
        cout<<output_str;
        OutputFile<<output_str<<endl;
    }

    OutputFile.close();
}

void assign(int index, int value, vector<int>& vec){
    vec[index] = value;
}

int search(string a, vector<string> &vec){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i]==a){ 
            return i;
        }
    }
    return -1;
}