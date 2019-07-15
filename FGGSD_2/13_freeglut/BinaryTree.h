#pragma once
#include "Structures.h"
#include "Cube.h"

class BinaryTree // order by x position of cube
{
public:
	BinaryTree(Branch* root);
	~BinaryTree();
	Branch* root;
	void preOrderTraverse(Branch* leaf, bool rotate);
	void inOrderTraverse(Branch* leaf);
	Branch* postOrderTraverse(Branch* leaf);
	Branch* depthFirstSearch(Branch* leaf, Vector3 targetPos);
	void pushLeaf(Branch* position, Branch* leaf);
	void popLeafAfter(Branch* position, Branch* leaf);
	Branch* makeNewBranch(SceneObject* newData);
	void traverseDraw(Branch* leaf);
	void traverseUpdateColour(Branch* leaf, bool rotate);
	void traverseSetColour(Branch* leaf, Material* mat);
	void traverseSetColour(Branch* leaf, SceneObject* baseData);
private:
	void empty(Branch* leaf);
	
};