#include "V_Cipher.h"
	//Empty constructor, just the A vector
	V_Cipher::V_Cipher(){
		A.push_back(.082);
		A.push_back(.015);
		A.push_back(.028);
		A.push_back(.043);
		A.push_back(.127);
		A.push_back(.022);
		A.push_back(.020);
		A.push_back(.061);
		A.push_back(.070);
		A.push_back(.002);
		A.push_back(.008);
		A.push_back(.040);
		A.push_back(.024);
		A.push_back(.067);
		A.push_back(.075);
		A.push_back(.019);
		A.push_back(.001);
		A.push_back(.060);
		A.push_back(.063);
		A.push_back(.091);
		A.push_back(.028);
		A.push_back(.010);
		A.push_back(.023);
		A.push_back(.001);
		A.push_back(.020);
		A.push_back(.001);
	}

	//A vector and given ciphertext constructor
	V_Cipher::V_Cipher(string c){
		ciphertext=c;
		A.push_back(.082);
		A.push_back(.015);
		A.push_back(.028);
		A.push_back(.043);
		A.push_back(.127);
		A.push_back(.022);
		A.push_back(.020);
		A.push_back(.061);
		A.push_back(.070);
		A.push_back(.002);
		A.push_back(.008);
		A.push_back(.040);
		A.push_back(.024);
		A.push_back(.067);
		A.push_back(.075);
		A.push_back(.019);
		A.push_back(.001);
		A.push_back(.060);
		A.push_back(.063);
		A.push_back(.091);
		A.push_back(.028);
		A.push_back(.010);
		A.push_back(.023);
		A.push_back(.001);
		A.push_back(.020);
		A.push_back(.001);
	}

	//Part1
	//compute the number of correlated points for 1<n<nMax shifts
	void V_Cipher::do_index_of_correlation(int nMax){
		for(int i=1; i<=nMax; i++){
			int n_match=0;

			for(int j=0; j<(ciphertext.length()-1)-i; j++){
				if(ciphertext[j]==ciphertext[j+i]){
					n_match+=1;
				}
			}
			indices[i]=n_match;
		}
	}
	//print the map readably
	void V_Cipher::print_index_results(int nMax){
		for(int i=1; i<=nMax; i++){
			cout << "For index " << i << " the number of coincidences is " << indices[i]<< endl;
		}
	}
	
	//Take the smallest instance of the largest correlation and suggest it as a potential key length to the user.
	void V_Cipher::suggest_key_length(int nMax){
		int myMax=0;
		vector<int> lengths;
		for(int i=1; i<=nMax; i++){
			if(indices[i]==myMax){
				lengths.push_back(i);
			}
			else if(indices[i] >myMax){
				lengths.clear();
				myMax=indices[i];
				lengths.push_back(i);
			}
		}
		cout << "The maximum number of coincidences, " << myMax << " occurs at " << lengths.size() << " indices, the smallest being, " << lengths.at(0) << " so, we suggest this as a key length" << endl;

	}

	//Part2
	//Set the private key length of the cipher for computation
	void V_Cipher::set_key_length(int n){
		key_len=n;
	}
	
	//Construct the modular buckets of ciphertext and place into a map
	void V_Cipher::make_buckets(){
		int iter;
		string temp;
		for(int i=0; i<key_len; i++){
			iter=0;
			temp="";
			while((iter*key_len+i)<ciphertext.length()){
				temp+=ciphertext[iter*key_len+i];
				iter+=1;
			}
			buckets[i+1]=temp;
		}
	}

	//Print the map of buckets in a readable form
	void V_Cipher::print_buckets(){
		for(int i=1; i<=key_len; i++){
			cout << "Bucket " << i << " is: " << buckets[i] << endl;
			cout << endl;
		}
	}

	//Part3
	//Perform the second method in Trappe and Washington
	void V_Cipher::do_second_method(){
		vector <vector<double> > W;
		vector<double> activeW;
		vector<double> tempA;
		vector<double> dots;
		double tempMax;
		int tempMaxIndex;
		
		//Get weight vector
		W=generate_w_vector();
		cout << endl;
		//Find the offset for each letter of the key
		for(int i=0; i<key_len; i++){
			tempMax=0;
			tempMaxIndex=0;
			activeW=W.at(i);
			//Compute all of the dots of A_i*A_j
			for(int j=0; j<26; j++){
				tempA=rotate_a_matrix(j);
				dots.push_back(dotMe(tempA, activeW));
			}
			//Find the maximum offset for each letter of the key and then compute the key from the rotation using ASCII char numeric values
			for(int m=0; m<dots.size(); m++){
				if(dots.at(m) > tempMax){
					tempMax=dots.at(m);
					tempMaxIndex=m;
				}
			}
			cout << "The maximum dot is " << tempMax << " corresponding to a rotation of " << tempMaxIndex << endl;
		       	key+=(char)(tempMaxIndex+65);
			dots.clear();
		}

	}

	//Print the key that we foud above
	void V_Cipher::print_key(){
	cout << "After performing Maximum Likelihood Decoding, we find the key to be, " << key << endl;
	}

	//Part4
	//Using the definition of the Viginere cipher and the computed key, we rotate all of the ciphertext to the plaintext
	void V_Cipher::decrypt(){
		char reducedC;
		char reducedK;
		char p;
		for(int i=0; i<ciphertext.length(); i++){
			reducedC=ciphertext[i]-65;
			reducedK=key[i%key.length()]-65;
			if((reducedC-reducedK)<0){
				p=26+(reducedC-reducedK)+65;
			}
			else{
				p=(reducedC-reducedK)+65;
			}
			plaintext+=p;
		}
	}

	//Print the plaintext to the user
	void V_Cipher::print_plaintext(){
		cout << "The decrypted plaintext is as follows:" << endl;
		cout << plaintext << endl;
	}
	
	//My simple function to compute A_j using mod 26 for the alphabet
	vector<double> V_Cipher::rotate_a_matrix(int j){
		vector<double> toReturn;
		for(int i=0; i<26; i++){
			if((i-j)<0){
				toReturn.push_back(A[26+(i-j)]);
			}
			else{
				toReturn.push_back(A[i-j]);
			}
		}
		return toReturn;
	}

	//Compute the weights of each letter frequency for each bucket of the cipher
	vector< vector<double> > V_Cipher::generate_w_vector(){
		vector< vector<int> > letterCounts;
		vector< vector<double> > W;
		vector<int> temp;
		vector<double> lilW;
		string activeBucket;
		int count;
		for(int i=1; i<=key_len; i++){
			activeBucket=buckets[i];
			for(int j=0; j<26; j++){
				count=0;
				for(int k=0; k<activeBucket.length(); k++){
					if(activeBucket[k]==('A'+j)){
						count+=1;
					}
				}
				temp.push_back(count);
			}
			letterCounts.push_back(temp);
			for(int f=0; f<temp.size(); f++){
				lilW.push_back(double(temp.at(f))/double(activeBucket.length()));
			}
			W.push_back(lilW);
			temp.clear();
			lilW.clear();

		}
		return W;

	}
	
	//My simple dot product function
	double V_Cipher::dotMe(vector<double> a, vector<double> b){
		double summer=0;
		for(int i=0; i<a.size(); i++){
			summer+=a.at(i)*b.at(i);
		}
		return summer;
	}
