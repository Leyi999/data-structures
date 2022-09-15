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

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data)
		:_data(data),col(color::Red),_parent(nullptr),_left(nullptr),_right(nullptr)
	{
		;
	}
	color col;
	T _data;
	RBTreeNode* _parent;
	RBTreeNode* _left;
	RBTreeNode* _right;
};
template<class T,class Ref,class Ptr>
struct Iterator {
	typedef RBTreeNode<T> Node;
	typedef Iterator<T, Ref, Ptr> Self;
	Iterator( Node* pnode = nullptr) 
	: _it(pnode){ ; }
	Ref operator *() {
		return _it->_data;
	}
	Ptr operator ->() {
		return &_it->_data;
	}
	Self& operator++() {
		if (_it->_right) {//右子树的最左
			Node* right = _it->_right;
			while (right->_left)
				right = right->_left;
			_it = right;
		}
		else {//往第一个子为父的左的树
			Node* parent = _it->_parent;
			while (parent && _it != parent->_left) {
				_it = parent;
				parent = parent->_parent;
			}
			_it = parent;
		}
		return *this;
	}
	Self operator++(int) {
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	Self& operator--() {
		if (_it->_left) {
			Node* left = _it->_left;
			while (left->_right)
				left = left->_right;
		}
		else{
			Node* parent = _it->_parent;
			while (parent && _it != parent->_right) {
				_it = parent;
				parent = parent->_parent;
			}
			_it = parent;
		}
	}
	Self operator --(int) {
		Self tmp(*this);
		--(*this);
		return tmp;
	}
	bool operator != (const Self& it)const {
		return _it != it._it;
	}
	bool operator ==(const Self& it)const {
		return !(it._it != _it);
	}

	Node* _it;
};
template<class K, class T,class KeyOfT>
struct RBTree
{
	typedef Iterator<T, T&, T*> iterator;
	typedef Iterator<const T, const T&, const T*> const_iterator;
	typedef RBTreeNode<T> Node;
	RBTree()
		:_root(nullptr) {
		;
	}
	~RBTree() {
		_destroy(_root);
	}
	RBTree(const RBTree& root) {
		_root = _copy(root);
	}
	RBTree& operator=(RBTree tmp) {
		swap(tmp._root, _root);
	}
	iterator begin() {
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		return iterator(cur);
	}
	const_iterator begin() const {
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		const_iterator ret(cur);
		return ret;
	}
	iterator end()  {
		return iterator(nullptr);
	}
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	iterator find(const K& key) {
		KeyOfT kot;
		Node* cur = _root;
		while (cur) {
			if (kot(cur->_data) == key)
				return iterator(cur);
			cur = kot(cur->_data) > key ? cur->_left : cur->_right;
		}
		return iterator(cur);
	}
	const_iterator find(const K& key)const {
		KeyOfT kot;
		Node* cur = _root;
		while (cur) {
			if (kot(cur->_data) == key)
				return cosnt_iterator(cur);
			cur = kot(cur->_data) > key ? cur->_left : cur->_right;
		}
		return const_iterator(cur);
	}
	pair<iterator,bool> insert(const T& data) {
		if (!_root) {
			_root = new Node(data);
			_root->col = color::Black;
			return make_pair(iterator(_root), true);
		}
		KeyOfT kot;
		Node* cur = _root;
		Node* pev = nullptr;
		Node* newnode = new Node(data);
		while (cur) {
			if (kot(cur->_data) == kot(data))
				return make_pair(iterator(cur),false);
			pev = cur;
			cur = kot(data) > kot(cur->_data) ? cur->_right : cur->_left;
		}
		kot(data) > kot(pev->_data) ? pev->_right = newnode : pev->_left = newnode;
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
		return make_pair(iterator(newnode), true);
	}
	void LevelOrder() {
		KeyOfT kot;
		if (!_root)
			return;
		Node* cur = _root;
		queue<Node*> qu;
		size_t levelsize = 1;
		qu.push(_root);
		while (!qu.empty()) {
			while (levelsize--) {
				Node* front = qu.front();
				if (front->_left)
					qu.push(front->_left);
				if (front->_right)
					qu.push(front->_right);
				cout << kot(front->_data) << " ";
				qu.pop();
			}
			levelsize = qu.size();
			cout << endl;
		}
	}
private:
	void _destroy(Node*root) {
		if (!root)
			return;
		Node* left = root->_left;
		Node* right = root->_right;
		delete root;
		_destroy(left), _destroy(right);
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

	Node* _copy(Node* root) {
		if (!root)
			return nullptr;
		Node* newtree(root->_data);
		newtree->_left = _copy(root->_left);
		newtree->_right = _copy(root->_right);
		return newtree;
	}
	Node* _root;
	
};