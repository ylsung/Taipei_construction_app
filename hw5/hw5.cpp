#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include <cstdio>
#include <unordered_set>
#include <cctype>
#include <vector>
using namespace std;
inline void LowerCase(char* word){
	int i = 0;
	while(word[i]){
		word[i] = tolower(word[i]);
		i++;
	}
}
inline int findsize(char* word){
	int i = 0;
	while(word[i]){
		i++;
	}
	return i;
}
inline void Insert(char* value,string &inputword, vector<string> &ED1, set<string> &ED2,
	unordered_set<string> &dict){
	string word("");
	int size = inputword.length();
	for(int i = 0; i <= size; i++){
		char x = 'a';
		while(x <= 'z'){
			for(int j = 0; j < i; j++){
				word += inputword[j];
			}
			word += x;
			for(int j = i ; j < size; j++){
				word += inputword[j];
			}
			if(value != NULL)ED1.push_back(word);
			else{
				if(dict.find(word) != dict.end()){
					ED2.insert(word);
				}
			}

			x++;
			word = "";
		}
	}
	
}
inline void Delete(char* value,string &inputword, vector<string> &ED1, set<string> &ED2,
	unordered_set<string> &dict){
	string word("");
	int size = inputword.length();
	for(int i = 0; i < size; i++){
		for(int j = 0; j < i; j++){
			word += inputword[j];
		}
		for(int j = i + 1 ; j < size; j++){
			word += inputword[j];
		}
		if(value != NULL)ED1.push_back(word);
		else{
			if(dict.find(word) != dict.end()){
				ED2.insert(word);
			}
		}
		word = "";
	}
}
inline void Substitute(char* value,string &inputword, vector<string> &ED1, set<string> &ED2,
	unordered_set<string> &dict){
	string word("");
	int size = inputword.length();
	for(int i = 0; i < size; i++){
		char x = 'a';
		while(x <= 'z'){
			if(x != inputword[i]){
				for(int j = 0; j < i; j++){
					word += inputword[j];
				}
				word += x;
				for(int j = i + 1 ; j < size; j++){
					word += inputword[j];
				}
				if(value != NULL)ED1.push_back(word);
				else{
					if(dict.find(word) != dict.end()){
						ED2.insert(word);
					}
				}
			}
			x++;
			word = "";
		}
	}
}
inline void Transpose(char* value,string &inputword, vector<string> &ED1, set<string> &ED2,
	unordered_set<string> &dict){
	int size = inputword.length();
	for(int i = 0; i < size - 1; i++){
		string word = inputword;
		swap(word[i], word[i + 1]);
		if(value != NULL)ED1.push_back(word);
		else{
			if(dict.find(word) != dict.end()){
			ED2.insert(word);
			}
		}
	}
}
int main(){
	FILE *file = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "r");
	//FILE *file = fopen("cmudict-0.7b", "r");
	char value[50];
	int startpoint = 0;
	unordered_set<string> dict;
	dict.rehash(360901);
	while(fscanf(file, "%s%*[^\n]", value) != EOF){
		if(startpoint == 56){
			LowerCase(value);
			string word(value);
			//printf("%s + %d\n", value, findsize(value));
			dict.insert(word);
		}
		else startpoint++;
	}
	vector<string> ED1;
	unordered_set<string> ::iterator it;
	set<string> ED2;
	while(scanf("%s%*[^\n]", value) != EOF){
		string inputword(value);
		//check the word in dict first
		it = dict.find(inputword);
		if(it == dict.end()){
			//ED1
			Insert(value,inputword, ED1, ED2, dict);
			Delete(value,inputword, ED1, ED2, dict);
			Substitute(value,inputword, ED1, ED2, dict);
			Transpose(value,inputword, ED1, ED2, dict);
			while(!ED1.empty()){
				string word_ED2 = ED1.back();
				Insert(NULL,word_ED2, ED1, ED2, dict);
				Delete(NULL,word_ED2, ED1, ED2, dict);
				Substitute(NULL,word_ED2, ED1, ED2, dict);
				Transpose(NULL,word_ED2, ED1, ED2, dict);
				ED1.pop_back();
			}
			/*while(!ED1.empty()){
				cout << ED1.back()<<endl;
				ED1.pop_back();
			}*/
			if(ED2.empty()){
				printf("%s ==> NONE", inputword.c_str());
				//cout << inputword << " ==> NONE";
			}else{
				set<string>::iterator itt;
				printf("%s ==>", inputword.c_str());
				//cout << inputword << " ==>";
				for(itt = ED2.begin(); itt != ED2.end() ; itt++){
					printf(" %s", (*itt).c_str());
					//cout << " " << *itt;
				}
				ED2.clear();
			}
			
		}else{
			printf("%s ==> OK", inputword.c_str());
			//cout << inputword << " ==> OK";
		}
		printf("\n");
		//cout << endl;
	}	
}
