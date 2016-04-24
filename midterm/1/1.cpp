#include <iostream>
#include <stack>

using namespace std;

void permutaiton(int n, int Max, stack<int> &teststack);
int main(){
	int testcase;
	cin >> testcase;
	stack<int> teststack;
	permutaiton(1, testcase, teststack);
}

void permutaiton(int n, int Max, stack<int> &teststack){
	int num;
	if(n == Max){
		num = teststack.top();
		cout << num << endl;
		teststack.pop();
	}
	else{
		teststack.push(n);
		num = teststack.top();
		teststack.pop();
		cout << num << " ";
		permutaiton(n + 1, Max);
		teststack.push(n);
		permutaiton(n + 1, Max);
	}

}