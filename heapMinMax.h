/*
 * heap.h
 *
 *  Created on: 11/06/2012
 *      Author: Yakir
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <stdlib.h>
#include "avltreeDoubleRanked.h"

namespace wet2 {
	class heapMinMax {
	private:
		int initialSize;
		int currentSize;
		int firstEmpty;
		bool heapTypeMax;

        void doubleSize();
        void halfSize();
	bool isFirstBankSmaller(int indexA,int indexB);
	int smallestBetweenIndexAndSons(int heapIndex);
	int biggestBetweenIndexAndSons(int heapIndex);
	void switchNodes(AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** A,
			AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** B);

	public:
	AVLTreeDoubleRanked::AVLTreeDoubleRankedNode** nodeArray;
	int siftDown(int index); //balance down from the node
        int siftUp(int index);   //balance up from the node

        heapMinMax(int size, bool maxHeap); //only MAX heap implemented!
        ~heapMinMax();
        AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* findTop();
        void removeTop();
        int addNode(AVLTreeDoubleRanked::AVLTreeDoubleRankedNode* pData);
        void removeNode(int indexToRemove);
 };
}
#endif /* HEAP_H_ */
