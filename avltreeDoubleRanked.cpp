#include "avltreeDoubleRanked.h"
#include <iostream>

using namespace std;

namespace wet2 {
	int max(int num1, int num2){
		if (num1>num2) {
			return num1;
		}else return num2;
	}
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* AVLTreeDoubleRanked::find(int key){
		AVLTreeDoubleRankedNode* current = root;
		if (!root) {return NULL;}
		while (current->key != key){
			if (current->key > key && current->leftSon != NULL)
				current = current->leftSon;
			else if (current->key < key && current->rightSon != NULL)
					current = current->rightSon;
				else return current; //closest key to key reached no sons to go to
		}
		return current; //key found
	}
	void AVLTreeDoubleRanked::updateCountersNDepths(AVLTreeDoubleRankedNode* ptrNode){
		if (ptrNode==NULL) {
			return;
		}
		while(ptrNode != root){
			if (ptrNode->father->rightSon == ptrNode){
				ptrNode->father->biggerCounter=ptrNode->mainCounter+ptrNode->smallerCounter+
						ptrNode->biggerCounter;
				ptrNode->father->rightDepth=max(ptrNode->rightDepth,ptrNode->leftDepth)+1;
			}
			else {
				ptrNode->father->smallerCounter=ptrNode->mainCounter+ptrNode->smallerCounter+
						ptrNode->biggerCounter;
				ptrNode->father->leftDepth=max(ptrNode->rightDepth,ptrNode->leftDepth)+1;
			}
			ptrNode = ptrNode->father;
		}
	}

	void AVLTreeDoubleRanked::rollRR(AVLTreeDoubleRankedNode* ptrNode){
		AVLTreeDoubleRankedNode* ptrNodeSon;
		ptrNodeSon = ptrNode->rightSon;
		//every node connection is made twice: father.Xson=son and son.father=father
		if (ptrNode==root){
			ptrNodeSon->father=NULL;
			root=ptrNodeSon;
		}
		else{
			if ((ptrNode->father)->rightSon ==ptrNode){
				(ptrNode->father)->rightSon=ptrNodeSon;
			}
			else (ptrNode->father)->leftSon=ptrNodeSon;
			ptrNodeSon->father=ptrNode->father;
		}

		if (ptrNodeSon->leftSon != NULL){
			(ptrNodeSon->leftSon)->father=ptrNode;
			ptrNode->rightSon=ptrNodeSon->leftSon;
		}
		else ptrNode->rightSon=NULL;

		ptrNode->father=ptrNodeSon;
		ptrNodeSon->leftSon=ptrNode;
		//update smaller bigger counters and depths
		ptrNode->rightDepth=ptrNodeSon->leftDepth;
		ptrNodeSon->leftDepth=max(ptrNode->rightDepth,ptrNode->leftDepth)+1;

		ptrNode->biggerCounter=ptrNodeSon->smallerCounter;
		ptrNodeSon->smallerCounter=ptrNode->biggerCounter+ptrNode->smallerCounter+ptrNode->mainCounter;

	}

