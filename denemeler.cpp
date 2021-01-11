#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){
    // Create a text string, which is used to output the text file
    string myText;
    stringstream stream;

    // Read from the text file
    ifstream MyReadFile("deneme.inp");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        // Output the text from the file,
        string ab;
        stream.clear();
        stream.str(myText);
        for(int i=0; stream >> ab; i++){
            cout<<ab<<endl
            ;
        }
    }

    // Close the file
    MyReadFile.close();
    system("PAUSE");
}