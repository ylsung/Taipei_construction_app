#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
class Head;
class Item_Separate;
inline int accept(Head BigArray[], bool *UserRecord,int user, int item, int utime);
inline bool checkItem(Head BigArray[], int user, int item);
inline void items(Head BigArray[], int user1, int user2);
inline void getItemOfUserHead(Head BigArray[], vector<int> *ItemList, int user);
inline void getItemOfUserNumber(Item_Separate *tempNumber, vector<int> *ItemList);
inline void users(Head BigArray[], vector<int> *RealUser, int item1, int item2, int t1, int t2);
inline bool checkTime(Head BigArray[], int user, int item, int t1, int t2);
inline void ratio(Head BigArray[], vector<int> *RealUser, int item, int threshold);
inline bool checkAccept(Head BigArray[], int user, int item);
inline void useItemGetTime(Head BigArray[], int user, int item, vector<int> *TimeVector, int *Time_Record);
inline void findtime_item(Head BigArray[], int i1, vector<int> *querylist);

class Item_Separate{
public:
	Item_Separate(){}
	Item_Separate(int Number, int Combine){
		separate_number = Number;
		combine_number = Combine * 10 + Number;
		isItem = false;
		prev = NULL;
		head = NULL;
		for(int i = 0; i < 10; i++){
			next[i] = NULL;
		}
		TimeMax = 0;
		TimeMin = 1400000000;
	}
	bool addNext(int num){
		if(checkNumber(num) == false) {
			next[num] = new Item_Separate(num, combine_number);
			next[num]->setPrev(this);
			next[num]->setHead(head);
			return true;
		}
		return false;
	}
	Item_Separate *getNext(int num){
		return next[num];
	}
	bool checkNumber(int num){
		if(next[num] != NULL){
			return true;
		}
		return false;
	}
	bool SetTimeAndResult(int Time, int Result){
		bool check = 0;

		for(int i = 0; i < TimeAndResult[0].size(); i++){
			if(TimeAndResult[0][i] == Time) {
				check = 1;
				break;
			}
		}
		if(check == 0){
			/* 0 time */
			TimeAndResult[0].push_back(Time);
			if(Time > TimeMax) TimeMax = Time;
			if(Time < TimeMin) TimeMin = Time;
			/* 1 result */
			TimeAndResult[1].push_back(Result);
			isItem = true;
			return true;
		}
		return false;
	}
	bool checkTimeInterval(int time1, int time2){
		if(time1 > time2){
			int temp = time1;
			time1 = time2;
			time2 = temp;
		}
		if((TimeMax < time1 || TimeMin > time2)) return false;
		else if(!(time1 > TimeMin && time2 < TimeMax)) return true;
		else{
			for(int i = 0; i < TimeAndResult[0].size(); i++){
				if(TimeAndResult[0][i] >= time1 && TimeAndResult[0][i] <= time2) return true;
			}
		}
		return false;
	}
	int getResult(int Time){
		
		for(int i = 0; i < TimeAndResult[0].size(); i++){
			if(TimeAndResult[0][i] == Time) return TimeAndResult[1][i];
		}
		return 0;
	}
	bool isAccept(){
		for(int i = 0; i < TimeAndResult[1].size(); i++){
			if(TimeAndResult[1][i] == 1) return 1;
		}
		return 0;
	}
	void getTime(vector<int> *TimeVector, int *Time_Record){
		for(vector<int>::iterator it = TimeAndResult[0].begin()
			; it != TimeAndResult[0].end(); ++it){

			if(Time_Record[*it - 1318348785] == 0){
				Time_Record[*it - 1318348785] = 1;
				(*TimeVector).push_back(*it);
			}
		}
	}
	int getNumber(){
		return separate_number;
	}
	void setPrev(Item_Separate *node){
		prev = node;
	}
	void setHead(Head *node){
		head = node;
	}
	Head *getHead(){
		return head;
	}
	Item_Separate *getPrev(){
		return prev;
	}
	bool IsItem(){
		return isItem;
	}
	int getItem(){
		return combine_number;
	}/*
	~Item_Separate(){
		for(int i = 0; i < 10; i++){
			delete next[i];
		}
	}*/
private:
	int separate_number, combine_number, TimeMax, TimeMin;
	vector<int> TimeAndResult[2];
	bool isItem;
	Item_Separate *next[10];
	Item_Separate *prev;
	Head *head;
};

