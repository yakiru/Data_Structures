/*
 * heap.cpp
 *
 *  Created on: 11/06/2012
 *      Author: Yakir
 */
#include <stdlib.h>
#include <cmath>
#include "heapMinMax.h"

namespace wet2{

bool heapMinMax::isFirstBankSmaller(int indexA,int indexB){
	if (nodeArray[indexA]->mainCounter < nodeArray[indexB]->mainCounter){//smaller balance
		return true;
	}
	else if (nodeArray[indexA]->mainCounter > nodeArray[indexB]->mainCounter){//bigger balance
		return false;
	}
	else if (nodeArray[indexA]->key > nodeArray[indexB]->key){//same balance
		return true;
	}
	else return false;
}
int heapMinMax::smallestBetweenIndexAndSons(int heapIndex){
	if ((heapIndex*2+1) < firstEmpty){ //nodeArray[index] has 2 sons
		if (isFirstBankSmaller(heapIndex*2,heapIndex*2+1)) { //is left son smaller
			if (!isFirstBankSmaller(heapIndex,2*heapIndex)) //is left son smaller than father
				return (2*heapIndex);
			else return heapIndex;
		}
		else if (!isFirstBankSmaller(heapIndex,2*heapIndex+1)) //is right son smaller than father
				return (2*heapIndex+1);
			else return heapIndex;
		}
	else if (heapIndex*2 < firstEmpty){//nodeArray[index] has only left son
			if (!isFirstBankSmaller(heapIndex,2*heapIndex)) //is left son smaller than father
				return (2*heapIndex);
			else return (heapIndex);
	}
	return heapIndex;
}
int heapMinMax::biggestBetweenIndexAndSons(int heapIndex){
	if (heapIndex*2+1 < firstEmpty){ //nodeArray[index] has 2 sons
		if (!isFirstBankSmaller(heapIndex*2,heapIndex*2+1)) { //is left son bigger than right
			if (isFirstBankSmaller(heapIndex,2*heapIndex)) //is left son bigger than father
				return 2*heapIndex;
			else return heapIndex;
		}
		else if (isFirstBankSmaller(heapIndex,2*heapIndex+1)) //is right son bigger than father
				return (2*heapIndex+1);
			else return heapIndex;
	}
	else if (heapIndex*2 < firstEmpty){ //nodeArray[index] has only left son
			if (isFirstBankSmaller(heapIndex,2*heapIndex)){ //is left son bigger than father
				return (2*heapIndex);
			}
			else return heapIndex;
	}
	return heapIndex;
}
void heapMinMax::switchNodes(AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** A,
		AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** B){
	int tempIndex;
	tempIndex=(*A)->heapIndex;
	(*A)->heapIndex=(*B)->heapIndex;
	(*B)->heapIndex=tempIndex;
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* tempPointer=*A;
	*A=*B;
	*B=tempPointer;
}
void heapMinMax::doubleSize(){ //reallocate and copy
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** tempArray=
			new AVLTreeDoubleRanked::AVLTreeDoubleRankedNode*[currentSize*2]; //first cell=index 0 is garbage.
	for (int i=0; i<currentSize; i++){
		tempArray[i]=nodeArray[i];
	}
	currentSize=currentSize*2;
	delete[] nodeArray;
	nodeArray=tempArray;
}
void heapMinMax::halfSize(){ //reallocate and copy
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** tempArray=
			new AVLTreeDoubleRanked::AVLTreeDoubleRankedNode*[currentSize/2]; //first cell=index 0 is garbage.
	for (int i=0; i<(currentSize/2); i++){
		tempArray[i]=nodeArray[i];
	}
	currentSize=currentSize/2;
	delete[] nodeArray;
	nodeArray=tempArray;
}
heapMinMax::heapMinMax(int size, bool maxHeap) :
		initialSize(size),firstEmpty(1),heapTypeMax(maxHeap)
{
	currentSize= (int)pow(2,ceil(log2(size+1)))-1+1; //geometric series sum and first cell(index=0) is garbage
	nodeArray=new AVLTreeDoubleRanked::AVLTreeDoubleRankedNode*[currentSize];
};
heapMinMax::~heapMinMax(){
	delete[] nodeArray;
}
AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* heapMinMax:: findTop(){
	if (firstEmpty!=1){
		return nodeArray[1];
	}
	else return 0;
}

void heapMinMax::removeTop(){
	nodeArray[1]=nodeArray[firstEmpty-1];
	nodeArray[1]->heapIndex=1;
	firstEmpty--;
	siftDown(1);
}
int heapMinMax::addNode(AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* pData ){
	if (firstEmpty==currentSize) {
		doubleSize();
	}
	nodeArray[firstEmpty]=pData;
	pData->heapIndex=firstEmpty;
	firstEmpty++;
	return siftUp(firstEmpty-1); //TODO
}

/*void heapMinMax::removeNode(int indexToRemove){
	switchNodes(&nodeArray[indexToRemove],&nodeArray[firstEmpty-1]);
	firstEmpty--;
	
	if (heapTypeMax){ //MAX heap
		if (indexToRemove/2 >= 1 && !isFirstBankSmaller(indexToRemove,indexToRemove/2)){
			siftUp(indexToRemove);
			return;
		}
		int biggest=biggestBetweenIndexAndSons(indexToRemove);
		if (biggest!=indexToRemove){
			siftDown(indexToRemove);
		}
	}
	if (firstEmpty<0.3*currentSize){
		halfSize();
	}
	
}*/

int heapMinMax::siftDown(int index){
	//int index=currentSize/2;
	if (index==0){ //general reorder of heap
		index=(firstEmpty-1)/2; //index start from 0 in the array
		while (index>1){
			if (heapTypeMax){ //maximum heap
				int biggestIndex=biggestBetweenIndexAndSons(index);
				if (biggestIndex!=index){
					switchNodes(&nodeArray[index],&nodeArray[biggestIndex]);
				}
			}
			//TODO minimum heap
			index--;
		}
		return 0;
	}
	else {//specific sift down of one node
		while (index<firstEmpty-1){
			if (heapTypeMax){ //maximum heap
				int biggestIndex=biggestBetweenIndexAndSons(index);
				if (biggestIndex!=index){
					switchNodes(&nodeArray[index],&nodeArray[biggestIndex]);
					index=biggestIndex;
				}
				else break;
			}
			//TODO minimum heap
		}
		return index;
	}
}
int heapMinMax::siftUp(int index){
	while (index>1){
		if (heapTypeMax){ //maximum heap
			if (!isFirstBankSmaller(index,index/2)) { //is bigger than father
				switchNodes(&nodeArray[index],&nodeArray[index/2]);
				if (index/2 >= 1) {
					index=index/2;
				}
				else return index; //index =1
			}
			else return index;
		}
		//TODO minimum heap
	}
	return index;
}

}//namespace end
