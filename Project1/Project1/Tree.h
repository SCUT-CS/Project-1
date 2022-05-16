#pragma once
#include "Headers.h"

enum Direction { nw, ne }; //枚举生成子节点的方向
class treeIterator;

/** Data Structure of tree
  * @author CuiYuxin */
class treeNode
{
private:
	friend class Tree;
	friend class treeIterator;
	uchar confirm; //标识0或1
	treeNode* parent = nullptr; //父节点
	treeNode* nwchild = nullptr; //西北子节点
	treeNode* nechild = nullptr; //东北子节点
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
	static void setConfirm(treeIterator it, uchar c); //设置结点确认状态
	static uchar getConfirm(treeIterator it); //获取结点确认状态
	static void setChildConfirm(treeIterator it, uchar c, Direction dir); //设置孩子节点确认状态
	static void deleteChildNode(treeIterator it, Direction dir);
	static void LevelOrder(vector<char>& Q, treeIterator it); //层次遍历
private:
	treeNode* root = nullptr; //根结点地址

	static void InitialNode(treeNode*& node); //初始化树结点
	void deleteTree(treeNode* root);

};

/** Iterator for tree
  * @author CuiYuxin */
class treeIterator
{
public:
	treeIterator() :p(nullptr) {};
	treeIterator(treeNode* root) :p(root) {};
	treeIterator(Tree& t) :p(t.getRoot()) {};
	treeNode* operator->();
	treeNode* operator*();
	bool toNwChild();
	bool toNeChild();
	bool toParent();
	treeIterator getNwChild()const;
	treeIterator getNeChild()const;
	treeIterator getParent()const;
private:
	friend class Tree;
	treeNode* p;
};







