#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <set>
#include <queue>
#include <cstdio>
using namespace std;
class mycomparison;

class node{
public:
	int nbidID;
	int nclientID;
	int nprice;
	int nshareCount;
	node(int n1, int n2, int n3, int n4){
		nbidID = n1;
		nclientID = n2;
		nprice = n3;
		nshareCount = n4;
	}
	friend class mycomparison;
//private:
};

class mycomparison{
public:
	mycomparison(bool input = false){
		reverse = input;
	}
	bool operator()(node *node1, node *node2){
		if(reverse){
			if(node1->nprice > node2->nprice) return 1;
			else if(node1->nprice < node2->nprice) return 0;
			else{
				if(node1->nbidID > node2->nbidID) return 1;
				else return 0;
			}
		}else{
			if(node1->nprice < node2->nprice) return 1;
			else if(node1->nprice > node2->nprice) return 0;
			else{
				if(node1->nbidID > node2->nbidID) return 1;
				else return 0;
			}
		}
	}
private:
	bool reverse; //if true, then is min heap;
};
typedef priority_queue<node*,vector<node*>,mycomparison> myqueue;
inline int MaxBuy(int sellprice, int share, myqueue *BuyList){
	if(sellprice <= BuyList->top()->nprice){
		if(share < BuyList->top()->nshareCount){
			BuyList->top()->nshareCount -= share;
			return 1;
		}else if(share >= BuyList->top()->nshareCount){
			return 0;
		}
	}else return -1;
}
inline int MinSell(int buyprice, int share, myqueue *SellList){
	if(buyprice >= SellList->top()->nprice){
		if(share < SellList->top()->nshareCount){
			SellList->top()->nshareCount -= share;
			return 1;
		}else if(share >= SellList->top()->nshareCount){
			return 0;
		}
	}else return -1;
}

inline void buy(int &trasacID, int bidID, int clientID, int price, int shareCount, myqueue *SellList, 
	myqueue *BuyList, set<int> &CancelList){
	set <int> ::iterator it;
	if(shareCount <= 0){}
	else if(SellList->size() == 0){
		BuyList->push(new node(bidID, clientID, price, shareCount));
	}else{
		while(SellList->size() > 0){
			while(1){
				it = CancelList.find(SellList->top()->nbidID);
				if(it != CancelList.end()){
					CancelList.erase(it);
					SellList->pop();
					if(SellList->size() == 0) break;
				}else {
					break;
				}
			}
			if(SellList->size() == 0){
				if(shareCount != 0){
					BuyList->push(new node(bidID, clientID, price, shareCount));
				}
				break;
			}
			if(price >= SellList->top()->nprice){
				if(MinSell(price, shareCount, SellList) == 0){
					shareCount -= SellList->top()->nshareCount;
					printf("%d\t%d\t%d\t%d\t%d\n", trasacID, clientID, SellList->top()->nclientID,
						SellList->top()->nprice, SellList->top()->nshareCount);
					trasacID++;
					SellList->pop();
					if(shareCount == 0) break;
					if(SellList->size() == 0){
						if(shareCount != 0){
							BuyList->push(new node(bidID, clientID, price, shareCount));
						}
					}

				}else{
					printf("%d\t%d\t%d\t%d\t%d\n", trasacID, clientID, SellList->top()->nclientID,
						SellList->top()->nprice, shareCount);
					trasacID++;
					break;
				}
			}else{
				if(shareCount != 0){
					BuyList->push(new node(bidID, clientID, price, shareCount));
				}
				break;
			}
		}
	}
}
inline void sell(int &trasacID, int bidID, int clientID, int price, int shareCount, myqueue *SellList, 
	myqueue *BuyList, set<int> &CancelList){
	set <int> ::iterator it;
	if(shareCount <= 0){}
	else if(BuyList->size() == 0){
		SellList->push(new node(bidID, clientID, price, shareCount));
	}else{
		while(BuyList->size() > 0){
			while(1){
				it = CancelList.find(BuyList->top()->nbidID);
				if(it != CancelList.end()){
					CancelList.erase(it);
					BuyList->pop();
					if(BuyList->size() == 0) break;
				}else break;
			}
			if(BuyList->size() == 0){
				if(shareCount != 0){
					SellList->push(new node(bidID, clientID, price, shareCount));
				}
				break;
			}
			if(price <= (BuyList->top())->nprice){
				if(MaxBuy(price, shareCount, BuyList) == 0){
					shareCount -= (BuyList->top())->nshareCount;
					printf("%d\t%d\t%d\t%d\t%d\n", trasacID, BuyList->top()->nclientID,
						clientID, price, BuyList->top()->nshareCount);
					trasacID++;
					BuyList->pop();
					if(shareCount == 0) break;
					if(BuyList->size() == 0){
						if(shareCount != 0){
							SellList->push(new node(bidID, clientID, price, shareCount));
						}
					}
				}else{
					printf("%d\t%d\t%d\t%d\t%d\n", trasacID, BuyList->top()->nclientID,
						clientID, price, shareCount);
					trasacID++;
					break;
				}
			}else{
				if(shareCount != 0){
					SellList->push(new node(bidID, clientID, price, shareCount));
				break;
				}
			}
		}
	}
}

int main(){
	typedef priority_queue<node*,vector<node*>,mycomparison> myqueue;
	int trasacID = 0;
	myqueue BuyList(mycomparison(false));
	myqueue SellList(mycomparison(true));
	set <int> CancelList;
	int bidID;
	int clientID;
	int action;
	int price;
	int shareCount;
	while(scanf("%d%d%d%d%d", &bidID, &clientID, &action, &price, &shareCount) != EOF){
		if(action == 2){
			CancelList.insert(price); //price is bidID in cancel case
		}else if(action == 0){
			buy(trasacID, bidID, clientID, price, shareCount, &SellList, &BuyList, CancelList);
		}else{
			sell(trasacID, bidID, clientID, price, shareCount, &SellList, &BuyList, CancelList);
		}
	}
	
}