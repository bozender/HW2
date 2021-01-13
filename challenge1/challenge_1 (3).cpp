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
    cout<<input_string;
    InputFile.close();
    InputFile.open("temp.inp");

    while(getline(InputFile, input_string)){
        calculate(input_string, variable_names, variable_values);
    }
    system("PAUSE");
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

void calculate(string a, vector<string> &vec1, vector<int> &vec2) {
    
    ofstream OutputFile("deneme.out");

    stringstream attend_stream;
    attend_stream.clear();

    if (a.find('=') != string::npos) {
        
        string left_side = a.substr(0, a.find('='));
        string right_side = a.substr(a.find('=') + 1);
        
        auto plus = right_side.find('+');
        auto minus = right_side.find('-'); 
        auto multiply = right_side.find('*'); 
        auto divide = right_side.find('/');

        //addition (a+b)
        if (plus != string::npos) {

            string lp = right_side.substr(0, plus); 
            string rp = right_side.substr(plus + 1); 
            int lv = -1, rv = -1;

            //check if the left of plus is numeric and attend it to a variable
            for (int i = 0; i < lp.length(); i++) {
                if (lp[i] >= (int)'0' && lp[i] <= (int)'9') {
                    attend_stream.str(lp); 
                    attend_stream >> lv; 
                    attend_stream.clear(); 
                    break;
                }
            }
            //check if the rigt of plus is numeric and attend it to a variable
            for (int i = 0; i < rp.length(); i++) {
                if (rp[i] >= (int)'0' && rp[i] <= (int)'9') {
                    attend_stream.str(rp); 
                    attend_stream >> rv;
                    attend_stream.clear(); 
                    break;
                }
            }

            //check if lv and rv is set, this is to avoid numerical inputs
            if (lv == -1) {
                int pos = search(lp, vec1);
                lv = (pos == -1) ? -1 : vec2[pos];
            }
            if (rv == -1) {
                int pos = search(rp, vec1);
                rv = (pos == -1) ? -1 : vec2[pos];
            }
            //do the computation and assignment
            if(search(left_side, vec1)==-1){
                vec1.push_back(left_side);
            }
            else{
                assign(search(left_side, vec1), lv + rv, vec2);
            }
        }
        else{
            int value;
            vec1.push_back(left_side);
            
            for(int i = 0; i< right_side.size(); i++){
                if(right_side[i] >= (int)'0' && right_side[i] <= (int)'9'){
                    attend_stream.str(right_side);
                    attend_stream>>value;
                    attend_stream.clear();
                }
            }
            vec2.push_back(value);
        }

    }
    if (a.find("OUT") != string::npos) {
        string temp = a.substr(a.find("OUT")+3);
        int value_to_print = vec2[search(temp, vec1)];
        if(value_to_print == 31){
            cout<<"sj"<<endl;
            OutputFile<<value_to_print<<endl;
        }
        else{
            cout<<value_to_print<<endl;
            OutputFile<<value_to_print<<endl;
        }

    }
}