	void AVLTreeDoubleRanked::rollRL(AVLTreeDoubleRankedNode* ptrNode){
		AVLTreeDoubleRankedNode* ptrNodeSon;
		ptrNodeSon = ptrNode->rightSon;
		AVLTreeDoubleRankedNode* ptrNodeGrandSon;
		ptrNodeGrandSon = ptrNodeSon->leftSon;
		//every node connection is made twice: father.Xson=son and son.father=father
		if (ptrNode==root){
			ptrNodeGrandSon->father=NULL;
			root=ptrNodeGrandSon;
		}
		else{
			if ((ptrNode->father)->rightSon ==ptrNode){
				(ptrNode->father)->rightSon=ptrNodeGrandSon;
			}
			else (ptrNode->father)->leftSon=ptrNodeGrandSon;
			ptrNodeGrandSon->father=ptrNode->father;
		}

		if (ptrNodeGrandSon->leftSon != NULL){
			(ptrNodeGrandSon->leftSon)->father=ptrNode;
			ptrNode->rightSon=ptrNodeGrandSon->leftSon;
		}
		else ptrNode->rightSon=NULL;

		if (ptrNodeGrandSon->rightSon != NULL){
			(ptrNodeGrandSon->rightSon)->father=ptrNodeSon;
			ptrNodeSon->leftSon=ptrNodeGrandSon->rightSon;
		}
		else ptrNodeSon->leftSon=NULL;

		ptrNode->father=ptrNodeGrandSon;
		ptrNodeGrandSon->leftSon=ptrNode;

		ptrNodeSon->father=ptrNodeGrandSon;
		ptrNodeGrandSon->rightSon=ptrNodeSon;

		//update smaller bigger counters and depths
		ptrNode->rightDepth=ptrNodeGrandSon->leftDepth;
		ptrNodeSon->leftDepth=ptrNodeGrandSon->rightDepth;
		ptrNodeGrandSon->leftDepth=max(ptrNode->leftDepth,ptrNode->rightDepth)+1;
		ptrNodeGrandSon->rightDepth=max(ptrNodeSon->leftDepth,ptrNodeSon->rightDepth)+1;

		ptrNode->biggerCounter=ptrNodeGrandSon->smallerCounter;
		ptrNodeSon->smallerCounter=ptrNodeGrandSon->biggerCounter;
		ptrNodeGrandSon->smallerCounter=ptrNode->biggerCounter+ptrNode->smallerCounter+ptrNode->mainCounter;
		ptrNodeGrandSon->biggerCounter=ptrNodeSon->biggerCounter+ptrNodeSon->smallerCounter+ptrNodeSon->mainCounter;
	}
	void AVLTreeDoubleRanked::rollLL(AVLTreeDoubleRankedNode* ptrNode){
		AVLTreeDoubleRankedNode* ptrNodeSon;
		ptrNodeSon = ptrNode->leftSon;
		//every node connection is made twice: father.Xson=son and son.father=father
		if (ptrNode==root){
			ptrNodeSon->father=NULL;
			root=ptrNodeSon;
		}
		else{
			if ((ptrNode->father)->rightSon ==ptrNode){
				(ptrNode->father)->rightSon=ptrNodeSon;
			}
			else (ptrNode->father)->leftSon=ptrNodeSon;
			ptrNodeSon->father=ptrNode->father;
		}

		if (ptrNodeSon->rightSon != NULL){
			(ptrNodeSon->rightSon)->father=ptrNode;
			ptrNode->leftSon=ptrNodeSon->rightSon;
		}
		else ptrNode->leftSon=NULL;

		ptrNode->father=ptrNodeSon;
		ptrNodeSon->rightSon=ptrNode;
		//update smaller bigger counters and depths
		ptrNode->leftDepth=ptrNodeSon->rightDepth;
		ptrNodeSon->rightDepth=max(ptrNode->rightDepth,ptrNode->leftDepth)+1;

		ptrNode->smallerCounter=ptrNodeSon->biggerCounter;
		ptrNodeSon->biggerCounter=ptrNode->biggerCounter+ptrNode->smallerCounter+ptrNode->mainCounter;
	}
	void AVLTreeDoubleRanked::rollLR(AVLTreeDoubleRankedNode* ptrNode){
		AVLTreeDoubleRankedNode* ptrNodeSon;
		ptrNodeSon = ptrNode->leftSon;
		AVLTreeDoubleRankedNode* ptrNodeGrandSon;
		ptrNodeGrandSon = ptrNodeSon->rightSon;
		//every node connection is made twice: father.Xson=son and son.father=father
		if (ptrNode==root){
			ptrNodeGrandSon->father=NULL;
			root=ptrNodeGrandSon;
		}
		else{
			if ((ptrNode->father)->rightSon ==ptrNode){
				(ptrNode->father)->rightSon=ptrNodeGrandSon;
			}
			else (ptrNode->father)->leftSon=ptrNodeGrandSon;
			ptrNodeGrandSon->father=ptrNode->father;
		}

		if (ptrNodeGrandSon->rightSon != NULL){
			(ptrNodeGrandSon->rightSon)->father=ptrNode;
			ptrNode->leftSon=ptrNodeGrandSon->rightSon;
		}
		else ptrNode->leftSon=NULL;

		if (ptrNodeGrandSon->leftSon != NULL){
			(ptrNodeGrandSon->leftSon)->father=ptrNodeSon;
			ptrNodeSon->rightSon=ptrNodeGrandSon->leftSon;
		}
		else ptrNodeSon->rightSon=NULL;

		ptrNode->father=ptrNodeGrandSon;
		ptrNodeGrandSon->rightSon=ptrNode;

		ptrNodeSon->father=ptrNodeGrandSon;
		ptrNodeGrandSon->leftSon=ptrNodeSon;
		//update smaller bigger counters and depths
		ptrNodeSon->rightDepth=ptrNodeGrandSon->leftDepth;
		ptrNode->leftDepth=ptrNodeGrandSon->rightDepth;
		ptrNodeGrandSon->leftDepth=max(ptrNodeSon->rightDepth,ptrNodeSon->leftDepth)+1;
		ptrNodeGrandSon->rightDepth=max(ptrNode->rightDepth,ptrNode->leftDepth)+1;

		ptrNode->smallerCounter=ptrNodeGrandSon->biggerCounter;
		ptrNodeSon->biggerCounter=ptrNodeGrandSon->smallerCounter;
		ptrNodeGrandSon->biggerCounter=ptrNode->biggerCounter+ptrNode->smallerCounter+ptrNode->mainCounter;
		ptrNodeGrandSon->smallerCounter=ptrNodeSon->biggerCounter+ptrNodeSon->smallerCounter+ptrNodeSon->mainCounter;
	}

