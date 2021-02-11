#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <bitset>

using namespace std;

int h_lvl = 2;
int h1_lvl = h_lvl + 1;
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

class Buckets{
	public:
		Block* block;
		string block_key0;
		//remember to change this
		string block_key1 = NULL;
		int h_level;
		bool h_plus = false;

};


class LinearHash{
	public:
		int num_entries = 0;
		int num_buckets = 0;
		int bucket_cap = 5;
		int N = 4;
		int Next = 0;

		vector <Buckets> buckets;

		//pass an int id to get a string in bit format
		string getHash(int id){
			string key = bitset<32>(id).to_string();
			return key;
		}
		//give a full id and how many end bits you want 
		string levelKey(string fullkey, int bit_ct){
			int length = fullkey.length();
			return fullkey.substr(length-bit_ct);
		}
		void split(){
			//addBucket based off next
			addBucket();
						// redistribute
			Next++;
			if(Next > N){
				Next = 0;
				N *= 2;
				h_lvl++;
			}

		}

		void addBucket(){
			key = buckets[i].block_key0;
			buckets[i].block_key1 = "0" + key;
			buckets.push_back(Buckets());
			num_buckets++;
			int size = buckets.size();
			buckets[size-1].block_key0 = key;
			buckets[size-1].block_key1 = "1" + key;			
		}
		void newLevel(){
			for (int i =0; i <= num_buckets; i++){
				buckets[i].h_plus = false;
			}
		}

	
};



int main(int argc, char *argv[]){
	LinearHash temp;
	temp.buckets.push_back(Buckets());
	temp.buckets[0].block_key0 = "00";
	temp.buckets.push_back(Buckets());
	temp.buckets[1].block_key0 = "01";
	temp.buckets.push_back(Buckets());
	temp.buckets[2].block_key0 = "10";
	temp.buckets.push_back(Buckets());
	temp.buckets[3].block_key0 = "11";
	temp.addBucket();
	//testing getHas
	// string key = temp.getHash(100);
	// cout << key<< endl;
	// cout << key[0] << endl;

	//testing levleKey
	// cout << temp.levelKey(key, 4);


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