#pragma once
#include "Headers.h"

enum Direction { nw, ne }; //ö�������ӽڵ�ķ���
class treeIterator;

/** Data Structure of tree
  * @author CuiYuxin */
class treeNode
{
private:
	friend class Tree;
	friend class treeIterator;
	uchar confirm; //��ʶ0��1
	treeNode* parent = nullptr; //���ڵ�
	treeNode* nwchild = nullptr; //�����ӽڵ�
	treeNode* nechild = nullptr; //�����ӽڵ�
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
private:
	treeNode* p;
};