	void AVLTreeDoubleRanked::balance(AVLTreeDoubleRankedNode* ptrNode){ //balance checked up to root - for remove and add
		bool balanceFlag=false;
		AVLTreeDoubleRankedNode* ptrTempNode;
		ptrTempNode = ptrNode->father;
		AVLTreeDoubleRankedNode* ptrPreviousTempNode;
		ptrPreviousTempNode=ptrNode;
		int ptrTempNodeBF,ptrPreviousTempNodeBF;
		while (ptrTempNode!=NULL){ //reached root (root.father=NULL)
			ptrTempNodeBF= ptrTempNode->leftDepth- ptrTempNode->rightDepth;
			ptrPreviousTempNodeBF = ptrPreviousTempNode->leftDepth- ptrPreviousTempNode->rightDepth;
			if (abs(ptrTempNodeBF) == 2 ){ //illegal balance factor
				switch (ptrTempNodeBF){
					case 2: {
						if (ptrPreviousTempNodeBF == -1) {
							rollLR(ptrTempNode);
							ptrTempNode= ptrTempNode->father;//ptrPreviousTempNode->father;
							balanceFlag=true;
						}
						else {
							rollLL(ptrTempNode);
							ptrTempNode= ptrTempNode->father;//earlier:ptrPreviousTempNode->leftSon;
							balanceFlag=true;
						}
					break;
					}
					case (-2): {
						if (ptrPreviousTempNodeBF == 1) {
							rollRL(ptrTempNode);
							ptrTempNode= ptrTempNode->father;//ptrPreviousTempNode->father;
							balanceFlag=true;
						}
						else {
							rollRR(ptrTempNode);
							ptrTempNode= ptrTempNode->father;//ptrPreviousTempNode->rightSon;
							balanceFlag=true;
						}
					break;
					}
				}
			}
			if (balanceFlag==true){
				updateCountersNDepths(ptrTempNode);
				balanceFlag=false;
			}
			ptrPreviousTempNode=ptrTempNode;
			ptrTempNode=ptrTempNode->father;
		}
	}
/**********************************************************************************
Public functions
**********************************************************************************/
	AVLTreeDoubleRanked::AVLTreeDoubleRanked ():root(NULL){}

	void AVLTreeDoubleRanked::deleteTree(AVLTreeDoubleRankedNode* node){
		if (!node) return;
		deleteTree(node->rightSon);
		deleteTree(node->leftSon);
		delete node;
	}

