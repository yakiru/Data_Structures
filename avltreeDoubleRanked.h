#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <cstdlib>

namespace wet2 {
	class AVLTreeDoubleRanked {
	public:
        typedef struct innerNode {
        	//data
			int key; //bank or account ID
			int accountsNoORBankID; //number accounts for a bank or bank ID for account
			int heapIndex; // max heap for bank ,-1 for account
			int mainCounter; //balance
            int smallerCounter;
            int biggerCounter;
			//AVL parameters
			int rightDepth;
			int leftDepth;
			struct innerNode* father;
			struct innerNode* rightSon;
			struct innerNode* leftSon;
        } AVLTreeDoubleRankedNode;

        void balance(AVLTreeDoubleRankedNode* pNode); //balance up from the node
        void rollRR(AVLTreeDoubleRankedNode* ptrNode);
        void rollRL(AVLTreeDoubleRankedNode* ptrNode);
        void rollLL(AVLTreeDoubleRankedNode* ptrNode);
        void rollLR(AVLTreeDoubleRankedNode* ptrNode);
        void updateCountersNDepths(AVLTreeDoubleRankedNode* ptrNode);
		void removeNode(AVLTreeDoubleRankedNode* pNode);
		//void addNode(int nodeKey);
		AVLTreeDoubleRankedNode* find(int key);
		int lowestMutualAncestor(int node1Key,int node2Key);//returns father node key
		void deleteTree(AVLTreeDoubleRankedNode* node);

        //variables
        AVLTreeDoubleRankedNode* root;
		//int invalidKey;
		AVLTreeDoubleRanked (); //no nodes with mainCounter=0 
        ~AVLTreeDoubleRanked();
        AVLTreeDoubleRankedNode* addNode(int nodeKey,int accountsNoORBankID,int balance);
        AVLTreeDoubleRankedNode* findSmallerNodeByKey(AVLTreeDoubleRankedNode* node);
        AVLTreeDoubleRankedNode* findBiggerNodeByKey(AVLTreeDoubleRankedNode* node);
        //void decreaseNodeCounter(int nodeKey); //if main counter=1, node is removed, otherwise mainCounter--
        int changeNodeCounter(int nodeKey,int amount); //if node not in tree it's added and mainCounter=1, if exists mainCounter++
		int sumBetweenTwoNodes(int smallerKey, int biggerKey);
	};
}
#endif /* AVLTREE_H_ */
