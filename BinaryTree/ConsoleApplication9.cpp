
#include "BinaryTree.h"
#include "TreeNode.h"
#include <iostream>

void CreateMinimalBST(int* start, int first, int end, BinaryTree* tree)
{
    if(end == first)
        tree->Insert(start[first]);
    else
    {
        int indxHead = (end - first) / 2 + first;
        tree->Insert(start[indxHead]);
        if (indxHead != first)
            CreateMinimalBST(start, first, indxHead - 1, tree);
        if(indxHead != end)
            CreateMinimalBST(start, indxHead + 1, end, tree);
    }
}

int main()
{
    int array[] = { 1,2,3,4,5 };
    BinaryTree tree;
    CreateMinimalBST(array, 0, sizeof(array)/sizeof(&array) - 1, &tree);
}
