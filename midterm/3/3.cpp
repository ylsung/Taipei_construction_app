#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;


int main(){
	int Index = 1;
	string inputLine;
	vector<int> pre;
	vector<int> post;
	vector<int> tree;
	while((Index <= 2) && getline(cin, inputLine)){
		string inputElement;
		stringstream ss(inputLine);
		while(ss >> inputElement){
			if(Index  == 1){
				pre.push_back(stoi(inputElement));
			}else {
				post.push_back(stoi(inputElement));
			}
		}
		Index++;
	}
	tree.push_back(-1);
	tree.push_back(pre[0]);
}
void findtree(int index1, int index2, vector<int> &tree,  vector<int> &pre, vector<int> &post){
	if(index1 >= pre.size()) return;
}

