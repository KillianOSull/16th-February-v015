#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t unlock_prbs()
{   
    static uint32_t shift_register=0xa551199; // "random" seed value
	int b1 = 0;
	int b2 = 0;
	if (shift_register & (1 << 30))
	{
		b1 = 1;
	}
	if (shift_register & (1 << 27))
	{
		b2 = 1;
	}
	
	shift_register=shift_register << 1;
	shift_register=shift_register | (b1 ^ b2);
	shift_register = shift_register & 0x7fffffff;
    return shift_register ; // return 31 LSB's 
}

int main()
{

	uint32_t unlock_randnum;
	int counter_int;
	string counter_str;
	string compare_code;
	string unlock_randnum_str;
	
	stringstream ss;
	
	fstream ctr_file;
	ctr_file.open("unlock_counter.txt", ios::in);
	
	if (ctr_file.is_open()) {
		getline(ctr_file, counter_str);
		ss.str("");
		ss.clear();
		ss << counter_str;
		ss >> counter_int;
		cout << "the counter value in the file is: " << counter_int << endl;
	}
	else {														
		cout << "Cannot Locate file" << endl;				
		exit(0);											
	}														
	ctr_file.close();
	
	for (int i = 0; i < counter_int; i++){
		unlock_randnum = unlock_prbs();
	}
	
	ss.str("");
	ss.clear();
	ss << hex << unlock_randnum;
	ss >> unlock_randnum_str;
	
	printf("Unlock Code: %x\n", unlock_randnum);
	fstream code_file;
	code_file.open("unlock_code.txt", ios::in);
	if (code_file.is_open()) {
		getline(code_file, compare_code);
		cout << "the code in the file is: " << compare_code << endl;
	}
	else {														
		cout << "Cannot Locate file" << endl;				
		exit(0);											
	}														
	code_file.close();
	
	fstream match_file;
	match_file.open("unlock_match.txt", ios::out);
	
	
	if (compare_code == unlock_randnum_str){
		match_file << "1";
	}
	else {
		match_file << "0";
	}
	cout << "End of programme" << endl;
	return 0;	
	
}






	// * * * * * * * * * * * * * NOTES * * * * * * * * * * * *  //
	// instead of writing the code to file, compare codes using //
	// C++ program. this way NodeJS does not need to compare    //
	// strings... this process will be easier		    //
	
	
	//ctr_file << hex << unlock_randnum; //for writing the hex code to a file
		
		
