#pragma once
#include<math.h>
#include<iostream>
#include<queue>
#include<assert.h>
using  std::cout;
using std::endl;
using std:: queue;

template <class K, class V>
struct pair
{
	pair(const K f = K(), const V s = V())
		:first(f), second(s){;}
	pair(const pair <K, V>& __p) : first(__p.first), second(__p.second) {}
	K first;
	V second;
};
template<class K, class V>
struct AVLTreeNode {
	AVLTreeNode(K key=K(), V val=V()) 
		:_kv(key,val),_parent(nullptr),_left(nullptr),_right(nullptr),_bf(0){;}
	AVLTreeNode(const pair<K, V>& kv) 
		:_kv(kv), _parent(nullptr), _left(nullptr), _right(nullptr), _bf(0){;}
	pair<K, V> _kv;
	AVLTreeNode* _parent;
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	//左右子树高度差（平衡因子）
	int _bf;
};
template<class K,class V>
class AVLTree {
public:
	typedef AVLTreeNode<K, V> Node;
	bool insert(const pair<K, V>& kv) {
		if (!_root) {
			_root = new Node(kv);
			return true;
		}
		Node* cur = _root;
		Node* pev = nullptr;
		Node* newnode = new Node(kv);
		while (cur) {
			if (cur->_kv.first == kv.first)
				return false;
			pev = cur;
			cur =kv.first > cur->_kv.first ? cur->_right : cur->_left;
		}
		kv.first > pev->_kv.first?pev->_right = newnode:pev->_left = newnode;
		cur = newnode;
		newnode->_parent = pev;
		//调整平衡因子
		
		while (cur != _root) {
			cur->_parent->_bf += cur == cur->_parent->_left ? -1 : 1;
			pev = cur;
			cur = cur->_parent;
			if (!cur->_bf||abs(cur->_bf)>1)
				break;
		}
		if (abs(cur->_bf) > 1) {
			if (cur->_bf == 2) {
				if (pev->_bf == 1)
					RotateL(cur);
				else if (pev->_bf == -1)
					RotateRL(cur);
				else
					assert(false);
			}
			else if (cur->_bf == -2) {
				if (pev->_bf == -1)
					RotateR(cur);
				else if (pev->_bf == 1)
					RotateLR(cur);
				else
					assert(false);
			}
			//错误代码
			//if (pev == cur->_right)
			//	if (!pev->_right || pev->_left && pev->_left->_bf)
			//		RotateRL(cur);
			//	else
			//		RotateL(cur);
			//else
			//	if (!pev->_left || pev->_right && pev->_right->_bf)
			//		RotateLR(cur);
			//	else
			//		RotateR(cur);
		}
		return true;
	}
	void LevelOrder() {
		if (!_root)
			return;
		Node* cur = _root;
		queue<Node*> qu;
		int levelsize = 1;
		qu.push(_root);
		while (!qu.empty()) {
			while (levelsize--) {
				Node* front = qu.front();
				if (front->_left)
					qu.push(front->_left);
				if (front->_right)
					qu.push(front->_right);
				cout << front->_kv.first << " ";
				qu.pop();
			}
			levelsize = qu.size();
			cout << endl;
		}
	}
	int _Height(Node* root=_root)
	{
		if (root == nullptr)
			return 0;

		int lh = _Height(root->_left);
		int rh = _Height(root->_right);

		return lh > rh ? lh + 1 : rh + 1;
	}
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}
private:
	bool _IsBalanceTree(Node* root)
	{
		// 空树也是AVL树
		if (nullptr == root)
			return true;

		// 计算pRoot节点的平衡因子：即pRoot左右子树的高度差
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int diff = rightHeight - leftHeight;

		// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
		// pRoot平衡因子的绝对值超过1，则一定不是AVL树
		if (abs(diff) >= 2)
		{
			cout << root->_kv.first << "节点平衡因子异常" << endl;
			return false;
		}

		if (diff != root->_bf)
		{
			cout << root->_kv.first << "节点平衡因子不符合实际" << endl;
			return false;
		}

		// pRoot的左和右如果都是AVL树，则该树一定是AVL树
		return _IsBalanceTree(root->_left)
			&& _IsBalanceTree(root->_right);
	}
	void RotateL(Node* cur) {
		Node* parent = cur->_parent;
		Node* subR = cur->_right;
		Node* subRL = cur->_right->_left;
		cur->_right = subRL;
		if (subRL)
			subRL->_parent = cur;
		subR->_left = cur;
		cur->_parent = subR;
		//调整与父亲的关系
		if (parent) {//是子树
			//有可能是左子树或者右子树
			parent->_right == cur ? parent->_right = subR : parent->_left = subR;
			subR->_parent = parent;
		}
		else {//是根
			_root = subR;
			subR->_parent = nullptr;
		}
		//更新平衡因子
		cur->_bf = subR->_bf = 0;

	}

	void RotateR(Node* cur) {
		Node* parent = cur->_parent;
		Node* subL = cur->_left;
		Node* subLR = cur->_left->_right;

		cur->_left = subLR;
		if (subLR)
			subLR->_parent = cur;
		subL->_right = cur;
		cur->_parent = subL;
		if (parent) {
			parent->_left == cur ? parent->_left = subL : parent->_right = subL;
			subL->_parent = parent;
		}
		else {
			_root = subL;
			subL->_parent = nullptr;
		}
		cur->_bf = subL->_bf = 0;
	}
	
	void RotateLR(Node* cur) {
		Node* subL = cur->_left;
		Node* subLR = subL->_right;
		int c = subLR->_bf;
		RotateL(subL);
		RotateR(cur);
		//共三种模型 -已拍照
		switch (c)
		{
		case -1:
			subLR->_bf = subL->_bf = 0;
			cur->_bf = 1;
			break;
		case 0:
			subLR->_bf = subL->_bf = cur->_bf = 0;
			break;
		case 1:
			subL->_bf = -1;
			cur->_bf = subLR->_bf = 0;
			break;
		default:
			assert(false);
			break;
		}
	}

	void RotateRL(Node* cur) {
		Node* subR = cur->_right;
		Node* subRL = subR->_left;
		int c = subRL->_bf;
		RotateR(subR);
		RotateL(cur);
		//三种模型
		switch (c){
		case -1:
			subRL->_bf = cur->_bf = 0;
			subR->_bf = 1;
			break;
		case 0:
			subRL->_bf = subR->_bf = cur->_bf = 0;
			break;
		case 1:
			subRL->_bf = subR->_bf = 0;
			cur->_bf = -1;
			break;
		default:
			assert(false);
			break;
		}
	}


	Node* _root=nullptr;
};