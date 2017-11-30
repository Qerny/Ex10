// Ex10.cpp: определяет точку входа для консольного приложения. 
// 

#include "stdafx.h" 
#include<iostream> 
#include <algorithm> 


using namespace std;

template <typename T>
class BinaryTree
{
private:
	
	T key;
	BinaryTree* left;
	BinaryTree* right;

public:
	BinaryTree()
	{
		left = right = nullptr;
	}

	BinaryTree(T key)
	{
		this->key = key;
		left = right = nullptr;
	}

	BinaryTree* Min()
	{
		if (this->left == nullptr)
			return this;
		return this->left->Min();
	}

	void AddNode(T key)
	{
		if (key < this->key)
		{
			if (this->left != nullptr)
				this->left->AddNode(key);
			else
			{
				this->left = new BinaryTree();
				this->left->left = this->left->right = nullptr;
				this->left->key = key;
			}
		}
		else
		{
			if (this->right != nullptr)
				this->right->AddNode(key);
			else
			{
				this->right = new BinaryTree();
				this->right->left = this->right->right = nullptr;
				this->right->key = key;
			}
		}
	}

	BinaryTree* DeleteNode(T x)
	{
		BinaryTree* root = this;
		
		if (root == nullptr)
			return root;
		if (x < root->key)
			root->left = root->left->DeleteNode(x);
		else if (x > root->key)
			root->right = root->right->DeleteNode(x);
		else if ((root->left) && (root->right))
		{
			root->key = root->right->Min()->key;
			root->right = root->right->DeleteNode(root->key);
		}
		else if (root->left)
			root = root->left;
		else
			root = root->right;
		return root;
	}

	BinaryTree* FindNode(T k)
	{
		if ((this == nullptr) || (k == this->key))
			return this;
		if (k < this->key)
			return this->left->FindNode(k);
		else
			return this->right->FindNode(k);
	}

	T GetHeightTree()
	{
		{
			int h1 = 0, h2 = 0;
			if (this == nullptr)
				return 0;
			if (this->left)
				h1 = this->left->GetHeightTree();
			if (this->right)
				h2 = this->right->GetHeightTree();
			return(max(h1, h2) + 1);
		}

	}

	T GetSizeTree()
	{
			if (this->left == nullptr && this->right == nullptr)
				return 1;
			T l, r;
			if (this->left != nullptr)
				l = this->left->GetSizeTree();
			else
				l = 0;
			if (this->right != nullptr)
				r = this->right->GetSizeTree();
			else
				r = 0;

			return l + r + 1;
	}

	void PrintTree(int r)
	{
		if (this)
		{
			this->right->PrintTree(r + 5);
			for (int i = 0; i < r; i++)
				cout << " ";
			cout << this->key << endl;
			this->left->PrintTree(r + 5);
		}
	}
};

int main()
{

	BinaryTree<int> MyTree(0);

	MyTree.AddNode(12);
	MyTree.AddNode(10);
	MyTree.AddNode(1);
	MyTree.AddNode(121);
	MyTree.AddNode(0);
	MyTree.AddNode(10);

	MyTree.PrintTree(0);

	cout << "Height: " << MyTree.GetHeightTree() << endl;
	cout << "Size: " << MyTree.GetSizeTree() << endl;
	
	MyTree.DeleteNode(12);

	MyTree.PrintTree(0);


	int el;
	cout << "Введите элемент, который вы хотите найти в дереве" << endl;
	cin >> el;
	if (MyTree.FindNode(el) == nullptr)
	{
		cout << "Введенный вами элемент не существует" << endl;
	}
	else
	{
		cout << "Введенный вами элемент существует" << endl;
	}

	system("pause");
	return 0;
}