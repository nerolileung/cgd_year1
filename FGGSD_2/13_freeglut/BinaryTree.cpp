#include "BinaryTree.h"
#include <iostream>

using namespace std;

BinaryTree::BinaryTree(Branch* newRoot){
	root = newRoot;
}

BinaryTree::~BinaryTree(){
	empty(root);
}
void BinaryTree::empty(Branch* leaf) {
	delete postOrderTraverse(leaf);
};
void BinaryTree::preOrderTraverse(Branch* leaf, bool rotate) {
	leaf->data->SetRotatability(rotate);
	leaf->data->Update();
	if (leaf->left != nullptr) preOrderTraverse(leaf->left, rotate);
	if (leaf->right != nullptr) preOrderTraverse(leaf->right, rotate);
};
void BinaryTree::inOrderTraverse(Branch* leaf) {
	if (leaf->left != nullptr) inOrderTraverse(leaf->left);
	leaf->data->Draw();
	if (leaf->right != nullptr) inOrderTraverse(leaf->right);
};
Branch* BinaryTree::postOrderTraverse(Branch* leaf) {
	if (leaf->left != nullptr) postOrderTraverse(leaf->left);
	if (leaf->right != nullptr) postOrderTraverse(leaf->right);
	return leaf;
};
Branch* BinaryTree::depthFirstSearch(Branch* leaf, Vector3 targetPos) {
	Branch* answer = nullptr;
	if (leaf->data->GetPosition() == targetPos) return leaf;
	if (leaf->left != nullptr) depthFirstSearch(leaf->left, targetPos);
	if (leaf->right != nullptr) depthFirstSearch(leaf->right, targetPos);
	return answer;
};
void BinaryTree::pushLeaf(Branch* position, Branch* leaf) {
	if (position->left == nullptr) position->left = leaf;
	else if (position->right == nullptr) position->right = leaf;
	else pushLeaf(position->left, leaf);
}
void BinaryTree::popLeafAfter(Branch* position, Branch* leaf) {
	Branch* successorLeaf = nullptr;
	Branch* penultimateLeaf = nullptr;
	SceneObject* furthestRightData = nullptr;
	// leaf has single child
	if (leaf->left == nullptr && leaf->right != nullptr) successorLeaf = leaf->right;
	else if (leaf->right == nullptr && leaf->left != nullptr) successorLeaf = leaf->left;
	// leaf has two children
	else if (leaf->left != nullptr && leaf->right != nullptr) {
		penultimateLeaf = leaf;
		successorLeaf = leaf->right;
		furthestRightData = leaf->right->data;
		while (successorLeaf->right != nullptr) {
			penultimateLeaf = successorLeaf;
			successorLeaf = successorLeaf->right;
			furthestRightData = successorLeaf->data;
		}
	}
	if (position->left == leaf) {
		if (furthestRightData != nullptr) { //leaf had two children
			delete position->left->data;
			position->left->data = furthestRightData;
			popLeafAfter(penultimateLeaf, successorLeaf);
		}
		else if (successorLeaf!= nullptr) { //replace parent with only child
			delete position->left->data;
			position->left = successorLeaf;
		}
		else {
			delete position->left;
			position->left = nullptr;
		}
	}
	else if (position->right == leaf) {
		if (furthestRightData != nullptr) {
			delete position->right->data;
			position->right->data = furthestRightData;
			popLeafAfter(penultimateLeaf, successorLeaf);
		}
		else if (successorLeaf != nullptr) {
			delete position->right->data;
			position->right = successorLeaf;
		}
		else {
			delete position->right;
			position->right = nullptr;
		}
	}
	penultimateLeaf = nullptr;
	successorLeaf = nullptr;
	furthestRightData = nullptr;
}
Branch* BinaryTree::makeNewBranch(SceneObject* newData) {
	Branch* leaf = new Branch;
	leaf->data = newData;
	leaf->left = nullptr;
	leaf->right = nullptr;
	return leaf;
}
void BinaryTree::traverseDraw(Branch* leaf) {
	leaf->data->DrawStart();
	if (leaf->left != nullptr) inOrderTraverse(leaf->left);
	if (leaf->right != nullptr) inOrderTraverse(leaf->right);
	leaf->data->DrawEnd();
};
void BinaryTree::traverseUpdateColour(Branch* leaf, bool rotate) {
	leaf->data->SetRotatability(rotate);
	leaf->data->Update();
	if (leaf->left != nullptr) {
		leaf->left->data->AdjustColour();
		traverseUpdateColour(leaf->left, rotate);
	}
	if (leaf->right != nullptr) {
		leaf->right->data->AdjustColour();
		traverseUpdateColour(leaf->right, rotate);
	}
}
void BinaryTree::traverseSetColour(Branch* leaf, Material* mat) {
	leaf->data->ChangeMaterial(mat);
	if (leaf->left != nullptr) traverseSetColour(leaf->left, mat);
	if (leaf->right != nullptr) traverseSetColour(leaf->right, mat);
}
void BinaryTree::traverseSetColour(Branch* leaf, SceneObject* baseData) {
	if (leaf->left != nullptr) {
		leaf->left->data->ChangeMaterial(baseData);
		traverseSetColour(leaf->left, leaf->data);
	}
	if (leaf->right != nullptr) {
		leaf->right->data->ChangeMaterial(baseData);
		traverseSetColour(leaf->right, leaf->data);
	}
}