	AVLTreeDoubleRanked::~AVLTreeDoubleRanked() {
		deleteTree(root);
	}
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* AVLTreeDoubleRanked::findSmallerNodeByKey(AVLTreeDoubleRankedNode* node){
		AVLTreeDoubleRankedNode* ptrTempNode=NULL;
		if (node->leftSon != NULL) {
			ptrTempNode = node->leftSon; //one left and right till reaching leaf to find closest smaller on left branch
			while (ptrTempNode->rightSon != NULL) { 
				ptrTempNode=ptrTempNode->rightSon;
			}
		}
		AVLTreeDoubleRankedNode* ptrCandidate1=ptrTempNode;
		ptrTempNode=node;
		//going up tree looking for closest smaller
		while (1){
			if (ptrTempNode->father!= NULL) {
				if((ptrTempNode->father)->key > node->key){
					ptrTempNode=ptrTempNode->father;
				}
				else {
					ptrTempNode=ptrTempNode->father; //first smaller
					break;
					}
			}
			else {
				ptrTempNode=ptrTempNode->father; //reached root return NULL
					break;
				}
		}
		AVLTreeDoubleRankedNode* ptrCandidate2=ptrTempNode;
		if ( ptrCandidate1 != NULL) {
			if( ptrCandidate2 !=NULL && ptrCandidate2->key != node->key ) {
				int delta1;
				delta1 = node->key - ptrCandidate1->key;
				int delta2;
				delta2 = node->key-ptrCandidate2->key;
				return (delta1 < delta2) ? ptrCandidate1 : ptrCandidate2;
			}
			else return ptrCandidate1;
		}

		else if (ptrCandidate2 !=NULL && ptrCandidate2->key != node->key) {
				return ptrCandidate2;
			}
			else return NULL;
		return NULL; //just to eliminate warning
	}
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* AVLTreeDoubleRanked::findBiggerNodeByKey(AVLTreeDoubleRankedNode* node){
		AVLTreeDoubleRankedNode* ptrTempNode=NULL;
		if (node->rightSon != NULL) {

			ptrTempNode = node->rightSon; //one right and left till reaching leaf to find closest bugger on right branch
			while (ptrTempNode->leftSon != NULL) { 
				ptrTempNode=ptrTempNode->leftSon;
			}
		}
		AVLTreeDoubleRankedNode* ptrCandidate1=ptrTempNode;
		ptrTempNode=node;
		//going up tree looking for closest bigger
		while (1){
			if (ptrTempNode->father!= NULL) {
				if((ptrTempNode->father)->key < node->key){
					ptrTempNode=ptrTempNode->father;
				}
				else {
					ptrTempNode=ptrTempNode->father; //first bigger
					break;
					}
			}
			else {
				ptrTempNode=ptrTempNode->father; //reached root return NULL
					break;
				}
		}
		AVLTreeDoubleRankedNode* ptrCandidate2=ptrTempNode;
		if (ptrCandidate1 !=NULL ) {
			if (ptrCandidate2 !=NULL && ptrCandidate2->key != node->key) {
				int delta1;
				delta1 = ptrCandidate1->key-node->key;
				int delta2;
				delta2 = ptrCandidate2->key-node->key;
				return (delta1 < delta2) ? ptrCandidate1 : ptrCandidate2;
			}
			else return ptrCandidate1;
		}
		else if (ptrCandidate2 !=NULL && ptrCandidate2->key != node->key) {
				return ptrCandidate2;
			}
			else return NULL;
	}
	int AVLTreeDoubleRanked::lowestMutualAncestor(int node1Key,int node2Key){ //finding root of minimum subtree of 2 nodes
		AVLTreeDoubleRankedNode* ptrTempNode;
		ptrTempNode=root;
		while (1){ //loop broken by inside terms
			if ((ptrTempNode->key == node1Key) || (ptrTempNode->key == node2Key)) break; //one node is father of other
			if ((ptrTempNode->key > node1Key) && (ptrTempNode->key > node2Key)) { //going left together?
				ptrTempNode= ptrTempNode->leftSon;
				continue;
			}
			if ((ptrTempNode->key < node1Key) && (ptrTempNode->key < node2Key)) { //going right together?
				ptrTempNode= ptrTempNode->rightSon;
				continue;
			}
			else break; //routes to nodes split on lowest mutual ancestor
		}
		return ptrTempNode->key;
	}

