#include <fstream>
#include <iostream>
#include <string.h>
#include "ArgumentManager.h"
using namespace std;
//Variables
const char *pCharRemove = "1234567890+=!@#$%^&*()-_{[}]|;:<,>.?/~`";//These are characters that must be removed
ifstream inputfile;
ofstream outputfile;
int const MAX = 500, MAXC = 50;
char inputletter[MAX] /*file[MAXC]*/;
int n = 0, instances[MAX];
string words[MAX];

//This function removes the symbols and numbers
void RemoveChar(char *p, const char *pRemove) {
	int Remove[256] = { 0 };
	if (NULL == p || NULL == pRemove) {
		return;
	}
	//Empy all chars into bucket array
	while (*pRemove) {
		Remove[*pRemove++] = 1;
	}

	char *pDest = p;

	while (*p) {
		if (!Remove[*p]) {
			*pDest++ = *p;
		}
		p++;
	}
	*pDest = '\0';
}

//This functions converts the string into lowercase value
void ConvertCase(string &s) {
	for (size_t i = 0; i < s.length() ; i++) {
		s[i] = tolower(s[i]);
	}
}

	int main(int argc, char* argv[]) {

		if (argc < 2) {
			std::cerr << "Usage: topword inputfile=input.txt" << std::endl;
			return -1;
		}

		ArgumentManager am(argc, argv);
		const std::string input_file_name = am.get("inputfile");
		std::cout << "input file name is " << input_file_name << std::endl;

		inputfile.open(input_file_name.c_str());


		//The file is read by char and removes symbols and numbers
		while (inputfile >> inputletter) {

			RemoveChar(inputletter, pCharRemove);//Removing the symbols and numbers

			words[n] = inputletter;//Placing the char array into string array

			for (int i = 0; i < n + 1; i++)//Converting each string into lowercase form
				ConvertCase(words[i]);
		
			n++;//Counts up how many words the text file is made up of
		}

		inputfile.close(); //closed the input file
		outputfile.open("output.txt");
		/*for (int i = 0; i < n; i++) {  //this loop takes elements that has no value, just " " and moves the element to the back and shifts every other element forward
			if (words[i] == "") {
				for (int j = i; j < n; j++) 
					words[j] = words[j + 1];
			}
		}
		*/
		//variables
		string str = " ";
		int c = '\0';

		for (int i = 0; i < n; i++) { //this loop finds the most frequent word in the text file
			string temps = words[i];
			int tempc = 0;
			if (temps == " ") { //this loop makes sure that if an element has no value, it prints no value
				temps = " ";
				tempc = '\0';
			}
			for (int j = 0; j < n; j++)  //this loop counts up the number of instances for each word
				if (words[j] == temps) {
					tempc++;
				}
			if (tempc > c) {
				str = temps;
				c = tempc;
			}
		}
		
		if (c != '\0') {
			outputfile << str << ": " << c << endl; //prints the output in the "output.txt"
		}
		
		for (int i = 0; i < n; i++) { //this loop finds the most frequent word like the previous loop, and if the condition (same amount of frequency) meets, it prints the frequency in "output.txt"
			string temps = words[i];
			int tempc = 0;
			for (int j = 0; j < n; j++) {
				if (words[j] == temps) {
					tempc++;
					words[j] = " ";
				}
			}
			if (temps != str) {
				if (tempc == c)
					outputfile << temps << ": " << tempc << endl;
			}
		}
		outputfile.close(); //output file is closed
		cout << "Done! \n";

			return 0;
		}
	