class Head{
public:
	Head(){
		ItemNumber = 0;
		for(int i = 0; i < 9; i++){
			number[i] = NULL;
		}
	}
	bool addNumber(int num){
		if(checkNumber(num) == false) {
			number[num - 1] = new Item_Separate(num, 0);
			number[num - 1]->setHead(this);
			return true;
		}
		return false;
	}
	bool checkNumber(int num){
		if(num >=1 && number[num - 1] != NULL){
			return true;
		}
		return false;
	}
	Item_Separate *getNumber(int num){
		if(num >= 1) return number[num - 1];
		return NULL;
	}
	void addItemNumber(){
		ItemNumber++;
	}
	int getItemNumber(){
		return ItemNumber;
	}/*
	~Head(){
		for(int i = 0; i < 9; i++){
			delete number[i];
		}
	}*/
private:
	int ItemNumber;
	Item_Separate *number[9];
};

int main(){
	fstream BigData;
	char *line = new char[100];
	BigData.open("/tmp2/KDDCUP2012/track1/rec_log_train.txt", ios::in);

	vector<int> RealUser;
	bool *UserRecord;
	UserRecord = new bool[2321057];
	fill(UserRecord, UserRecord + 2321057, 0);
	Head *BigArray;
	BigArray = new Head[2321057];
	int a = 1;
	int user, *item_array, item, result, utime;
	while(BigData.getline(line, 100)){
		char *segment;
		int Case = 1;
		
		
		segment = strtok(line, "\t");
		while(segment != NULL){
			if(Case == 1){
				user = atoi(segment);
	
			}else if(Case == 2){
				item = atoi(segment);

				if((item / pow(10, 6)) > 1){
					int digit_temp = 1;
					item_array = new int[8];
					item_array[0] = 7;
					while(digit_temp <= item_array[0]){
						item_array[8 - digit_temp] = item % 10;
						item /= 10;
						digit_temp ++;
					}
				}else{
					int digit_temp = 1;

					item_array = new int[7];
					item_array[0] = 6;
					while(digit_temp <= item_array[0]){
						item_array[7 - digit_temp] = item % 10;
						item /= 10;
						digit_temp ++;
					}
				}
			
			}else if(Case == 3){
				result = atoi(segment);
			
			}else{
				utime = atoi(segment);
		
				Item_Separate *tempNumber;
				if(UserRecord[user - 100001] == 0) {
					UserRecord[user - 100001] = 1;
					RealUser.push_back(user - 100001);
				}
				for(int i = 1; i <= item_array[0]; i++){
					if(i == 1){
						BigArray[user - 100001].addNumber(item_array[1]);
						tempNumber = BigArray[user- 100001].getNumber(item_array[1]);
					}else if(i == item_array[0]){
						tempNumber->addNext(item_array[i]);
						tempNumber = tempNumber->getNext(item_array[i]);
						if(tempNumber->SetTimeAndResult(utime, result)){
							BigArray[user- 100001].addItemNumber();
						}

					}else{
						tempNumber->addNext(item_array[i]);
						tempNumber = tempNumber->getNext(item_array[i]);
					}
			
				}

				delete item_array;
			}
			segment = strtok(NULL, "\t");
			Case++;
		}
		
	}
	
	//sort(RealUser.begin(), RealUser.end());

	/* function use*/
	int TestThreshold = 0, TestLength = 1;
	cin >> TestThreshold;
	string TestType;
	int u1, u2, i1, i2, t1, t2, threshold;

	while(TestLength <= TestThreshold){
		cin >> TestType;
		if(TestType.compare("accept") == 0){
			cin >> u1 >> i1 >> t1;
			cout << accept(BigArray, UserRecord, u1 - 100001, i1, t1) << endl;
		}else if(TestType.compare("items") == 0){
			cin >> u1 >> u2;
			items(BigArray, u1 - 100001, u2 - 100001);
		}else if(TestType.compare("users") == 0){
			cin >> i1 >> i2 >> t1 >> t2;
			users(BigArray, &RealUser, i1, i2, t1, t2);
		}else if(TestType.compare("ratio") == 0){
			cin >> i1 >> threshold;
			ratio(BigArray, &RealUser, i1, threshold);
		}else if(TestType.compare("findtime_item") == 0){
			cin >> i1;
			
			string input;
			getline(cin, input);
			stringstream ss(input);
			string value;
			vector<int> querylist;
			while(ss >> value){
				querylist.push_back(stoi(value));
			}
			
			findtime_item(BigArray, i1, &querylist);
			//findtime_item(BigArray, i1, UserSet);
		}
		TestLength++;
	}
	delete BigArray;
	delete UserRecord;

}

