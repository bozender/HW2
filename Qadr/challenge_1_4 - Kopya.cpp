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

void calculate(string a, vector<string> &vec1, vector<int> &vec2) {                                                                 cout<<"debugger";
    cout<<"debugger";
    ofstream OutputFile("deneme.out");cout<<"debugger";
cout<<"debugger";
    stringstream attend_stream;cout<<"debugger";
    attend_stream.clear();cout<<"debugger";
cout<<"debugger";
    if (a.find('=') != string::npos) {cout<<"debugger";
        cout<<"debugger";
        string left_side = a.substr(0, a.find('='));cout<<"debugger";
        string right_side = a.substr(a.find('=') + 1);cout<<"debugger";
        cout<<"debugger";
        auto plus = right_side.find('+');cout<<"debugger";
        auto minus = right_side.find('-'); cout<<"debugger";
        auto multiply = right_side.find('*'); cout<<"debugger";
        auto divide = right_side.find('/');cout<<"debugger";
cout<<"debugger";
        //addition (a+b)cout<<"debugger";
        if (plus != string::npos) {cout<<"debugger";
cout<<"debugger";
            string lp = right_side.substr(0, plus);                                 cout<<"debugger";
            string rp = right_side.substr(plus + 1);cout<<"debugger";
            int lv = -1, rv = -1;cout<<"debugger";
cout<<"debugger";
            //check if the left of plus is numeric and attend it to a variablecout<<"debugger";
            for (int i = 0; i < lp.length(); i++) {cout<<"debugger";
                if (lp[i] >= (int)'0' && lp[i] <= (int)'9') {cout<<"debugger";
                    attend_stream.str(lp); cout<<"debugger";
                    attend_stream >> lv; cout<<"debugger";
                    attend_stream.clear(); cout<<"debugger";
                    break;cout<<"debugger";
                }cout<<"debugger";
            }cout<<"debugger";
            //check if the rigt of plus is numeric and attend it to a variablecout<<"debugger";
            for (int i = 0; i < rp.length(); i++) {cout<<"debugger";
                if (rp[i] >= (int)'0' && rp[i] <= (int)'9') {cout<<"debugger";
                    attend_stream.str(rp); cout<<"debugger";
                    attend_stream >> rv;cout<<"debugger";
                    attend_stream.clear(); cout<<"debugger";
                    break;cout<<"debugger";
                }cout<<"debugger";
            }cout<<"debugger";
cout<<"debugger";
            //check if lv and rv is set, this is to avoid numerical inputscout<<"debugger";
            if (lv == -1) {cout<<"debugger";
                int pos = search(lp, vec1);cout<<"debugger";
                lv = (pos == -1) ? -1 : vec2[pos];cout<<"debugger";
            }cout<<"debugger";
            if (rv == -1) {cout<<"debugger";
                int pos = search(rp, vec1);cout<<"debugger";
                rv = (pos == -1) ? -1 : vec2[pos];cout<<"debugger";
            }cout<<"debugger";
            //do the computation and assignmentcout<<"debugger";
            if(search(left_side, vec1)==-1){cout<<"debugger";
                vec1.push_back(left_side);cout<<"debugger";
            }else{cout<<"debugger";
                assign(search(left_side, vec1), lv + rv, vec2);cout<<"debugger";
            }cout<<"debugger";
        }cout<<"debugger";
        else{
            int value;cout<<"debugger";
            vec1.push_back(left_side);cout<<"debugger";
            
            for(int i = 0; i< right_side.size(); i++){cout<<"debugger";
                if(right_side[i] >= (int)'0' && right_side[i] <= (int)'9'){cout<<"debugger";
                    attend_stream.str(right_side);cout<<"debugger";
                    attend_stream>>value;cout<<"debugger";
                    attend_stream.clear();cout<<"debugger";
                }cout<<"debugger";
            }
            vec2.push_back(value);cout<<"debugger";
        }
    }
    if (a.find("OUT") != string::npos) {cout<<"debugger";
        string temp = a.substr(a.find("OUT")+3);cout<<"debugger";
        int value_to_print = vec2[search(temp, vec1)];cout<<"debugger";
        if(value_to_print == 31){cout<<"debugger";
            cout<<"sj"<<endl;cout<<"debugger";
            OutputFile<<value_to_print<<endl;cout<<"debugger";
        }cout<<"debugger";
        else{
            cout<<value_to_print<<endl;cout<<"debugger";
            OutputFile<<value_to_print<<endl;cout<<"debugger";
        }cout<<"debugger";

}