	int AVLTreeDoubleRanked::sumBetweenTwoNodes(int smallerKey, int biggerKey){
		AVLTreeDoubleRankedNode* tempLowNode = find(smallerKey);
		while (tempLowNode!=NULL && tempLowNode->key < smallerKey) //in case highest party found is lower than low limit
			tempLowNode = findBiggerNodeByKey(tempLowNode);
		AVLTreeDoubleRankedNode* tempHighNode = find(biggerKey);
		while (tempHighNode!=NULL && tempHighNode->key > biggerKey)//in case lowest party found is higher than high limit
			tempHighNode = findSmallerNodeByKey(tempHighNode);
		if (tempLowNode==NULL || tempHighNode==NULL || tempLowNode->key < smallerKey || tempHighNode->key >biggerKey
				|| tempLowNode->key > tempHighNode->key){
			return 0;
		}



		int fatherKey = lowestMutualAncestor(smallerKey,biggerKey);
		AVLTreeDoubleRankedNode* prealSmallerKey = tempLowNode;//find(smallerKey);
		AVLTreeDoubleRankedNode* prealbiggerKey = tempHighNode;//find(biggerKey);
		int counter =0;
		AVLTreeDoubleRankedNode* tempCurrentNode = prealSmallerKey;
		AVLTreeDoubleRankedNode* tempPreviousNode = prealSmallerKey;

		if (tempCurrentNode->key != fatherKey){
				counter += tempCurrentNode->biggerCounter;
		}
		while (tempCurrentNode->key != fatherKey) {
			if (tempCurrentNode->leftSon==tempPreviousNode) { //going up and right (coming from left son)
				counter += tempCurrentNode->biggerCounter;
			}
			if (tempCurrentNode->key >= smallerKey && tempCurrentNode->key <= biggerKey){
				counter += tempCurrentNode->mainCounter;
			}
			tempPreviousNode=tempCurrentNode;
			tempCurrentNode=tempCurrentNode->father;
		}//stopping when current node is the mutual father
		counter += tempCurrentNode->mainCounter; //summing father counter
		tempCurrentNode=tempPreviousNode = prealbiggerKey;
		//tempPreviousNode = prealSmallerKey;
		if (tempCurrentNode->key != fatherKey){
			counter+=tempCurrentNode->smallerCounter;
		}
		while (tempCurrentNode->key != fatherKey) {
			if (tempCurrentNode->rightSon==tempPreviousNode) { //going up and left (coming from right son)
				counter += tempCurrentNode->smallerCounter;
			}
			if (tempCurrentNode->key >= smallerKey && tempCurrentNode->key <= biggerKey){
				counter += tempCurrentNode->mainCounter;
			}
			tempPreviousNode=tempCurrentNode;
			tempCurrentNode=tempCurrentNode->father;
		}//stopping when current node is the mutual father
		return counter;
	}

	int AVLTreeDoubleRanked::changeNodeCounter(int nodeKey, int amount) {
		AVLTreeDoubleRankedNode* tempNode= find(nodeKey);
		if (tempNode==NULL){
			return 0;
		}
		else tempNode->mainCounter+=amount;
		return 1;
	}

