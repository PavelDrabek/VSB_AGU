#include "stdafx.h"

template<typename T>
void Tree<T>::Insert(T* value)
{
	Insert(root, value);
}

template<typename T>
void Tree<T>::Insert(TreeNode<T>* node, T* value)
{
	if (node == NULL) {
		node = new TreeNode(value);
	}
	else if (value < node->value) {
		Insert(node->left, value);
	}
	else {
		Insert(node->right, value);
	}
}

template<typename T>
void Tree<T>::Remove(T* value)
{
}

