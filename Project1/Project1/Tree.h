#pragma once
#include "Headers.h"

enum Direction { nw, ne }; //枚举生成子节点的方向

/** Data Structure of tree
  * @author CuiYuxin */
class treeNode
{
private:
	friend class Tree;
	friend class treeIterator;
	uchar confirm; //标识0或1
	treeNode* parent;
	treeNode* nwchild;
	treeNode* nechild;
};

/** Iterator for tree
  * @author CuiYuxin */
class treeIterator
{
public:
	treeIterator() :p(nullptr) {};
	treeIterator(treeNode* root) :p(root) {};
	treeNode* operator->();
	treeNode* operator*();
	bool toNwChild();
	bool toNeChild();
	bool toParent();
private:
	treeNode* p;
};

/** Creating tree and provide method
  * @author CuiYuxin */
class Tree
{
public:
	Tree();
	~Tree();
	treeNode* getRoot();
	//void InsertNode(treeNode*& root); //插入孩子结点
	static void addchild(treeIterator it, Direction dir); //插入孩子结点
	
	
private:
	treeNode* root = nullptr; //根结点地址
	
	static void InitialNode(treeNode*& node); //初始化树结点
	void LevelOrder(vector<char>& Q, treeNode* root); //层次遍历
	void deleteTree(treeNode* root);
	
};





