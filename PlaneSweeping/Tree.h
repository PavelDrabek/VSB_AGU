#pragma once

#include "TreeNode.h"

template<typename T> class Tree
{
private:

public:
	TreeNode<T>* root = NULL;

	void Insert(T *value);
	void Insert(TreeNode<T> * node, T * value);
	void Remove(T *value);

};

