
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
/*void UseRestriction(int start, int RowOrColumn, vector<int> restriction, int restrictionNum,
	int *Pre, int *Now, int *temp);*/
void UseRestriction(int *origin, int RC, int *Now, int*Pre, int *temp, int length, 
	vector<int> restriction, int restrictionNum, int frag);
bool DFS(int **Now, int GoalRow, int Row, int Column, vector<int> *RowRestriction, 
	vector<int> *ColumnRestriction, stack<int**> DFSstack, int start, int restrictionNum);
void LineCheck(int *origin, int RC, int *Now, int length, vector<int> restriction, 
	int restrictionNum, stack<int*> &DFSstack, int frag);
bool ColumnCheck(int **Now, int Row, int Column, vector<int> *ColumnRestriction);
bool ColumnCheckPro(int **Now, int Row, int Column, vector<int> *ColumnRestriction);

int main(){
	int row, column;
	cin >> row >> column;
	cin.get(); // eat the /n at the first line
	string inputLine;
	vector<int> *rowRestriction;
	vector<int> *columnRestriction;
	int **nonogram;
	nonogram = new int*[row];

	for(int i = 0; i < row; i++){
		nonogram[i] = new int[column];
	}
	for(int i = 0; i < row; i++){
		fill(nonogram[i], nonogram[i] + column, -1);
	} // initiate the nonogram, 0 means not block
	rowRestriction = new vector<int>[row];
	columnRestriction = new vector<int>[column];
	for(int i = 0; i < row; i++){
		rowRestriction[i].push_back(0); //the first element is to save the restriction number of the row
	}
	for(int i = 0; i < column; i++){
		columnRestriction[i].push_back(0); //the first element is to save the restriction number of the column
	}
	int Index = 0;
	//read the input
	while((Index < row + column) && getline(cin, inputLine)){
		string inputElement;
		stringstream ss(inputLine);
		while(ss >> inputElement){
			if(Index < row){
				rowRestriction[Index].push_back(stoi(inputElement));
				rowRestriction[Index][0]++;
			}else {
				columnRestriction[Index - row].push_back(stoi(inputElement));
				columnRestriction[Index - row][0]++;
			}
		}
		Index++;
	}
	/* do line checking*/
	bool KeepGoing = 1;
	int *PreRow = new int[column];
	int *NowRow = new int[column];
	int *tempRow = new int [column];
	int *PreColumn = new int[row];
	int *NowColumn = new int[row];
	int *tempColumn = new int[row];
	
	while(KeepGoing){
		// Row Checking
		bool AllSolve = 1;
		//cout << "Row " << Round << endl;
		for(int i = 0; i < row; i++){
			fill(tempRow, tempRow + column, 0);
			copy(nonogram[i], nonogram[i] + column, PreRow);
			copy(nonogram[i], nonogram[i] + column, NowRow);
			//cout << "Row :" << i << endl;
			UseRestriction(NowRow, column, NowRow, PreRow, tempRow, column, rowRestriction[i], 1, 0);
			/*cout << "temp" << endl;
			for(int k = 0; k < column; k++){
				cout << tempRow[k] << " ";
			}
			cout << endl;*/
			for(int j = 0; j < column; j++){
				if(AllSolve == 1 && tempRow[j] == -1) AllSolve = 0;
				if(tempRow[j] != -1){
					nonogram[i][j] = tempRow[j];
				}
			}
		}
		/*for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				cout << setw(3)<< nonogram[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
		//Column Checking
		if(AllSolve == 1) break;
		else if(AllSolve == 0){
			//cout << "Column " << Round << endl;
			AllSolve = 1;
			KeepGoing = 0;
			for(int i = 0; i < column; i++){
				fill(tempColumn, tempColumn + row, 0);
				for(int j = 0; j < row; j++){
					PreColumn[j] = nonogram[j][i];
					NowColumn[j] = nonogram[j][i];
				}
				/*for(int j = 0; j < row; j++){
					cout << setw(3) << right << NowColumn[j];
				}
				cout << endl << endl;*/
				//cout << "Column :" << i << endl;

				UseRestriction(NowColumn, row, NowColumn, PreColumn, tempColumn, row, columnRestriction[i], 1, 0);
				for(int j = 0; j < row; j++){
					if(AllSolve == 1 && tempColumn[j] == -1) AllSolve = 0;
					if((KeepGoing == 0) && (tempColumn[j] != nonogram[j][i])) KeepGoing = 1;
					if(tempColumn[j] != -1){
						nonogram[j][i] = tempColumn[j];
					}
				}/*
				cout << "temp" << endl;
				for(int k = 0; k < row; k++){
					cout << tempColumn[k] << " ";
				}
				cout << endl;*/
			}
			/*for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				cout << setw(3)<< nonogram[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
		}

		if(AllSolve == 1) break;
		
	}
/*
	for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				cout << setw(3)<< nonogram[i][j];
			}
			cout << endl;
		}
	*/
	delete []PreRow;
	delete []NowRow;
	delete []tempRow;
	delete []PreColumn;
	delete []NowColumn;
	delete []tempColumn;

	//DFS
	stack<int*> DFSstack;
	int** TempNonogram;
	TempNonogram = new int*[row];
	//int* NowRow;
	NowRow = new int[column + 1];
	int NowRowNum = 0;
	int PreRowNum = 0;
	int TopRowNum = 0;
	for(int i = 0; i < row; i++){
		TempNonogram[i] = new int[column];
		copy(nonogram[i], nonogram[i] + column, TempNonogram[i]);
	}
	copy(nonogram[0], nonogram[0] + column, NowRow);
	NowRow[column] = 0;
	if(find(NowRow, NowRow + column, -1) == NowRow + column) DFSstack.push(NowRow);
	else {
		LineCheck(NowRow, column, NowRow, column, rowRestriction[0], 1, DFSstack, 0);
		delete []NowRow;
	}
	while(!DFSstack.empty()){
		NowRow = DFSstack.top();
		DFSstack.pop();
		NowRowNum = NowRow[column];
		if(NowRowNum > TopRowNum) TopRowNum = NowRowNum;
		/*check the Now Num, if NowNum < PreNum means that the row is tracing back.
		  so use cover the Row at NowNum with original nonogram Row, or the error judge will happen.
		*/
		if(PreRowNum > NowRowNum) 
			{
				for(int i = PreRowNum; i <= TopRowNum; i++){
					copy(nonogram[i], nonogram[i] + column, TempNonogram[i]);
				}
				
			}
		//cerr << DFSstack.size() << endl;
		PreRowNum = NowRowNum;
		//use new line to switch original row at Temp.
		copy(NowRow, NowRow + column, TempNonogram[NowRowNum]);
		/*for(int i = 0; i < column; i++) {
			cout << setw(3) << right << i;
		}
			cout << endl;
		for(int i = 0; i < column; i++) {
			cout << setw(3) << right << "-";
		}
			cout << endl;
		for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				cout << setw(3) << right << TempNonogram[i][j];
		}
		cout << endl;
	}*/
		//no use, delete
		delete []NowRow;
		// last row check the answer.
		if(NowRowNum == row - 1){
			if(ColumnCheckPro(TempNonogram, row, column, columnRestriction)) break;
		}else {
			/* if not the last line, do simple check it is posible or not, if not, just 
			   don't do anything. if yes, Line check the next row.*/
			if(ColumnCheck(TempNonogram, row, column, columnRestriction)){
				NowRow = new int[column+ 1];
				copy(TempNonogram[NowRowNum + 1], TempNonogram[NowRowNum + 1] + column, NowRow);
				NowRow[column] = NowRowNum + 1;
				if(find(NowRow, NowRow + column, -1) == NowRow + column) DFSstack.push(NowRow);
				else{
					LineCheck(NowRow, column, NowRow, column, rowRestriction[NowRowNum + 1], 1, DFSstack, 0);
					delete []NowRow;
				}
			}
		}
	}
	while(!DFSstack.empty()){
		DFSstack.pop();
	} 

	//int** NowNonogram;
	/*for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			cout << nonogram[i][j] << " ";
		}
		cout << endl;
	}*/

	/*if(DFScheck)*/ //DFS(nonogram, 0, row, column, rowRestriction, columnRestriction, DFSstack, 0, 1);
	

	/*
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			cout << TempNonogram[i][j] << " ";
		}
		cout << endl;
	}*/
	/*
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if(nonogram[i][j] == 1){
				cout << "#";
			}else if(nonogram[i][j] == 0)
				cout << ".";
				else cout << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if(TempNonogram[i][j] == 1){
				cout << "#";
			}else if(TempNonogram[i][j] == 0)
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}

void UseRestriction(int *origin, int RC, int *Now, int*Pre, int *temp, int length, 
	vector<int> restriction, int restrictionNum, int frag){
	if(length <= 0) return;
	int *record = new int[length];
	copy(Now, Now + length, record);
	for(int i = 0; i < length; i++){
		
		if(i > 0) {
			if(Now[i - 1] == 1) {
				if(Now[i] != 1) frag++;
				goto Tag2;
				//break;
			}
		}

		if(Now[i] != 0){
			if( i + restriction[restrictionNum] - 1 >= length)break;
			if(find(Now + i, Now + i + restriction[restrictionNum], 0) == 
				Now + i + restriction[restrictionNum]){
				if(i + restriction[restrictionNum] == length){
					fill(Now + i, Now + i + restriction[restrictionNum], 1);
					frag++;
				}
				else if(Now[i + restriction[restrictionNum]] != 1){
					fill(Now + i, Now + i + restriction[restrictionNum], 1);
					Now[i + restriction[restrictionNum]] = 0;
					frag++;
				}else{
					goto Tag;
				}
			}else {
				goto Tag;
			}
		}else{
			goto Tag;
		}
		
		if(frag > restriction[0]){
			goto Tag;
		}
		if(restrictionNum == restriction[0]){
			/*for(int j = 0; j < length; j++){
				if(Now[j] == -1) Now[j] = 0;
			}*/
			for(int j = i + restriction[restrictionNum] + 1; j < length; j++){
				if(Now[j] == 1) {
					frag--;
					goto Tag;
				}
			}
			for(int j = 0; j < RC; j++){
				if(origin[j] == -1) origin[j] = 0;
				//cout << setw(3) << right << origin[j];
			}
			//cout << endl;
			//Todo
			if(find(Pre, Pre + RC, -1) == (Pre + RC)){ // the PreRow don't have undesided element
					for(int k = 0; k < RC; k++){
						if(temp[k] != -1){
							if(Pre[k] == 1 && origin[k] == 1){
								temp[k] = 1;
							}else if(Pre[k] != origin[k]){
								temp[k] = -1;
							}else if(Pre[k] == 0 && origin[k] == 0){
								temp[k] = 0;
							}
						}
					}
				}else{ // the PreRow has undesided element, copy the NowRow to it
					copy(origin, origin + RC, Pre);
					copy(origin, origin + RC, temp);
				}
		}else{
			UseRestriction(origin, RC, Now + i + restriction[restrictionNum] + 1,Pre, temp, 
				length - (i + restriction[restrictionNum] + 1), restriction, restrictionNum + 1, frag);
		}
		Tag2:
		frag--;
		Tag:
		copy(record, record + length, Now);
		if(Now[i] == 1) frag++;
		//if(Now[i] == -1) Now[i] = 0;
 	}
 	delete []record;
}

