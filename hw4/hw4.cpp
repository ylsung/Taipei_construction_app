
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <utility>
#include <queue>
#include <set>
#include <cstdio>

using namespace std;
class buy{
public:
	buy(int bidID_input, int ID_input, int price_input, int shareCount_input){
		bidID = bidID_input;
		ID = ID_input;
		price = price_input;
		shareCount = shareCount_input;
		position = 0;
		LeftNode = NULL;
		RightNode = NULL;
	}
	buy *addLeft(int bidID_input, int ID_input, int price_input, int shareCount_input){
		LeftNode = new buy(bidID_input, ID_input, price_input, shareCount_input);
		LeftNode->position = 1; // 1 means left
		LeftNode->parent = this;
		return LeftNode;
	}
	buy *addRight(int bidID_input, int ID_input, int price_input, int shareCount_input){
		RightNode = new buy(bidID_input, ID_input, price_input, shareCount_input);
		RightNode->position = 2; // 2 means right
		RightNode->parent = this;
		return RightNode;
	}
	buy *getRight(){
		return RightNode;
	}
	buy *getLeft(){
		return LeftNode;
	}
	int getPosition(){
		return position;
	}
	buy *getParent(){
		return parent;
	}
	int getPrice(){
		return price;
	}
	int getShare(){
		return shareCount;
	}
	int getID(){
		return ID;
	}
	int getBidID(){
		return bidID;
	}
	friend class buy_transaction;
private:
	int bidID;
	int ID;
	int price;
	int shareCount;
	buy *parent;
	buy *LeftNode;
	buy *RightNode;
	int position;
};

class sell{
public:
	sell(int bidID_input, int ID_input, int price_input, int shareCount_input){
		bidID = bidID_input;
		ID = ID_input;
		price = price_input;
		shareCount = shareCount_input;
		position = 0;
		LeftNode = NULL;
		RightNode = NULL;
	}
	sell *addLeft(int bidID_input, int ID_input, int price_input, int shareCount_input){
		LeftNode = new sell(bidID_input, ID_input, price_input, shareCount_input);
		LeftNode->position = 1; // 1 means left
		LeftNode->parent = this;
		return LeftNode;
	}
	sell *addRight(int bidID_input, int ID_input, int price_input, int shareCount_input){
		RightNode = new sell(bidID_input, ID_input, price_input, shareCount_input);
		RightNode->position = 2; // 2 means right
		RightNode->parent = this;
		return RightNode;
	}
	sell *getRight(){
		return RightNode;
	}
	sell *getLeft(){
		return LeftNode;
	}
	int getPosition(){
		return position;
	}
	sell *getParent(){
		return parent;
	}
	int getPrice(){
		return price;
	}
	int getShare(){
		return shareCount;
	}
	int getID(){
		return ID;
	}
	int getBidID(){
		return bidID;
	}
	friend class sell_transaction;
private:
	int bidID;
	int ID;
	int price;
	int shareCount;
	sell *parent;
	sell *LeftNode;
	sell *RightNode;
	int position;
};

