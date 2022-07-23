// Binary Tree
/*
implementation same as fancy list, dynamic array that curr el and size is kept track of

PARENT AND CHILDREN

    child1 = 2*i + 1
    child2 = 2*i + 2

    parent = (i - 2)/2 or (i-1)/2
        depends on if left or right child == even vs odd index
        need (i % 2 == 0) check

HEIGHT
n = w^(h+1) -1
h = O(log n) // height scales with log n -> layers
*/

// Heaps
/*
requirements: complete binary tree, descendents must all be bigger / larger

insert: check against parents, move up/down to parents spot until heap condition satisfied
    inserting from left because complete binary tree
    O(logn)

pop: delete root, then replace by last element and bubble down
    gives O(log n) which is better than O(n) - shifting everything left 1

learn how to bubble up and down

*/

// BINARY SEARCH TREES
/*
implemented as linked list of TreeNode

struct TreeNode(){
    int value;
    struct Treenode *right;
    struct Treenode *left;
    struct Treenode *parent;
}TreeNode;

order of insertion can affect tree strucutre -> balanced or unbalanced
    best to try to force tree into logn (make balanced)

deleting nodes with two children with children
    choose leaf so theres less bubbling (either max on left side, or min on right side)
    goal is to find node that causes least rewiring if possible

*/