void LineCheck(int *origin, int RC, int *Now, int length, vector<int> restriction, 
	int restrictionNum, stack<int*> &DFSstack, int frag){
	if(length <= 0) return;
	int *record = new int[length];
	copy(Now, Now + length, record);
	for(int i = 0; i < length; i++){
		if(i > 0) {
			if(Now[i - 1] == 1) {
				if(Now[i] != 1) frag++;
				goto Tag2;
			}
		}
		if(Now[i] != 0){
			if(i + restriction[restrictionNum] - 1 >= length)break;
			if(find(Now + i, Now + i + restriction[restrictionNum], 0) == 
				Now + i + restriction[restrictionNum]){
				if(i + restriction[restrictionNum] == length){
					fill(Now + i, Now + i + restriction[restrictionNum], 1);
					frag++;
				}
				else if(Now[i + restriction[restrictionNum]] != 1){
					fill(Now + i, Now + i + restriction[restrictionNum], 1);
					Now[i + restriction[restrictionNum]] = 0;
					frag++;
				}else{
					goto Tag;
				}
			}else {
				goto Tag;
			}
		}else{
			goto Tag;
		}
		if(frag > restriction[0]) goto Tag;
		if(restrictionNum == restriction[0]){
			/*for(int j = 0; j < length; j++){
				if(Now[j] == -1) Now[j] = 0;
			}*/
			for(int j = i + restriction[restrictionNum] + 1; j < length; j++){
				if(Now[j] == 1) {
					frag--;
					goto Tag;
				}
			}
			for(int j = 0; j < RC; j++){
				if(origin[j] == -1) origin[j] = 0;
				//cout << origin[j] << " ";
			}
			//cout << endl;
			int *New = new int[RC + 1];
			copy(origin, origin + RC + 1, New);
			DFSstack.push(New);
		}else{
			LineCheck(origin, RC, Now + i + restriction[restrictionNum] + 1, 
				length - (i + restriction[restrictionNum] + 1), restriction, restrictionNum + 1, DFSstack, frag);

		}
		Tag2:
		frag--;
		Tag:
		copy(record, record + length, Now);
		if(Now[i] == 1) frag++;

 	}
 	delete []record;
}

