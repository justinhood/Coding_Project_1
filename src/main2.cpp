//This is the code for part 2 of the challenge

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>


#include "V_Cipher.h"
using namespace std;

//Globals
V_Cipher c;
map <int, string> cipherFiles;
int cipherNum;
int nMax=16;
int keySelected;

int main(){
	ifstream inFile;
	string ctext;
	string temp;
	cipherFiles[1]="../Ciphertexts/ciphertext_1.txt";
	cipherFiles[2]="../Ciphertexts/ciphertext_2.txt";
	cipherFiles[3]="../Ciphertexts/ciphertext_3.txt";
	cipherFiles[4]="../Ciphertexts/ciphertext_4.txt";
	cipherFiles[5]="../Ciphertexts/ciphertext_5.txt";
	cipherFiles[6]="../Ciphertexts/ciphertext_6.txt";
	cipherFiles[7]="../Ciphertexts/ciphertext_7.txt";

	cout << "Input number of cipherFile" << endl;
	cin >> cipherNum;

	inFile.open(cipherFiles[cipherNum].c_str());

	if(!inFile){
		cout << "File error" << endl;
		return -1;	
	}
	while(!inFile.eof()){
		inFile >> temp;
		ctext+=temp;
	}

	inFile.close();
	//cout << ctext << endl;
	c=V_Cipher(ctext);
	c.do_index_of_correlation(nMax);
	c.print_index_results(nMax);
	c.suggest_key_length(nMax);
	cout << endl;
	cout << endl;
	cout << "What is your selected index of coincidence?" << endl;
	cin >> keySelected;
	c.set_key_length(keySelected);
	c.make_buckets();
	c.print_buckets();
	return 0;
}
