/**@file V_Cipher.h
 @author Justin Hood
 @version 2.2
 @brief This is the header file for the V_Cipher class.
 @details All of the functions that are called for the various stages of this project are contained within this file, so as to protect data, and simplify the construction of the main functions.
 @date Friday February 23, 2018
 */
/*! \mainpage Coding Project 1
\section Introduction 
The code enclosed in this project is intended to be used to perform a maximum likelihood decoding attack on a piece of ciphertext that is encoded using a Vigenere Cipher.
\section Compilation
\subsection MAKEFILE
The code enclosed in this project contains a prewritten makefile that will compile the files into four different executables, as seen below. Given how the code is written, the execution of these files must be from the /src/ folder, as the ciphertext locations are hard coded relative to that location.
\subsection Stage1.exe
This executable will prompt the user for input about which ciphertext that is desired, and output the number of coincidences for each index in that text.
\subsection Stage2.exe
This executable will perform as stage1.exe, but will additionally prompt the user for what index/key length is desired and then compute the associated "buckets" of ciphertext.
\subsection Stage3.exe
This executable will function as stage2.exe, but will use the method outlined in Trappe and Washington to actually compute the key
\subsection Vigenere_decoder.exe
This executable will prompt the user for which ciphertext to use, and then ask for the key length. Then it will compute the key and display the decrypted plaintext.
*/
/*This code was working without any bugs to my knowledge*/


//Prevent sourcing errors
#pragma once

//Include section
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

//Class creator
class V_Cipher{
	//Public Variables
	public:
		V_Cipher();
		/**<
		 Empty Constructor for the V_Cipher Class.
		 */
		V_Cipher(string c);
		/**<
		 Nonempty Constructior for the V_Cipher Class.  This constructor allows for the class to be initialized with a ciphertext without needing the setter functions.
		 @param c This is a string that contains the ciphertext.
		 @pre
		 -# Starts with an uninitialized class
		 @post
		 -# Ends with a class instance with ciphertext defined.
		 */
		
		//Part1
		void do_index_of_correlation(int nMax);
		/**<
		 This function computes the number of correlations for each integer 1<n<nMax.
		 @return void
		 @param nMax The largest possible key length
		 @pre
		 -#The indices map is empty
		 @post
		 -#The indices map will be filled with shift length, correlation pairs.
		*/
		void print_index_results(int nMax);
		/**<
		 This function prints the indices map in a human readable format.
		 @return void
		 @param nMax The largest index from the map that we want to print.
		 */
		void suggest_key_length(int nMax);
		/**<This program takes the minimum high value, and suggests the potential key length to the user.
		 @return void
		 @param nMax The largest key length possible for comparison.
		 */
		//Part2
		void set_key_length(int n);
		/**<
		 This function takes user input and sets the ciphers key length.  This input will be found in the main function, as that is not practicle to partition to this file.
		 @return void
		 @param n The length of the key in characters that the user has decided upon.
		 */
		void make_buckets();
		/**<
		 This function uses the key length to generate the "buckets" of partitioned ciphertext.
		 @return void
		 @pre
		 -# The private map buckets is uninitialized
		 @post
		 -# The private map buckets is filled with the partitioned ciphertext based on the key length.
		 */
		void print_buckets();
		/**<This function prints the map, buckets, in a human readable form.
		 @return void
		 */

		//Part3
		void do_second_method();
		/**<
		 * This function performs the second method for a key attack on the ciphertext. This attack is the "Second Method" from the Trappe and Washington text. These actions are entirely composed of private members and functions of the class, so no input is requred from the user.
		 * @return void
		 * @pre
		 * -# The key value is undefined
		 * -# The map of Weights and dotproducts is empty
		 * @post
		 * -# The key is computed
		 * -# The Map of Weights is computed
		 */
		void print_key();
		/**<This function takes the results of the second method attack, and prints the computed key to the user in a human readable form.
		 * @return void
		 */

		//Part4
		void decrypt();
		/**<This function takes the ciphertext and computed key from before, and undoes the Vigenere cipher to produce the plaintext.
		 * @return void
		 */
		void print_plaintext();
		/**<This function prints the decrypted plaintext for the user.
		 * @return void
		 */

	private:
		map <int,int> indices;
		string ciphertext;
		string plaintext;
		int key_len;
		map<int, string> buckets;
		string key;
		vector<double> A;

		vector<double> rotate_a_matrix(int j);
		/**<This function provides the rotated A matrix to the function who calls it. This A matrix is the predefined frequency vector from Trappe and Washington, that is used for computing the dot product in the frequency attack on the ciphertext.
		 * @return vector<double>
		 * @param j This is the number of spaces that we would like to rotate the A matrix.
		 */
		vector< vector<double> > generate_w_vector();
		/**<This function computes the vector of letter frequency weights on each of the buckets of ciphertext.
		 * @return vector< vector<double> >
		 */
		double dotMe(vector<double> a, vector<double> b);
		/**<This function computes the dot product of two vectors.
		 *@return double 
		 @param a This is the first vector.
		 @param b This is the second vector.
		 */

};