bool ColumnCheck(int **Now, int Row, int Column, vector<int> *ColumnRestriction){
	int black = 0;
	int restrictionNum = 0;
	bool desided = 1;
	int check = 0;
	for(int i = 0; i < Column; i++){
		desided = 1;
		restrictionNum = 0;
		black = 0;
		check = 0;
		for(int j = 0; j < Row; j++){
			if(Now[j][i] == -1) desided = 0;
			
			if(Now[j][i] == 1 && check == 0){
				black++;

				restrictionNum++;
				if(restrictionNum > ColumnRestriction[i][0]) {
					/*cout << "Column :" << i << ", out of restrictionNum ! restrictionNum = " 
					<< restrictionNum << endl;*/
					return 0;
				}
				
				check = 1;
			}else if(Now[j][i] == 0){
				if(black != ColumnRestriction[i][restrictionNum] && desided == 1 && check == 1) {
					/*cout << "at column : " << i << " black not satisfied, black numebr = " << black 
					<< ", expect black = " << ColumnRestriction[i][restrictionNum] << endl; */
					return 0;
				}
				black = 0;
				check = 0;
			}else if(Now[j][i] == 1){
				if(desided) black++;
				if(black > ColumnRestriction[i][restrictionNum]  && desided == 1) {
					/*cout << "at column : " << i << ", The black number is out of bound, black = " 
					<< black << " expect = " << ColumnRestriction[i][restrictionNum] << endl; */
					return 0;
				}
			}
			
		}
	}
	return 1;
}

