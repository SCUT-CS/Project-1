#pragma once
#include "Headers.h"

enum Direction { nw, ne }; //ö�������ӽڵ�ķ���

/** Data Structure of tree
  * @author CuiYuxin */
class treeNode
{
private:
	friend class Tree;
	friend class treeIterator;
	uchar confirm; //��ʶ0��1
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
	//void InsertNode(treeNode*& root); //���뺢�ӽ��
	static void addchild(treeIterator it, Direction dir); //���뺢�ӽ��
	
	
private:
	treeNode* root = nullptr; //������ַ
	
	static void InitialNode(treeNode*& node); //��ʼ�������
	void LevelOrder(vector<char>& Q, treeNode* root); //��α���
	void deleteTree(treeNode* root);
	
};





