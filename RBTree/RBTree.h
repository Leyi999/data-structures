#pragma once
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
enum class color
{
	Red,
	Black,
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode(pair<K,V>kv)
		:_kv(kv),col(color::Red),_parent(nullptr),_left(nullptr),_right(nullptr)
	{
		;
	}
	color col;
	pair<K, V> _kv;
	RBTreeNode* _parent;
	RBTreeNode* _left;
	RBTreeNode* _right;
};
template<class K, class V>
struct RBTree
{
	typedef RBTreeNode<K, V> Node;
	RBTree()
		:_root(nullptr) {
		;
	}
	bool insert(const pair<K, V>& kv) {
		if (!_root) {
			_root = new Node(kv);
			_root->col = color::Black;
			return true;
		}
		Node* cur = _root;
		Node* pev = nullptr;
		Node* newnode = new Node(kv);
		while (cur) {
			if (cur->_kv.first == kv.first)
				return false;
			pev = cur;
			cur = kv.first > cur->_kv.first ? cur->_right : cur->_left;
		}
		kv.first > pev->_kv.first ? pev->_right = newnode : pev->_left = newnode;
		cur = newnode;
		newnode->_parent = pev;
		//调整平衡因子

		while (cur != _root) {
			pev = cur;
			cur = cur->_parent;
			Node* parent = cur->_parent;
			
			Node* bother = parent ? cur == parent->_left ? parent->_right : parent->_left:nullptr;
			if (cur->col == color::Red && pev->col == color::Red) {//连续两个红
				if (bother && bother->col == color::Red) {//情况一 只改变颜色，也许向上调整
					while (bother && bother->col == color::Red) {
						cur->col = bother->col = color::Black;
						parent->col = color::Red;
						if (parent == _root) {
							parent->col = color::Black;
							break;
						}
						cur=pev = parent;
					}
				}//情况二 需要旋转 并且调整颜色，不影响其他路径的黑色节点数量
				else if (bother == nullptr || bother->col == color::Black) {
					//    cur
					//pev
					if (pev == cur->_left) {
					      //     pare
						 //    cur
					    //   pev
						if (cur == parent->_left) {
							RotateR(parent);
							cur->col = color::Black;
							parent->col = pev->col = color::Red;
						}
						//    pare
						// cur
						//    pev
						else {
							RotateR(cur);
							RotateL(parent);
							pev->col = color::Black;
							parent->col = color::Red;
						}
							break;
					}
					// cur
					//    pev
					else {
						// pare
						//    cur
						//       pev
						if (cur == parent->_right) {
							RotateL(parent);
							cur->col = color::Black;
							parent->col = pev->col = color::Red;
						}
						//    pare
						// cur
						//    pev
						else {
							RotateL(cur);
							RotateR(parent);
							pev->col = color::Black;
							parent->col = color::Red;
						}
						break;
					}
				}
			}
		}
		_root->col = color::Black;
		return true;
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
		;

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

	}
	int _maxHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _maxHeight(root->_left);
		int rh = _maxHeight(root->_right);

		return lh > rh ? lh + 1 : rh + 1;
	}

	int _minHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _minHeight(root->_left);
		int rh = _minHeight(root->_right);

		return lh < rh ? lh + 1 : rh + 1;
	}


	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t BlackCount)
	{
		//走到null之后，判断k和color::Black是否相等
		if (nullptr == pRoot)
		{
			if (k != BlackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}

		// 统计黑色节点的个数
		if (color::Black == pRoot->col)
			k++;

		// 检测当前节点与其双亲是否都为红色
		if (color::Red == pRoot->col && pRoot->_parent && pRoot->_parent->col == color::Red)
		{
			cout << "违反性质三：存在连在一起的红色节点" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, BlackCount) &&
			_IsValidRBTree(pRoot->_right, k, BlackCount);
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

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		void Height()
		{
			cout << "最长路径:" << _maxHeight(_root) << endl;
			cout << "最短路径:" << _minHeight(_root) << endl;
		}


		bool IsBalanceTree()
		{
			// 检查红黑树几条规则

			Node* pRoot = _root;
			// 空树也是红黑树
			if (nullptr == pRoot)
				return true;

			// 检测根节点是否满足情况
			if (color::Black != pRoot->col)
			{
				cout << "违反红黑树性质二：根节点必须为黑色" << endl;
				return false;
			}

			// 获取任意一条路径中黑色节点的个数 -- 比较基准值
			size_t BlackCount = 0;
			Node* pCur = pRoot;
			while (pCur)
			{
				if (color::Black == pCur->col)
					BlackCount++;

				pCur = pCur->_left;
			}

			// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
			size_t k = 0;
			return _IsValidRBTree(pRoot, k, BlackCount);
		}
	Node* _root;
	
};