bool ColumnCheckPro(int **Now, int Row, int Column, vector<int> *ColumnRestriction){
	int ColumnrestrictionNum = 0;
	bool onestreak = 0;
	int onenum = 0;
	for(int k = 0; k < Column; k++){
		ColumnrestrictionNum = 0;
		onestreak = 0;
		onenum = 0;
		for(int l = 0; l < Row; l++){
			if(onestreak == 0 && Now[l][k] == 1){
				ColumnrestrictionNum++;
				if(ColumnrestrictionNum > ColumnRestriction[k][0]){
					//cout << "out of res" << endl;
					return 0;
				}
				onestreak = 1;
				onenum++;
			}else if(onestreak == 1 && Now[l][k] == 1){
				onenum++;
			}else if(Now[l][k] == 0){
				if(onestreak == 1){
					onestreak = 0;
					//cout << "COLUMN " << k << "one " << onenum << endl;
					if(onenum != ColumnRestriction[k][ColumnrestrictionNum]){
						return 0;
					}
					onenum = 0;
				}
			}
			if(l == Row - 1){
				if(onestreak == 1){
					if(onenum != ColumnRestriction[k][ColumnrestrictionNum]){
						return 0;
					}else{
						if(ColumnrestrictionNum == ColumnRestriction[k][0]){}
						else {
							return 0;
						}
					}
					onenum = 0;
				}
			}
		}
		/*if(k == Column - 1){
			//cout << "OK" << endl;
				return 1;
		}*/
	}
	return 1;
}



