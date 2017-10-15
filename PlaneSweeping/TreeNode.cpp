#include "stdafx.h"

TreeNode<class T>::TreeNode()
{
	left = right = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T * value)
{
	this();
	this->value = value;
}


TreeNode<class T>::~TreeNode()
{
}
