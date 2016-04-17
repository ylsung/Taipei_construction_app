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

using namespace std;
void UseRestriction(int start, int RowOrColumn, vector<int> restriction, int restrictionNum,
	int *Pre, int *Now, int *temp);
bool DFS(int **Now, int GoalRow, int Row, int Column, vector<int> *RowRestriction, 
	vector<int> *ColumnRestriction, stack<int**> DFSstack, int start, int restrictionNum);

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
			//cout << "Row " << i << endl;
			UseRestriction(0, column, rowRestriction[i], 1, PreRow, NowRow, tempRow);
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
				//cout << "Column " << i << endl;
				UseRestriction(0, row, columnRestriction[i], 1,PreColumn, NowColumn, tempColumn);
				for(int j = 0; j < row; j++){
					if(AllSolve == 1 && tempRow[j] == -1) AllSolve = 0;
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
		}

		//if(AllSolve == 1) break;
		
	}
	
	delete []PreRow;
	delete []NowRow;
	delete []tempRow;
	delete []PreColumn;
	delete []NowColumn;
	delete []tempColumn;
	//DFS
	stack<int**> DFSstack;
	//DFSstack.push(nonogram);
	//int** NowNonogram;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			cout << nonogram[i][j] << " ";
		}
		cout << endl;
	}
	/*
	bool DFScheck = 0;
	for(int i = 0; i < row; i++){
		if(find(nonogram[i], nonogram[i] + column, -1) == nonogram[i] + column) {
			DFScheck = 1;
			break;
		}
	}
	cerr << DFScheck << endl;*/
	/*if(DFScheck)*/ DFS(nonogram, 0, row, column, rowRestriction, columnRestriction, DFSstack, 0, 1);
	

	/*
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			cout << nonogram[i][j] << " ";
		}
		cout << endl;
	}*/
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if(nonogram[i][j] == 1){
				cout << "#";
			}else if(nonogram[i][j] == 0)
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}
/*
void UseRestriction(int start, int RowOrColumn, vector<int> restriction, int restrictionNum,
	int *Pre, int *Now, int *temp){

	for(int i = start; i < RowOrColumn; i++){
		if(i + restriction[restrictionNum] - 1 >= RowOrColumn) return; // out of the bound
		
		fill(Now + i, Now + i + restriction[restrictionNum], 1);
		if(restrictionNum + 1 <= restriction[0]){
			UseRestriction(i + 1 + restriction[restrictionNum], RowOrColumn, restriction,
			 restrictionNum + 1, Pre, Now, temp);
		}
		if(restrictionNum == restriction[0]){
			if(find(Pre, Pre + RowOrColumn, 1) != (Pre + RowOrColumn)){ // the PreRow is not new
				for(int i = 0; i < RowOrColumn; i++){
					if(temp[i] != -1){
						if(Pre[i] == 1 && Now[i] == 1){
							temp[i] = 1;
						}else if(Pre[i] != Now[i]){
							temp[i] = -1;
						}else if(Pre[i] == 0 && Now[i] == 0){
							temp[i] = 0;
						}
					}
				}
			}else{ // the PreRow is new, copy the NowRow to it
				copy(Now, Now + RowOrColumn, Pre);
				copy(Now, Now + RowOrColumn, temp);
			}
		}

		fill(Now + i, Now + i + restriction[restrictionNum], 0);
	}
}
*/
void UseRestriction(int start, int RowOrColumn, vector<int> restriction, int restrictionNum,
	int *Pre, int *Now, int *temp){
	int go = 0;
	int *record = new int[RowOrColumn];
	for(int i = start; i < RowOrColumn; i++){
		if(i + restriction[restrictionNum] - 1 >= RowOrColumn) {
			delete []record;
			return; // out of the bound
		}
		copy(Now, Now + RowOrColumn, record);

		if(Now[i] != 0){
			if(find(Now + i, Now + i + restriction[restrictionNum], 0) == 
				(Now + i + restriction[restrictionNum])){
				if(Now[i + restriction[restrictionNum]] != 1){
					if(i >= 1 && Now[i - 1] == 1){}
					else{
						fill(Now + i, Now + i + restriction[restrictionNum], 1);
						if(restrictionNum == restriction[0]){
							for(int k = 0; k < RowOrColumn; k++){
								if(Now[k] == -1) Now[k] = 0;
							}
						}
						go = 1;
					}
				}
			}
		}
		if(go == 1){
			/*check the block section not over restriction number*/
			bool check = 0;
			int block_number = 0;
			for(int k = 0; k < RowOrColumn; k++){
				if(Now[k] == 1 && check == 0) {
					block_number++;
					check = 1;
				}else if(Now[k] == 0){
					check = 0;
				}
			}
			if((restrictionNum + 1 <= restriction[0]) && (block_number <= restriction[0])){
				UseRestriction(i + 1 + restriction[restrictionNum], RowOrColumn, restriction,
				 restrictionNum + 1, Pre, Now, temp);
			}
		
			if((restrictionNum == restriction[0]) && (block_number <= restriction[0])){
				/*
				cout << "block_number" << block_number << endl;
				cout << "Now" << endl;
				for(int k = 0; k < RowOrColumn; k++){
					cout << Now[k] << " ";
				}
				cout << endl;
				cout << "Pew" << endl;
				for(int k = 0; k < RowOrColumn; k++){
					cout << Pre[k] << " ";
				}
				cout << endl;*/
				if(find(Pre, Pre + RowOrColumn, -1) == (Pre + RowOrColumn)){ // the PreRow don't have undesided element
					for(int i = 0; i < RowOrColumn; i++){
						if(temp[i] != -1){
							if(Pre[i] == 1 && Now[i] == 1){
								temp[i] = 1;
							}else if(Pre[i] != Now[i]){
								temp[i] = -1;
							}else if(Pre[i] == 0 && Now[i] == 0){
								temp[i] = 0;
							}
						}
					}/*
					cout << "Temp IN" << i + restriction[restrictionNum] << endl;
					for(int k = 0; k < RowOrColumn; k++){
						cout << temp[k] << " ";
					}
					cout << endl;*/
				}else{ // the PreRow has undesided element, copy the NowRow to it
					copy(Now, Now + RowOrColumn, Pre);
					copy(Now, Now + RowOrColumn, temp);
				}
			}
		}
		go = 0;
		/*
		cout << "record" << endl;
			for(int k = 0; k < RowOrColumn; k++){
				cout << record[i] << " ";
		}
		cout << endl;*/
		//fill(Now + i, Now + i + restriction[restrictionNum], 0);
		copy(record, record + RowOrColumn, Now);
		if(i == RowOrColumn - 1){
			delete []record;
		}
	}
}
bool DFS(int **Now, int GoalRow, int Row, int Column, vector<int> *RowRestriction, 
	vector<int> *ColumnRestriction, stack<int**> DFSstack, int start, int restrictionNum){
	// no undesided element
	//if(find(Now[GoalRow], Now[GoalRow] + Column, -1) == (Now[GoalRow] + Column)) goto Tag;
	int **record = new int*[Row];
	for(int i = 0; i < Row; i++){
		record[i] = new int[Column];
		copy(Now[i], Now[i] + Column, record[i]);
	}
	/////////
	int go = 0;
	/*
	bool undesidedOrNot = 0;
	for(int l = 0; l < Column; l++){
		if(Now[GoalRow][l] == -1) undesidedOrNot = 1;
	}
	if(undesidedOrNot == 0){
		if(!DFS(Now, GoalRow + 1, Row, Column, RowRestriction, ColumnRestriction, DFSstack, 
							0, 1)){}
						else return 1;
	}
	else{*/
		for(int i = start; i < Column; i++){
			
			if(i + RowRestriction[GoalRow][restrictionNum] - 1 >= Column) {
				for(int j = 0; j < Row; j++){
					delete []record[j];
				}
				delete []record;

				return 0; // out of the bound
			}
			if(Now[GoalRow][i] != 0){
				if(find(Now[GoalRow] + i, Now[GoalRow] + i + RowRestriction[GoalRow][restrictionNum], 0) == 
					(Now[GoalRow] + i + RowRestriction[GoalRow][restrictionNum])){
					if(Now[GoalRow][i + RowRestriction[GoalRow][restrictionNum]] != 1){
						if(i >= 1 && Now[GoalRow][i - 1] == 1){}
						else{
							fill(Now[GoalRow] + i, Now[GoalRow] + i + RowRestriction[GoalRow][restrictionNum], 1);
							if(restrictionNum == RowRestriction[GoalRow][0]){
								for(int k = 0; k < Column; k++){
									if(Now[GoalRow][k] == -1) Now[GoalRow][k] = 0;
								}
							}
							go = 1;
						}
					}
				}
			}
			if(go == 1){
				/*
				cout << "GoalRow   :" << GoalRow << endl;
				for(int l = 0; l < Column; l++){
					cout << Now[GoalRow][l] << " ";
				}
				cout << endl;*/
				/*check the block section not over restriction number*/
				//////

				//////
				/*cout << "GoalRow" << GoalRow << endl;
				for(int l = 0; l < Row; l++){
					for(int j = 0; j < Column; j++){
						cout << Now[l][j] << " ";
					}
					cout << endl;
				}
				cout << endl;*/
				//////
				bool check = 0;
				int block_number = 0;
				for(int k = 0; k < Row; k++){
					if(Now[GoalRow][k] == 1 && check == 0) {
						block_number++;
						check = 1;
					}else if(Now[GoalRow][k] == 0){
						check = 0;
					}
				}

				if((restrictionNum + 1 <= RowRestriction[GoalRow][0]) && (block_number <= RowRestriction[GoalRow][0])){
					if(!DFS(Now, GoalRow, Row, Column, RowRestriction, ColumnRestriction, DFSstack, 
						start + 1, restrictionNum + 1)){}
					else return 1;
				}
				
				/////
				bool RowAccept = 0;
				if(restrictionNum == RowRestriction[GoalRow][0]){
					int restrictionNum_row = 0;
					int onestreak_row = 0;
					int onenum_row = 0;
					
							for(int l = 0; l < Column; l++){
								if(onestreak_row == 0 && Now[GoalRow][l] == 1){
									restrictionNum_row++;
									if(restrictionNum_row > RowRestriction[GoalRow][0]){
										//cout << "out of res" << endl;
										goto Tag;
										return 0;
									}
									onestreak_row = 1;
									onenum_row++;
								}else if(onestreak_row == 1 && Now[GoalRow][l] == 1){
									onenum_row++;
								}else if(Now[GoalRow][l] == 0){
									if(onestreak_row == 1){
										onestreak_row = 0;
										//cout << "COLUMN " << k << "one " << onenum << endl;
										if(onenum_row != RowRestriction[GoalRow][restrictionNum_row]){
											goto Tag;
											return 0;
										}
										onenum_row = 0;
									}
								}
								if(l == Column - 1){
									if(onestreak_row == 1){
										if(onenum_row != RowRestriction[GoalRow][restrictionNum_row]){
											goto Tag;
											return 0;
										}else{
											if(restrictionNum_row == RowRestriction[GoalRow][0]){
												RowAccept = 1;
											}
											else {
												goto Tag;
												return 0;
											}
										}
										onenum_row = 0;
									}
									else if(restrictionNum_row == RowRestriction[GoalRow][0]) RowAccept = 1;
								}
							}
						
				}
				//cout << "A "<< RowAccept << endl;
				/////
				if((restrictionNum == RowRestriction[GoalRow][0]) && (RowAccept == 1)){
					/*
					cout << "block_number" << block_number << endl;
					cout << "Now" << endl;
					for(int k = 0; k < RowOrColumn; k++){
						cout << Now[k] << " ";
					}
					cout << endl;
					cout << "Pew" << endl;
					for(int k = 0; k < RowOrColumn; k++){
						cout << Pre[k] << " ";
					}
					cout << endl;*/
					
					bool Satisfy = 1;
					bool finalSatisfy = 1;
					for(int k = 0; k < Column; k++){
						Satisfy = 1;
						check = 0;
						block_number = 0;
						for(int l = 0; l < Row; l++){
							if(Now[l][k] == 1 && check == 0) {
								block_number++;
								check = 1;
							}else if(Now[l][k] == 0){
								check = 0;
							}
						}
						if(block_number > ColumnRestriction[k][0]){
							Satisfy = 0;
							break;
						}
						if(block_number != ColumnRestriction[k][0]){
							finalSatisfy = 0;
						}
					}
					if(GoalRow < Row - 1 && Satisfy == 1){
						//DFSstack.push(Now);
						if(!DFS(Now, GoalRow + 1, Row, Column, RowRestriction, ColumnRestriction, DFSstack, 
							0, 1)){}
						else return 1;
					}else if(GoalRow == Row - 1 && finalSatisfy == 1){
						//cout << "IN" << endl;
						/*cout << "GoalRow" << GoalRow << endl;
						for(int l = 0; l < Row; l++){
							for(int j = 0; j < Column; j++){
								cout << Now[l][j] << " ";
							}
							cout << endl;
						}
						cout << endl;*/
						////////////////
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
										goto Tag;
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
											goto Tag;
											return 0;
										}
										onenum = 0;
									}
								}
								if(l == Row - 1){
									if(onestreak == 1){
										if(onenum != ColumnRestriction[k][ColumnrestrictionNum]){
											goto Tag;
											return 0;
										}else{
											if(ColumnrestrictionNum == ColumnRestriction[k][0]){}
											else {
												goto Tag;
												return 0;
											}
										}
										onenum = 0;
									}
								}
							}
							if(k == Column - 1){
								//cout << "OK" << endl;
	   							return 1;
							}
						}
					}
				}
			}
			Tag:
			go = 0;
			/*
			cout << "record" << endl;
				for(int k = 0; k < RowOrColumn; k++){
					cout << record[i] << " ";
			}
			cout << endl;*/
			//fill(Now + i, Now + i + restriction[restrictionNum], 0);
			
			//copy(record[GoalRow], record[GoalRow] + Column, Now[GoalRow]);
			for(int j = 0; j < Row; j++){
				copy(record[j], record[j] + Column, Now[j]);
			}

			
			
			if(i == Column - 1){
				for(int j = 0; j < Row; j++){
					delete []record[j];
				}
				delete []record;
				return 0;
			}
		}
	
	//}

}


