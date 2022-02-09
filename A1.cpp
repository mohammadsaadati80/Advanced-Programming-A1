#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
void checking_the_order(vector<vector<string> > &order);
int encrypt_simple(vector<vector<string> > &order);
int decrypt_simple(vector<vector<string> > &order);
int encrypt_complicated(vector<vector<string> > &order);
int decrypt_complicated(vector<vector<string> > &order);
int vector_simple_key_ascii(vector<vector<string> > &order, vector<int> &key_ascii);
int writing_text_on_file(vector<vector<string> > &order, vector<char> &coding_result);
int writing_number_on_file(vector<vector<string> > &order, vector<int> &coding_result);

int decrypt_complicated(vector<vector<string> > &order) 
{
	int srand_number = 0;
	for (int i = 0; i < order[2][0].size(); i++) {
		srand_number += int(order[2][0][i]);
	}
	srand(srand_number);

	int number;
	ifstream myfile;
	myfile.open(order[3][0].c_str(), ios::in);
	vector<char> coding_result;

	while (myfile >> number)
	{
		char character = number - (rand() % 11);
		coding_result.push_back(character);
	}
	myfile.close();

	writing_text_on_file(order, coding_result);

	return 0;
}

int writing_text_on_file(vector<vector<string> > &order, vector<char> &coding_result)
{
	ofstream outfile;
	outfile.open(order[4][0].c_str(), ios::in | ios::out | ios::trunc);
	for (int i = 0; i < coding_result.size();i++) {
		outfile << coding_result[i];
	}
	outfile.close();
	return 0;
}

int encrypt_complicated(vector<vector<string> > &order)
{
	int srand_number = 0;
	for (int i = 0; i < order[2][0].size(); i++) {
		srand_number += int(order[2][0][i]);
	}
	srand(srand_number);

	string line;
	ifstream myfile;
	myfile.open(order[3][0].c_str(), ios::in);
	vector<int> coding_result;

	while (getline(myfile, line))
	{
		for (int i = 0; i < line.size(); i++) {
			int number = line[i] + (rand() % 11);
			coding_result.push_back(number);
		}
		 int number = '\n' + (rand() % 11);
		 coding_result.push_back(number);
	}
	myfile.close();

	writing_number_on_file(order, coding_result);

	return 0;
}

int writing_number_on_file(vector<vector<string> > &order, vector<int> &coding_result)
{
	ofstream outfile;
	outfile.open(order[4][0].c_str(), ios::in | ios::out | ios::trunc);
	for (int i = 0; i < coding_result.size() - 1;i++) {
		outfile << coding_result[i] << endl;
	}
	outfile << endl;
	outfile.close();
	return 0;
}

int decrypt_simple(vector<vector<string> > &order)
{
	vector<int> key_ascii;
	int sizaof_key = vector_simple_key_ascii(order, key_ascii);

	int number;
	ifstream myfile;
	myfile.open(order[3][0].c_str(), ios::in);
	vector<char> coding_result;

	int j = 0;
	while (myfile >> number)
	{
		if (j >= sizaof_key) {
			j = 0;
		}
			char character = number - key_ascii[j];
			coding_result.push_back(character);
			j++;
	}
	myfile.close();

	writing_text_on_file(order, coding_result);

	return 0;
}

int vector_simple_key_ascii(vector<vector<string> > &order, vector<int> &key_ascii)
{
	int sizaof_key = order[2][0].size();
	for (int i = 0; i < sizaof_key;i++) {
		int key_ascii_number = order[2][0][i];
		key_ascii.push_back(key_ascii_number);
	}
	return order[2][0].size();
}

int encrypt_simple(vector<vector<string> > &order) 
{
	vector<int> key_ascii;
	int sizaof_key = vector_simple_key_ascii(order, key_ascii);

	string line;
	ifstream myfile;
	myfile.open(order[3][0].c_str(), ios::in);
	vector<int> coding_result;
	
	int j = 0;
	while (getline(myfile, line))
	{
		for (int i = 0; i < line.size(); i++) {
			if (j >= sizaof_key) {
				j = 0;
			}
			int number = line[i] + key_ascii[j];
			coding_result.push_back(number);
			j++;
		}
		if (j >= sizaof_key) {
			j = 0;
		}
		int number = '\n' + key_ascii[j];
		coding_result.push_back(number);
		j++;
	}
	myfile.close();

	writing_number_on_file(order, coding_result);

	return 0;
}

void checking_the_order(vector<vector<string> > &order) 
{
	if ((order[0][0] == "encrypt") && (order[1][0] == "simple")) {
		encrypt_simple(order);
	}
	if ((order[0][0] == "decrypt") && (order[1][0] == "simple")) {
		decrypt_simple(order);
	}
	if ((order[0][0] == "encrypt") && (order[1][0] == "complicated")) {
		encrypt_complicated(order);
	}
	if ((order[0][0] == "decrypt") && (order[1][0] == "complicated")) {
		decrypt_complicated(order);
	}
}

int main() 
{
	vector<vector<string> > order(5);
	string line;
	int i = 0;

	while (getline(cin, line)) {
		order[i].push_back(line);
		i++;
	}

	checking_the_order(order);

	return 0;
}