#include <iostream>
#include <fstream>
#include <ctime>
#include "structure.h"
using namespace std;


void shiftString(string& find);
void clearPunc(string* str, string* temp);
void createStopWordArray(string* stopWordArray, int* intArr);
string makeLower(string str);
int isPunc(const string& str);
bool isNum(const string& str);
bool isStopWord(const string& str, const string* stopWordArray, const int* arr);


int main() {

	clock_t start, stop;
	float totalTime;
	start = clock();
	
	// initialize the top 10 word array
	for (int i = 0; i < 10; i++) 
		topTen[i] = new Word("abc");
	
	//This part of the code creates stop word array and allocates it in the heap
	string* stopWordArray = new string[571];
	int intArr[27] = { 0 };
	createStopWordArray(stopWordArray, intArr);


	string fileName = "Documents/reut2-000.sgm";
	myStructure strSturct;

	for (int q = 0; q < 22; q++) {

		//File name modifications
		fileName[18] = 48 + (q % 10);
		fileName[17] = 48 + int(q / 10);

		ifstream file(fileName);
		
		if (file.is_open()) {

			while (!file.eof()) {

				string find = "abcdef";
				int m = 1;

				shiftString(find);

				//Finds <BODY> keyword in the files
				while (m != -1) {

					m = file.get();
					char next = m;
					shiftString(find);

					if (m != -1)
						find[find.size() - 1] = next;

					if (find == "<BODY>") {
						break;
					}
				}


				string wrd;

				while (file >> wrd) {

					string temp = "0";

					//Searching for ending command
					if (wrd == "&#3;</BODY></TEXT>") {
						break;
					}

					//Checks string whether is number or not
					if (isNum(wrd)) {
						continue;
					}

					//Makes lower case
					wrd = makeLower(wrd);

					//Removes all punctuation marks from word
					clearPunc(&wrd, &temp);

					//Checks  stop words, if not adds to structure
					if (wrd == "") {
						continue;
					}
					if (temp != "0") {
						if (!isStopWord(temp, stopWordArray, intArr) && !strSturct.isExist(temp)) {
							strSturct.insert(temp);
						}
					}
					if (!isStopWord(wrd, stopWordArray, intArr) && !strSturct.isExist(wrd)) {
						strSturct.insert(wrd);
					}
				}
			}

		}
		else {
			cout << "File is not open\n";
		}

		file.close();
	}
	strSturct.traverse();

	for (int i = 9; i >= 0; i--) 
		cout << topTen[i]->getWord() << "\t" << topTen[i]->getCount() << "\n";
	
	stop = clock();
	totalTime = (stop - start) / (float)CLOCKS_PER_SEC;

	cout << "Total Time Elapsed: " << totalTime << " second";
	

	return 0;
}


void shiftString(string& find) {

	for (size_t i = 1; i < find.size(); i++) {
		find[i - 1] = find[i];
	}
}


string makeLower(string str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] < 91 && 64 < str[i]) {
			str[i] = str[i] + 32;
		}
	}
	return str;
}


bool isNum(const string& str) {

	for (size_t i = 0; i < str.size(); i++) {

		if (str[i] >= '0' && str[i] <= '9')
			return true;
	}

	return false;
}


int isPunc(const string& str) {
	int t;

	for (size_t i = str.size() - 1; i < 2 * str.size() - 1; i++) {
		t = i % str.size();

		if ((str[t] < 65 || str[t] > 90) && (str[t] < 97 || str[t] > 122))
			return t;
	}

	return -1;
}


void clearPunc(string* str, string* temp) {
	int pos = isPunc(*str);

	while (pos != -1) {

		if (pos == str->size() - 1)
		{
			str->erase(str->size() - 1);
		}
		else if (pos == 0) {
			str->erase(0, 1);
		}
		else
		{
			*temp = str->substr(0, pos);
			str->erase(0, pos);
		}

		pos = isPunc(*str);
	}
}


void createStopWordArray(string* stopWordArray, int* intArr) {
	ifstream stopWordFile("stopwords.txt");
	int index = 0, intIndex = 1, prevLine = 1;
	char ch = 'a';

	while (!stopWordFile.eof()) {
		stopWordFile >> stopWordArray[index++];

		if (ch != stopWordArray[index - 1][0]) {
			intArr[intIndex++] = index - 1;
			ch = stopWordArray[index - 1][0];
		}
	}

	intArr[intIndex] = index;
	stopWordFile.close();
}


bool isStopWord(const string& str, const string* stopWordArray, const int* arr) {
	bool isStopWord = false;
	int range = arr[str[0] - 96];

	for (int index = arr[str[0] - 97]; index < range; index++) {

		if (str == stopWordArray[index]) {
			isStopWord = true;
			break;
		}
	}
	return isStopWord;
}

//Mehmet Emre Astarcýoðlu, Mehmet Ali Kýsacýk, Mert Oðuz