class buy_transaction{
public:
	buy_transaction(){
		size = 0;
		head = NULL;
		tail = NULL;
	}
	buy_transaction(int bidID_input, int ID_input, int price_input, int shareCount_input){
		head = new buy(bidID_input, ID_input, price_input, shareCount_input);
		tail = head;
	}
	buy *setHead(buy *node){
		size++;
		head = node;
		tail = head;
	}
	buy* getHead(){
		return head;
	}
	int Size(){
		return size;
	}
	void addLast(int bidID_input, int ID_input, int price_input, int shareCount_input){
		buy *temp = tail;
		/* find the nearest left node */
		if(temp->getPosition() == 2){
			while(temp->getPosition() == 2){
				temp = temp->getParent();
			}
		}
		/* we found the nearest node*/
		if(temp->getPosition() == 1){
			temp = temp->getParent();
			/* the case for the left external node, we just need to find its opposite right node */
			if(temp->getRight() == NULL){
				temp->addRight(bidID_input, ID_input, price_input, shareCount_input);
				tail = temp->getRight();
			/* the case for the right external node, after we find the nearest left node, 
			   we need to find its next left node, the method is find the opposite right 
			   node of the nearest left node, and then keep going left to find the place 
			   we want */
			}else{
				temp = temp->getRight();
				while(1){
					if(temp->getLeft() == NULL){
						temp->addLeft(bidID_input, ID_input, price_input, shareCount_input);
						tail = temp->getLeft();
						break;
					}
					temp = temp->getLeft();
				}
			}
		}else if(temp->getPosition() == 0){ 
		/*last case, when the node is the last node at last depth, just like
		 the algorithm show above.*/
			while(1){
				if(temp->getLeft() == NULL){
					temp->addLeft(bidID_input, ID_input, price_input, shareCount_input);
					tail = temp->getLeft();
					break;
				}
				temp = temp->getLeft();
			}
		}
		buy *Now = tail;
		buy *Pre = tail->getParent();
		while(1){
			if(Pre->price < Now->price){
				swap(Pre->bidID, Now->bidID);
				swap(Pre->ID, Now->ID);
				swap(Pre->price, Now->price);
				swap(Pre->shareCount, Now->shareCount);
				if(Pre->getPosition() != 0){
					Now = Pre;
					Pre = Pre->getParent();
				}else{
					break;
				}
			}else{
				break;
			}
		}
		size++;
	}
void removeMax(){
	swap(head->bidID, tail->bidID);
	swap(head->ID, tail->ID);
	swap(head->price, tail->price);
	swap(head->shareCount, tail->shareCount);
	//move tail to the right place, just opposite to find new tail
	buy *temp = tail;

	if(temp->getPosition() == 1){
		while(temp->getPosition() == 1){
			temp = temp->getParent();
		}
	}
	if(temp->getPosition() == 2){
		temp = temp->getParent();
		if((temp->getLeft())->getRight() == NULL){
			temp = temp->getLeft();
		}else{
			temp = temp->getLeft();
			while(1){
				if((temp->getRight())->getRight() == NULL){
					temp = temp->getRight();
					break;
				}
				temp = temp->getRight();
			}
		}
	}else if(temp->getPosition() == 0){ 
		if(temp->getLeft() == NULL){
			head == NULL;
		}else if(temp->getRight() == NULL){
		}else{
			while(1){
				if((temp->getRight())->getRight() == NULL){
					temp = temp->getRight();
					break;
				}
				temp = temp->getRight();
			}
		}
	}

	if(tail->getPosition() == 1){
		tail->parent->LeftNode = NULL;
	}else if(tail->getPosition() == 2){
		tail->parent->RightNode = NULL;
	}else{}
	delete tail;
	tail = temp;

	//down
	buy *Now = head;
	buy *NextLeft = Now->getLeft();
	buy *NextRight = Now->getRight();
	while(1){
		if(NextRight == NULL && NextLeft == NULL) break;
		else if(NextRight == NULL){
			if(NextLeft->price >= Now->price){
				if(NextLeft->price > Now->price || NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					break;
				}else break;
			}else break;
		}else if(NextRight->price > NextLeft->price){
			if(NextRight->price >= Now->price){
				if(NextRight->price > Now->price || NextRight->bidID < Now->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}
			else{
				break;
			}
		}else if(NextRight->price < NextLeft->price){
			if(NextLeft->price >= Now->price){
				if(NextLeft->price > Now->price || NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}
			else{
				break;
			}
		}else if(NextRight->price == NextLeft->price){
			if(NextLeft->price > Now->price){
				if(NextRight->bidID > NextLeft->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else if(NextRight->bidID < NextLeft->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}else if(NextLeft->price == Now->price){
				if(NextRight->bidID > NextLeft->bidID && NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else if(NextRight->bidID < NextLeft->bidID && NextRight->bidID < Now->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}else break;
		}else break;
	}
	size--;
}

int MaxBuy(int sellprice, int share){
	if(sellprice <= head->price){
		if(share < head->shareCount){
			head->shareCount -= share;
			return 1;
		}else if(share >= head->shareCount){
			return 0;
		}
	}else return -1;
}

private:
	int size;
	buy *head;
	buy *tail;
};

class sell_transaction{
public:
	sell_transaction(){
		size = 0;
		head = NULL;
		tail = NULL;
	}
	sell_transaction(int bidID_input, int ID_input, int price_input, int shareCount_input){
		head = new sell(bidID_input, ID_input, price_input, shareCount_input);
		tail = head;
	}
	sell *setHead(sell *node){
		size++;
		head = node;
		tail = head;
	}
	sell* getHead(){
		return head;
	}
	int Size(){
		return size;
	}
	void addLast(int bidID_input, int ID_input, int price_input, int shareCount_input){
		sell *temp = tail;
		/* find the nearest left node */
		if(temp->getPosition() == 2){
			while(temp->getPosition() == 2){
				temp = temp->getParent();
			}
		}
		/* we found the nearest node*/
		if(temp->getPosition() == 1){
			temp = temp->getParent();
			/* the case for the left external node, we just need to find its opposite right node */
			if(temp->getRight() == NULL){
				temp->addRight(bidID_input, ID_input, price_input, shareCount_input);
				tail = temp->getRight();
			/* the case for the right external node, after we find the nearest left node, 
			   we need to find its next left node, the method is find the opposite right 
			   node of the nearest left node, and then keep going left to find the place 
			   we want */
			}else{
				temp = temp->getRight();
				while(1){
					if(temp->getLeft() == NULL){
						temp->addLeft(bidID_input, ID_input, price_input, shareCount_input);
						tail = temp->getLeft();
						break;
					}
					temp = temp->getLeft();
				}
			}
		}else if(temp->getPosition() == 0){ 
		/*last case, when the node is the last node at last depth, just like
		 the algorithm show above.*/
			while(1){
				if(temp->getLeft() == NULL){
					temp->addLeft(bidID_input, ID_input, price_input, shareCount_input);
					tail = temp->getLeft();
					break;
				}
				temp = temp->getLeft();
			}
		}
		sell *Now = tail;
		sell *Pre = tail->getParent();
		while(1){
			if(Pre->price > Now->price){
				swap(Pre->bidID, Now->bidID);
				swap(Pre->ID, Now->ID);
				swap(Pre->price, Now->price);
				swap(Pre->shareCount, Now->shareCount);
				if(Pre->getPosition() != 0){
					Now = Pre;
					Pre = Pre->getParent();
				}else{
					break;
				}
			}else{
				break;
			}
		}
		size++;
	}
void removeMin(){
	swap(head->bidID, tail->bidID);
	swap(head->ID, tail->ID);
	swap(head->price, tail->price);
	swap(head->shareCount, tail->shareCount);
	//move tail to the right place, just opposite to find new tail
	sell *temp = tail;

	if(temp->getPosition() == 1){
		while(temp->getPosition() == 1){
			temp = temp->getParent();
		}
	}
	if(temp->getPosition() == 2){
		temp = temp->getParent();
		if((temp->getLeft())->getRight() == NULL){
			temp = temp->getLeft();
		}else{
			temp = temp->getLeft();
			while(1){
				if((temp->getRight())->getRight() == NULL){
					temp = temp->getRight();
					break;
				}
				temp = temp->getRight();
			}
		}
	}else if(temp->getPosition() == 0){ 
		if(temp->getLeft() == NULL){
			head == NULL;
		}else if(temp->getRight() == NULL){
		}else{
			while(1){
				if((temp->getRight())->getRight() == NULL){
					temp = temp->getRight();
					break;
				}
				temp = temp->getRight();
			}
		}
	}

	if(tail->getPosition() == 1){
		tail->parent->LeftNode = NULL;
	}else if(tail->getPosition() == 2){
		tail->parent->RightNode = NULL;
	}else{}
	delete tail;
	tail = temp;

	//down
	sell *Now = head;
	sell *NextLeft = Now->getLeft();
	sell *NextRight = Now->getRight();
	while(1){
		if(NextRight == NULL && NextLeft == NULL) break;
		else if(NextRight == NULL){
			if(NextLeft->price <= Now->price){
				if(NextLeft->price < Now->price || NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					break;
				}else break;
			}
			else break;
		}else if(NextRight->price < NextLeft->price){
			if(NextRight->price <= Now->price){
				if(NextRight->price < Now->price || NextRight->bidID < Now->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}
			else{
				break;
			}
		}else if(NextRight->price > NextLeft->price){
			if(NextLeft->price <= Now->price){
				if(NextLeft->price < Now->price || NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}
			else{
				break;
			}
		}else if(NextRight->price == NextLeft->price){
			if(NextRight->price < Now->price){
				if(NextRight->bidID > NextLeft->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else if(NextRight->bidID < NextLeft->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}else if(NextRight->price == Now->price){
				if(NextRight->bidID > NextLeft->bidID && NextLeft->bidID < Now->bidID){
					swap(NextLeft->bidID, Now->bidID);
					swap(NextLeft->ID, Now->ID);
					swap(NextLeft->price, Now->price);
					swap(NextLeft->shareCount, Now->shareCount);
					Now = NextLeft;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else if(NextRight->bidID < NextLeft->bidID && NextRight->bidID < Now->bidID){
					swap(NextRight->bidID, Now->bidID);
					swap(NextRight->ID, Now->ID);
					swap(NextRight->price, Now->price);
					swap(NextRight->shareCount, Now->shareCount);
				
					Now = NextRight;
					NextLeft = Now->getLeft();
					NextRight = Now->getRight();
				}else break;
			}else break;
		}else break;
	}
	size--;
}
int MinSell(int buyprice, int share){
	if(buyprice >= head->price){
		if(share < head->shareCount){
			head->shareCount -= share;
			return 1;
		}else if(share >= head->shareCount){
			return 0;
		}
	}else return -1;
}
private:
	int size;
	sell *head;
	sell *tail;
};


int main(){
	string inputLine;
	buy_transaction *BuyList = new buy_transaction();
	sell_transaction *SellList = new sell_transaction();
	set <int> CancelList;
	set <int> ::iterator it;
	int index = 0;
	bool BuyHeadCheck = 0;
	bool SellHeadCheck = 0;
	int trasacID = 0;
	while(getline(cin, inputLine)){
		int bidID;
		int clientID;
		int action;
		int price;
		int shareCount;
		string inputElement;
		stringstream ss(inputLine);
		while(ss >> inputElement){
			if(index == 0) {
				bidID = stoi(inputElement);
				index++;
			}
			else if(index == 1){
				clientID = stoi(inputElement);
				index++;
			}else if(index == 2){
				action = stoi(inputElement);
				index++;
			}else if(index == 3){
				price = stoi(inputElement);
				index++;
			}else if(index == 4){
				shareCount = stoi(inputElement);
				index = 0;
				if(action == 2){
					CancelList.insert(price); //price is bidID in cancel case
				}
				else if(action == 0){
					if(shareCount <= 0){}
					else if(SellList->Size() == 0){
						if(shareCount != 0){
							if(BuyList->Size() == 0){
								BuyList->setHead(new buy(bidID, clientID, price, shareCount));
							}else{
								BuyList->addLast(bidID, clientID, price, shareCount);
							}
						}
					}else{
						while(SellList->Size() > 0){
							while(1){
								it = CancelList.find(SellList->getHead()->getBidID());
								if(it != CancelList.end()){
									//cout << *it << endl;
									CancelList.erase(it);
									SellList->removeMin();
									if(SellList->Size() == 0) break;
								}else {
									break;
								}
							}
							if(SellList->Size() == 0){
								if(shareCount != 0){
									if(BuyList->Size() == 0){
										BuyList->setHead(new buy(bidID, clientID, price, shareCount));
									}
									else BuyList->addLast(bidID, clientID, price, shareCount);
								}
								break;
							}
							if(price >= (SellList->getHead())->getPrice()){
								if(SellList->MinSell(price, shareCount) == 0){
									shareCount -= (SellList->getHead())->getShare();
									cout << trasacID << "\t" << clientID << "\t" << SellList->getHead()->getID()
									<< "\t" << SellList->getHead()->getPrice() << "\t" << (SellList->getHead())->getShare()
									<< endl;
									/*printf("%d\t%d\t%d\t%d\t%d\n", trasacID, clientID, SellList->getHead()->getID(),
										SellList->getHead()->getPrice(), (SellList->getHead())->getShare());*/
									trasacID++;
									SellList->removeMin();
									if(shareCount == 0) break;
									if(SellList->Size() == 0){
										if(shareCount != 0){
											if(BuyList->Size() == 0){
												BuyList->setHead(new buy(bidID, clientID, price, shareCount));
											}
											else BuyList->addLast(bidID, clientID, price, shareCount);
										}
									}

								}else{
									cout << trasacID << "\t" << clientID << "\t" << SellList->getHead()->getID()
									<< "\t" << SellList->getHead()->getPrice() << "\t" << shareCount << endl;
									/*printf("%d\t%d\t%d\t%d\t%d\n", trasacID, clientID, SellList->getHead()->getID(),
										SellList->getHead()->getPrice(), shareCount);*/
									trasacID++;
									break;
								}
							}else{
								if(shareCount != 0){
									if(BuyList->Size() == 0){
										BuyList->setHead(new buy(bidID, clientID, price, shareCount));
									}
									else BuyList->addLast(bidID, clientID, price, shareCount);
								}
								break;
							}
						}
					}
					
				}else if(action == 1){
					if(shareCount <= 0){}
					else if(BuyList->Size() == 0){
						if(shareCount != 0){
							if(SellList->Size() == 0){
								SellList->setHead(new sell(bidID, clientID, price, shareCount));
							}
							else SellList->addLast(bidID, clientID, price, shareCount);
						}
					}else{
						while(BuyList->Size() > 0){
							while(1){
								it = CancelList.find(BuyList->getHead()->getBidID());
								if(it != CancelList.end()){
									CancelList.erase(it);
									BuyList->removeMax();
									if(BuyList->Size() == 0) break;
								}else break;
							}
							if(BuyList->Size() == 0){
								if(shareCount != 0){
									if(SellList->Size() == 0){
										SellList->setHead(new sell(bidID, clientID, price, shareCount));
									}
									else SellList->addLast(bidID, clientID, price, shareCount);
								}
								break;
							}
							if(price <= (BuyList->getHead())->getPrice()){
								if(BuyList->MaxBuy(price, shareCount) == 0){
									shareCount -= (BuyList->getHead())->getShare();
									
									cout << trasacID << "\t" << BuyList->getHead()->getID() << "\t" << clientID
									<< "\t" << price << "\t" << (BuyList->getHead())->getShare()<< endl;
									
									/*printf("%d\t%d\t%d\t%d\t%d\n", trasacID, BuyList->getHead()->getID(),
										clientID, price, (BuyList->getHead())->getShare());*/
									trasacID++;
									BuyList->removeMax();
									if(shareCount == 0) break;
									if(BuyList->Size() == 0){
										if(shareCount != 0){
											if(SellList->Size() == 0){
												SellList->setHead(new sell(bidID, clientID, price, shareCount));
											}
											else SellList->addLast(bidID, clientID, price, shareCount);
										}
									}
								}else{
									
									cout << trasacID << "\t" << BuyList->getHead()->getID() << "\t" << clientID 
									<< "\t" << price << "\t" << shareCount << endl;
									/*printf("%d\t%d\t%d\t%d\t%d\n", trasacID, BuyList->getHead()->getID(),
										clientID, price, shareCount);*/
									trasacID++;
									break;
								}
							}else{
								if(shareCount != 0){
									if(SellList->Size() == 0){
										SellList->setHead(new sell(bidID, clientID, price, shareCount));
									}
									else SellList->addLast(bidID, clientID, price, shareCount);
								}
								break;
							}
						}//TODO cout the result
					}
				}
			}
		}
	}

}