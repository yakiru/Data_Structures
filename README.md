Data_Structures
===============
2 data sturctures impletmented for progamming assignments:

Ranked AVL tree : http://en.wikipedia.org/wiki/AVL_tree
Balanced binary tree based on integer key value. Insertion, deletion, balancing (using rolls)
and searching implemented.
In addition, each node has a rank to specify weight (iteration in the DS) and the weight of 
each node's child subtree is also maintained in node.
A function to sum the number of nodes (and their weight/iterations) is also implemented.
Each node has extra information specific to the task it was created for.

Binary heap (Min/Max): http://en.wikipedia.org/wiki/Binary_heap
Binary heap implemented using an array and maintaining the smaller/largest node (depending on its type
declared upon creation) in the top of the heap (first node). The array cells are AVL tree nodes that 
were used in the assignment