	//REMOVE NODE
	void AVLTreeDoubleRanked::removeNode(AVLTreeDoubleRankedNode* currentNode) {
		if (currentNode == NULL) {
			return;
		}
		AVLTreeDoubleRankedNode* parent = currentNode->father;
		if (currentNode->rightSon && currentNode->leftSon){
			AVLTreeDoubleRankedNode* nextNode = currentNode->rightSon;
			while (nextNode->leftSon)
				nextNode = nextNode->leftSon;
			AVLTreeDoubleRankedNode* nextNodeTemp;

			if (nextNode->rightSon){
				nextNodeTemp= nextNode->rightSon; //save right son
				(nextNode->rightSon)->father=nextNode->father;
				if ((nextNode->father)->rightSon==nextNode) {
					(nextNode->father)->rightSon=nextNodeTemp;
				}
				else (nextNode->father)->leftSon=nextNodeTemp;
				nextNodeTemp->father=nextNode->father;
				updateCountersNDepths(nextNode->rightSon);
			}
			else{
				nextNodeTemp= nextNode->father; ///save father
				if (nextNodeTemp->rightSon==nextNode) {
					nextNodeTemp->biggerCounter=0;
					nextNodeTemp->rightDepth=0;
					nextNodeTemp->rightSon=NULL;
				}
				else {
					nextNodeTemp->smallerCounter=0;
					nextNodeTemp->leftDepth=0;
					nextNodeTemp->leftSon=NULL;
				}
				updateCountersNDepths(nextNode->father);
			}
			if (parent==NULL){
				root=nextNode;
				nextNode->father=NULL;
			}
			else {
				if ((currentNode->father)->rightSon==currentNode) {
					(currentNode->father)->rightSon=nextNode;
				}
				else {
					(currentNode->father)->leftSon=nextNode;
				}
				nextNode->father=currentNode->father;
			}
			nextNode->leftSon=currentNode->leftSon;
			nextNode->smallerCounter=currentNode->smallerCounter;
			nextNode->leftDepth=currentNode->leftDepth;
			nextNode->rightSon=currentNode->rightSon;
			nextNode->biggerCounter=currentNode->biggerCounter;
			nextNode->rightDepth=currentNode->rightDepth;
			if (currentNode->rightSon) {
				(currentNode->rightSon)->father=nextNode;
			}
			if (currentNode->leftSon) {
				(currentNode->leftSon)->father=nextNode;
			}
			updateCountersNDepths(nextNode);
			balance(nextNode);
			delete currentNode;
			return;
		}
		if (currentNode->rightSon == currentNode->leftSon){ // meaning they are both NULL
			if (currentNode==root){ //deleting only node
				delete currentNode;
				root=NULL;
				return;
			}
			else {
				if (parent->rightSon == currentNode) {
					parent->biggerCounter=0;
					parent->rightDepth=0;
					parent->rightSon=NULL;
				}
				else {
					parent->smallerCounter=0;
					parent->leftDepth=0;
					parent->leftSon=NULL;
				}
				updateCountersNDepths(parent);
				delete currentNode;
				if (parent->rightSon) 
					balance(parent->rightSon);
				else if (parent->leftSon)
					balance(parent->leftSon);
				else
					balance(parent);
				return;
			}
		}
		if (currentNode->rightSon && !currentNode->leftSon){ //current only has rightSon
			AVLTreeDoubleRankedNode* currentNodeRight = currentNode->rightSon;
			if (parent==NULL){
				root=currentNodeRight;
				currentNodeRight->father=NULL;
			}
			else {
				if(parent->rightSon == currentNode){
					parent->rightSon = currentNodeRight;
					currentNode->rightSon->father = parent;
				} else {
					parent->leftSon = currentNodeRight;
					currentNode->rightSon->father = parent;
				}
			}
			updateCountersNDepths(currentNodeRight);
			balance(currentNodeRight);
			delete currentNode;
			return;
		}
		if (currentNode->leftSon && !currentNode->rightSon){ // current only has leftSon
			AVLTreeDoubleRankedNode* currentNodeLeft = currentNode->leftSon;
			if (parent==NULL){
				root=currentNodeLeft;
				currentNodeLeft->father=NULL;
			}
			else {
					if (parent->rightSon == currentNode){
						parent->rightSon = currentNode->leftSon;
						currentNodeLeft->father = parent;
					} else {
						parent->leftSon = currentNode->leftSon;
						currentNodeLeft->father = parent;
					}
			}
			updateCountersNDepths(currentNodeLeft);
			balance(currentNodeLeft);
			delete currentNode;
			return;
		}
	}
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* AVLTreeDoubleRanked::addNode
	(int nodeKey,int accountsNoORBankID, int balance)
	{
		AVLTreeDoubleRankedNode* currentNode = root;
		if (!root) {
			root = new AVLTreeDoubleRankedNode;
			root->father = root->leftSon = root->rightSon = NULL;
			root->leftDepth = root->rightDepth = 0;
			root->key=nodeKey;
			root->accountsNoORBankID=accountsNoORBankID;
			root->mainCounter=balance;
			root->smallerCounter=root->biggerCounter=0;
			return root;
		}
		while(1) {
			if (currentNode->key > nodeKey && !(currentNode->leftSon)){ //going left when no left son
				currentNode->leftSon = new AVLTreeDoubleRankedNode;
				currentNode->leftSon->father = currentNode;
				currentNode = currentNode -> leftSon;
				currentNode->leftSon = currentNode->rightSon = NULL;
				currentNode->key=nodeKey;
				currentNode->accountsNoORBankID=accountsNoORBankID;
				currentNode->mainCounter=balance;
				currentNode->smallerCounter=currentNode->biggerCounter=0;
				currentNode->leftDepth = currentNode->rightDepth = 0;
				updateCountersNDepths(currentNode);
				this->balance(currentNode);
				return currentNode;
			}
			if (currentNode->key > nodeKey){ //going left 
				currentNode = currentNode->leftSon;
				continue;
			}
			if (currentNode->key < nodeKey && !(currentNode->rightSon)) { //going right when no right son
				currentNode->rightSon = new AVLTreeDoubleRankedNode;
				currentNode->rightSon->father = currentNode;
				currentNode = currentNode -> rightSon;
				currentNode->leftSon = currentNode->rightSon = NULL;
				currentNode->key=nodeKey;
				currentNode->accountsNoORBankID=accountsNoORBankID;
				currentNode->mainCounter=balance;
				currentNode->smallerCounter=currentNode->biggerCounter=0;
				currentNode->leftDepth = currentNode->rightDepth = 0;
				updateCountersNDepths(currentNode);
				this->balance(currentNode);
				return currentNode;
			}
			if (currentNode->key < nodeKey){ //going right 
				currentNode = currentNode->rightSon;
				continue;
			}
		}
		return NULL;//to eliminate warning
	}

} // namespace
