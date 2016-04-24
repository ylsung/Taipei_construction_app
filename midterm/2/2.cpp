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
void pre(vector<int> &tree, int index, int size);
void in(vector<int> &tree, int index, int size);
void post(vector<int> &tree, int index, int size);
int main(){
	vector<int> tree;
	string inputLine;
	while(getline(cin, inputLine)){
		string inputElement;
		stringstream ss(inputLine);
		while(ss >> inputElement){
			tree.push_back(stoi(inputElement));
		}
		
	}
	pre(tree, 1, tree.size() - 1);
	cout << endl;
	in(tree, 1, tree.size() - 1);
	cout << endl;
	post(tree, 1, tree.size() - 1);
	cout << endl;

}
void pre(vector<int> &tree, int index, int size){
	if(index > size) return;
	if(tree[index] == -1) return;
	cout << tree[index] << " ";
	pre(tree, 2*index, size);
	pre(tree, 2*index+1, size);

}
void in(vector<int> &tree, int index, int size){
	if(index > size) return;
	if(tree[index] == -1) return;
	in(tree, 2*index, size);
	cout << tree[index] << " ";
	in(tree, 2*index+1, size);
}
void post(vector<int> &tree, int index, int size){
	if(index > size) return;
	if(tree[index] == -1) return;
	post(tree, 2*index, size);
	post(tree, 2*index+1, size);
	cout << tree[index] << " ";
}

