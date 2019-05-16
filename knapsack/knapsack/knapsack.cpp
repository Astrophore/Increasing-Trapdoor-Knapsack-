/*
 * --------------------------
 * Programming language: C++
 * File name: knapsack.cpp
 * Author: Wei Jie
 * Trapdoor Knapsack Encryption & Decryption
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <bitset>
#include <vector>
#include <functional>
#include <sstream>
#include <numeric>
#include <iterator>

using namespace std;
vector<int> prikey;
vector<int> publickey;
vector<int> messagebinary;
vector<int> binaryresult;
vector<int> ciphertext;
vector<int> plaintext;
vector<int> decryptionnumber;
vector<int> buffer;
vector<int>binary;
int userSize, userinput, mod, sum, multiplier;
string message;

int gcd(int a1, int a2) {
	int tmp;
	while (a2 != 0) {
		tmp = a1;
		a1 = a2;
		a2 = tmp % a2;
	}
	return a1;
}

int modInverse(int a, int b)
{
	a = a % b;
	for (int x = 1; x < b; x++)
	{
		if ((a*x) % b == 1)
			return x;
	}
}

int main()
{
	cout << "Size of the super-increasing knapsack will be set default as 8" << endl;
	userSize = 8;
	prikey.resize(userSize); //Resizing the vector size to user input value
	prikey.clear(); //clear content of vector so that new values can be added in the next for loop
	cout << endl;
	cout << "Please enter private keys. Number of inputs required: " << userSize << endl;
	/*User input for a series o private key (super-increasing)*/
	for (int i = 0; i < userSize; i++) {
		cout << "Enter input number " << i + 1 << ":";
		cin >> userinput;
		prikey.push_back(userinput);
		cout << endl;
	}

	int a = 1;
	cout << "Your private keys are shown below:" << endl;
	for (vector<int>::const_iterator i = prikey.begin(); i != prikey.end(); ++i) {
		cout << a << ")" << " " << *i << endl;
		a++;
	}

	/*Calculation of sum of knapsack*/
	sum = accumulate(prikey.begin(), prikey.end(), 0);
	cout << "Sum of your knapsack: " << sum << "." << endl << endl;

	cout << "Enter your mod value: ";
	cin >> mod;
	cout << endl;

	/*This while loops ensures user can only choose a mod value > sum of the knapsack*/
	while (mod < sum) {
		cout << "Please enter a mod value bigger than" << sum << endl;
		cin >> mod;
	}

	cout << "Enter a multiplier that is coprime to the mod value of " << endl
		<< mod << " :";
	cin >> multiplier;
	cout << endl;

	while (gcd(multiplier, mod) != 1) {
		cout << "Please enter a multipier value that is coprime to " << mod << "." << endl << endl;
		cin >> multiplier;
	}



	for (int i = 0; i < userSize; i++) {
		publickey.push_back(prikey.at(i) * multiplier % mod); //create public key
	}

	cout << "Your public key is:" << endl;
	for (vector<int>::const_iterator i = publickey.begin(); i != publickey.end(); ++i) {
		cout << *i << endl; //print out public key
	}
	cout << "---END OF PUBLIC KEY---" << endl;
	cin.ignore();
	cout << "Please enter message to be encrypted \n";
	getline(cin, message);

	for (size_t i = 0; i < message.size(); ++i) {
		bitset<8> test(message.c_str()[i]);
		string mystring = test.to_string<char, string::traits_type, string::allocator_type>();

		for (int j = 0; j < mystring.size(); j++) {
			int t = 0;
			stringstream ss;
			ss << mystring.at(j);
			while (ss >> t) {
				messagebinary.push_back(t);
			}
		}
	}

	cout << "Binary form of the plaintext: " << endl;
	for (int i = 0; i < messagebinary.size(); i++) {
		cout << messagebinary[i];
	}
	cout << endl;

	while (messagebinary.size() % userSize != 0) {
		messagebinary.insert(messagebinary.begin(), 0);
	}

	int count = 0;
	while (count != messagebinary.size()) {
		int x = 0;
		for (int i = 0; i < userSize; i++) {
			x += publickey[i] * messagebinary[count];
			count++;
		}
		ciphertext.push_back(x);
	}


	for (vector<int>::const_iterator i = ciphertext.begin(); i != ciphertext.end(); ++i)
		cout << "Chipertext: " << *i << endl; //Print our encrypted text


	/*DECRYPTION*/

	for (int i = 0; i < ciphertext.size(); i++) {
		decryptionnumber.push_back(ciphertext.at(i) * modInverse(multiplier, mod) % mod);
	}

	cout << endl;
	cout << "DECRYPTION IN PROGRESS..." << endl;
	for (vector<int>::const_iterator i = decryptionnumber.begin(); i != decryptionnumber.end(); ++i) {
		cout << *i << endl;
	}
	cout << endl;



	int R = 0;

	for (int i = 0; i < ciphertext.size(); i++) {

		R = modInverse(multiplier, mod) * ciphertext.at(i) % mod;

		for (int j = userSize - 1; j > -1; j--) {
			R = R - prikey[j];
			if (R >= 0) {
				buffer.push_back(1);
			}
			else if (R < 0) {
				buffer.push_back(0);
				R = R + prikey[j];
			}

		}


	}

	reverse(buffer.begin(), buffer.end());

	cout << "Reversed Message in Binary Format:" << endl;
	for (vector<int>::const_iterator i = buffer.begin(); i != buffer.end(); ++i) {
		cout << *i;
	}
	cout << endl;

	string tempBinary;
	ostringstream oss;

	if (!buffer.empty()) {
		copy(buffer.begin(), buffer.end() - 1, ostream_iterator<int>(oss, ""));
		oss << buffer.back();
	}

	tempBinary = oss.str(); //tempBinary now contains the plaintext in Binary (REVERSED)

	stringstream sstream(tempBinary);
	string output;
	char c;
	/*The variable "output" will contains the plaintext, but in reversed.*/
	while (sstream.good()) {
		bitset<8> bits;
		sstream >> bits;
		c = char(bits.to_ulong());
		output += c;
	}
	reverse(output.begin(), output.end());
	cout << "Decrypted plaintext = " << output << endl;
}

