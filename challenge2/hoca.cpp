#include <iostream>
#include <fstream>
#include <filesystem>  //https://en.cppreference.com/w/cpp/filesystem
using namespace std;
using namespace std::filesystem;

int main()
{
	try {
		path p(".\\"); //gets the current path.

		if (!is_directory(p)) {
			cout << "!not in a accessable directory!" << endl;
			return 1;
		}
		cout << "Current Path:" << absolute(p) << endl;
		cout << "--------------------------------------" << endl;
		cout << "Text (.txt) files in this folder" << endl;
		cout << "--------------------------------------" << endl;
		for (const directory_entry& dre : directory_iterator(p))
		{
			if (!is_directory(dre))    // is a file
			{
				if (dre.path().extension() == ".txt")
				{
					cout << dre.path().filename() << endl;
				}
			}
		}
	}
	catch (const filesystem_error& ex)
	{
		cout << ex.what() << endl;
	}
    system("PAUSE");
}