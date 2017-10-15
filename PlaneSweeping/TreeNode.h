#pragma once

template <class T> class TreeNode
{
public:
	TreeNode();
	TreeNode(T* value);
	~TreeNode();

	T* value;
	TreeNode *left;
	TreeNode* right;

	bool IsLeaf();
	bool IsRoot();
};