inline int accept(Head BigArray[], bool *UserRecord, int user, int item, int utime){
	
	int *item_array;
	if(UserRecord[user] == 0) return 0;

	if((item / pow(10, 6)) > 1){
		int digit_temp = 1;
		item_array = new int[8];
		item_array[0] = 7;
		while(digit_temp <= item_array[0]){
			item_array[8 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else if((item / pow(10, 5)) > 1){
		int digit_temp = 1;	
		item_array = new int[7];
		item_array[0] = 6;
		while(digit_temp <= item_array[0]){
			item_array[7 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else return 0;
	Item_Separate *tempNumber;
	for(int i = 1; i <= item_array[0]; i++){
		if(i == 1){
			if((tempNumber = BigArray[user].getNumber(item_array[i])) == NULL) {
				delete item_array;
				return 0;
			}
		}else if(i == item_array[0]){
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return 0;
			}
			if(tempNumber->IsItem()){
				delete item_array;
				return tempNumber->getResult(utime);
			}
			delete item_array;
			return 0;
		}else{
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return 0;
			}
		}
	}
}
inline bool checkItem(Head BigArray[], int user, int item){
	int *item_array;
	if((item / pow(10, 6)) > 1){
		int digit_temp = 1;
		item_array = new int[8];
		item_array[0] = 7;
		while(digit_temp <= item_array[0]){
			item_array[8 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else if((item / pow(10, 5)) > 1){
		int digit_temp = 1;	
		item_array = new int[7];
		item_array[0] = 6;
		while(digit_temp <= item_array[0]){
			item_array[7 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else return false;
	Item_Separate *tempNumber;
	for(int i = 1; i <= item_array[0]; i++){
		if(i == 1){
			if((tempNumber = BigArray[user].getNumber(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}else if(i == item_array[0]){
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
			if(tempNumber->IsItem()){
				delete item_array;
				return true;
			}
			delete item_array;
			return false;
		}else{
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}
	}
}
inline void items(Head BigArray[], int user1, int user2){
	vector<int> ItemList;

	getItemOfUserHead(BigArray, &ItemList, user1);

	for (vector<int>::iterator it = ItemList.begin() ; it != ItemList.end();){
		if(!checkItem(BigArray, user2, *it)) ItemList.erase(it);
		else ++it;
	}	

	sort(ItemList.begin(), ItemList.end());

	if(ItemList.empty()) cout << "EMPTY" << endl;
	else{
		for (vector<int>::iterator it = ItemList.begin() ; it != ItemList.end(); ++it){
			cout << *it << endl;
		}
	}
}

inline void getItemOfUserHead(Head BigArray[], vector<int> *ItemList, int user){
	for(int j = 1; j <= 9; j++){
		Item_Separate *tempNumber;
		if((tempNumber = BigArray[user].getNumber(j)) != NULL) {
			getItemOfUserNumber(tempNumber, ItemList);
		}
	}
}

inline void getItemOfUserNumber(Item_Separate *tempNumber, vector<int> *ItemList){
	Item_Separate *node;
	if(tempNumber -> IsItem()) {
		(*ItemList).push_back(tempNumber->getItem());
	}
	for(int i = 0; i <= 9; i++){
		if((node = tempNumber->getNext(i)) != NULL){
			getItemOfUserNumber(node, ItemList);
		}
	}
}

inline void users(Head BigArray[], vector<int> *RealUser, int item1, int item2, int t1, int t2){
	vector <int>user_time;
	for (vector<int>::iterator it = (*RealUser).begin() ; it != (*RealUser).end(); ++it){
		if(checkTime(BigArray, *it, item1, t1, t2)){
			if(checkTime(BigArray, *it, item2, t1, t2)){
				user_time.push_back(*it + 100001);
			}
		}
	}
	sort(user_time.begin(), user_time.end());
	if(user_time.empty()) cout << "EMPTY" << endl;
	else{
		for (vector<int>::iterator it = user_time.begin() ; it != user_time.end(); ++it){
			cout << *it << endl;
		}
	}
}

inline bool checkTime(Head BigArray[], int user, int item, int t1, int t2){
	int *item_array;
	if((item / pow(10, 6)) > 1){
		int digit_temp = 1;
		item_array = new int[8];
		item_array[0] = 7;
		while(digit_temp <= item_array[0]){
			item_array[8 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else if((item / pow(10, 5)) > 1){
		int digit_temp = 1;	
		item_array = new int[7];
		item_array[0] = 6;
		while(digit_temp <= item_array[0]){
			item_array[7 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else return 0;
	Item_Separate *tempNumber;
	for(int i = 1; i <= item_array[0]; i++){
		if(i == 1){
			if((tempNumber = BigArray[user].getNumber(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}else if(i == item_array[0]){
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
			if(tempNumber->IsItem() && tempNumber->checkTimeInterval(t1, t2)){
				delete item_array;
				return true;
			}
			delete item_array;
			return false;
		}else{
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}
	}
	
}
inline void ratio(Head BigArray[], vector<int> *RealUser, int item, int threshold){
	int total = 0, accept = 0;
	for (vector<int>::iterator it = (*RealUser).begin() ; it != (*RealUser).end(); ++it){
		if(BigArray[*it].getItemNumber() > threshold){
			total++;
			if(checkAccept(BigArray, *it, item)) accept++;
		}
	}
	cout << accept << "/" << total << endl;
}

inline bool checkAccept(Head BigArray[], int user, int item){
	int *item_array;
	if((item / pow(10, 6)) > 1){
		int digit_temp = 1;
		item_array = new int[8];
		item_array[0] = 7;
		while(digit_temp <= item_array[0]){
			item_array[8 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else if((item / pow(10, 5)) > 1){
		int digit_temp = 1;	
		item_array = new int[7];
		item_array[0] = 6;
		while(digit_temp <= item_array[0]){
			item_array[7 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else return 0;
	Item_Separate *tempNumber;
	for(int i = 1; i <= item_array[0]; i++){
		if(i == 1){
			if((tempNumber = BigArray[user].getNumber(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}else if(i == item_array[0]){
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
			if(tempNumber->IsItem() && tempNumber->isAccept()){
				delete item_array;
				return true;
			}
			delete item_array;

			return false;
		}else{
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return false;
			}
		}
	}
}

inline void useItemGetTime(Head BigArray[], int user, int item, vector<int> *TimeVector, int *Time_Record){
	int *item_array;
	if((item / pow(10, 6)) > 1){
		int digit_temp = 1;
		item_array = new int[8];
		item_array[0] = 7;
		while(digit_temp <= item_array[0]){
			item_array[8 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else if((item / pow(10, 5)) > 1){
		int digit_temp = 1;	
		item_array = new int[7];
		item_array[0] = 6;
		while(digit_temp <= item_array[0]){
			item_array[7 - digit_temp] = item % 10;
			item /= 10;
			digit_temp ++;
		}
	}else return;
	
	Item_Separate *tempNumber;
	for(int i = 1; i <= item_array[0]; i++){
		if(i == 1){
			if((tempNumber = BigArray[user].getNumber(item_array[i])) == NULL) {
				delete item_array;
				return;
			}
		}else if(i == item_array[0]){
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return;
			}
			if(tempNumber->IsItem()){
				tempNumber->getTime(TimeVector, Time_Record);
				delete item_array;
				return;
			}
			delete item_array;

			return;
		}else{
			if((tempNumber = tempNumber->getNext(item_array[i])) == NULL) {
				delete item_array;
				return;
			}
		}
	}

}

inline void findtime_item(Head BigArray[], int i1, vector<int> *querylist){
	
	vector<int>TimeVector;
	int *Time_Record;
	Time_Record = new int[2678415];
	fill(Time_Record, Time_Record + 2678415, 0);

	for (vector<int>::iterator it = (*querylist).begin() ; it != (*querylist).end(); ++it){
		useItemGetTime(BigArray, *it - 100001, i1, &TimeVector, Time_Record);
	}

	sort(TimeVector.begin(), TimeVector.end());
	if(TimeVector.empty()) cout << "EMPTY" << endl;
	else {
		for (vector<int>::iterator it = TimeVector.begin() ; it != TimeVector.end(); ++it){
		cout << *it << endl;
		}
	}
	delete Time_Record;
}
