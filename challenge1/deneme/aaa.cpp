#include <iostream>
#include <sstream>
using namespace std;
int func(int a){
    int temp;
    int sum = 0;
    stringstream convert
    ;string b;
    convert.clear();
    convert<<a;
    convert>>b;
    convert.clear()
    ;convert.str(b);
    while(convert>>temp){
        sum+= temp;
    }
    return sum;
}
//Ex:    int a = func(123) ;   >   a is equal to 6 after  this.
int main(){
    int a = func(123) ;
    cout<<a<<endl;
    system("PAUSE");
}