#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <bitset>

using namespace std;

class Record{
	public:
		float eid;
		string name;
		string bio;
		float mid;
		int hash_value;
};

class Block{
	// float size = 5;
	public:
		int block_key0;
		int block_key1 = NULL;
		vector <Record> primary;
		vector <Record> *overflow_ptr=NULL;
};

class Bucket{
	public:
		Block* block;
		int block_key0;
		int block_key1 = NULL;
		int h_level;
}


class LinearHash{
	public:
		int num_entries = 0;
		int num_buckets = 0;
		int bucket_cap = 5;
		vector <Bucket> buckets;

	
};



int main(int argc, char *argv[]){
	//creation mode
	// if (argv[1] == "C"){
	// 	FILE * pFile;
	// 	  pFile = fopen ("Employees.csv","r");
	// 	  if (pFile!=NULL)
	// 	  {
	// 	    while(fscanf(pFile))
	// 	  }
	// }
	// //search mode
	// else if(argv[1] == 'L'){
	// 	target_id = stoi(argv[2])

	// }
	return 0;
}