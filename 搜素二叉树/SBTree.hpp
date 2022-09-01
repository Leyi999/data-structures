#pragma once
#include<iostream>
using namespace std;
template<typename K>
//SearchBinaryNode
struct SBNode {
	SBNode(K key = K())
		:_key(key), _left(nullptr), _right(nullptr) { }
	SBNode* _left;
	SBNode* _right;
	K _key;
};
template<typename K>
class SBTree {
public:
	typedef SBNode<K> Node;
	SBTree() = default;
	~SBTree() {
		Destroy(_root);
	}
	SBTree(const SBTree<K>& t) {
		_root = Copy(t._root);
	}
	SBTree& operator =(SBTree t) {//�ִ�д��
		swap(t._root, _root);
		return *this;
	}
	bool insert(const K& key = K()) {
		if (!_root) {
			_root = new Node(key);
			return true;
		}
		Node* parent, * cur;
		parent = nullptr;
		cur = _root;
		while (cur != nullptr) {//parentָ�����һ���ڵ�
			if (key == cur->_key)
				return false;
			parent = cur;
			cur = ((key > cur->_key) ? cur->_right : cur->_left);
		}
		cur = new Node(key);//����key
		cur->_key > parent->_key ? parent->_right = cur : parent->_left = cur;
		return true;
	}
	const Node* Find(const K& key)const {
		for (Node* cur = _root; cur; cur = (key > cur->_key) ? cur->_right : cur->_left)
			if (cur->_key == key) return cur;
		return nullptr;
	}
	bool Erase(const K& key) {
		Node* cur, * parent;
		cur = parent = _root;
		while (cur && cur->_key != key) {
			parent = cur;
			cur = (key > cur->_key) ? cur->_right : cur->_left;
		}
		if (cur) {
			if (cur->_left == nullptr) {//ֻ���Һ���
				if (cur == _root) //root���⴦��
					_root = _root->_right;
				else
					key > parent->_key ? parent->_right = cur->_right : parent->_left = cur->_right;//ȷ���й�λ��
			}
			else if (cur->_right == nullptr) {//ֻ������
				if (cur == _root) //root���⴦��
					_root = _root->_left;
				else
					key > parent->_key ? parent->_right = cur->_left : parent->_left = cur->_left;//ȷ���й�λ��
			}
			else {//���Һ��Ӷ��У�������Ҫ���滻��
				Node* child = cur->_left;
				Node* parent = cur;
				while (child->_right) {//�ҵ������������ӽڵ�
					parent = child;
					child = child->_right;
				}
				cur->_key = child->_key;
				//�����õݹ�ɾ������Ϊ�Ҳ�����
				delete child;
				child = nullptr;
				//�����ø��ڵ���ӽڵ�ָ��գ�����������������
				//��������жϸ��ڵ��ı�ָ���
				parent == cur ? parent->_left = child : parent->_right = child;
				return true;
			}
			delete cur;
			return true;
		}
		return false;
	}
	void InOder()const {
		_InOder(_root);
	}
	const Node* RFind(const K& key) const {
		return _RFind(_root, key);
	}
	bool RInsert(const K& key) {
		return _RInsert(_root, key);
	}
	bool RErase(const K& key) {
		return _RErase(_root, key);
	}
protected:
	bool _RErase(Node*& root ,const K& key) {//��������܌�
		if (root->_key == key) {
			Node* del = root;
			if (root->_left == nullptr) 
				root = root->_right;	
			else if (root->_right == nullptr) 
				root = root->_left;
			else {
			//	Node* parent = root;
			//	Node* leftchild = root->_left;
			//	while (leftchild->_right) {
			//		parent = leftchild;
			//		leftchild = leftchild->_right;
			//	}
			//	parent == root ? parent->_left = nullptr : parent->_right = nullptr;
			//	root->_key = leftchild->_key;
			//	del = leftchild;
				Node* leftchild = root->_left;
				while (leftchild->_right)
					leftchild = leftchild->_right;
				swap(leftchild->_key, root->_key);
				return _RErase(root->_left, key);//�����������ʱreturn������del �ͻ�ѻ������Ľڵ�ɾ�ˣ�
			}
			delete del;
			return true;
		}
		return root?(root->_key > key ? _RErase(root->_left, key) : _RErase(root->_right, key)):false;//����ϲ������Ŀ
	}
	bool _RInsert(Node*& root, const K& key) {//��������܌� 
		if (root == nullptr) {
			root = new Node(key);//��Ϊ�Ǹ��ڵ��ֽڵ�ָ��ı���������ֱ�Ӹģ�
			return true;
		}
		return root->_key == key ? false : (root->_key > key ? _RInsert(root->_left, key) : _RInsert(root->_right, key));//����ϲ������Ŀ
	}
	const Node* _RFind(Node* root, const K& key)const {
		if (root)
			return root->_key == key ? root : (root->_key > key ? _RFind(root->_left, key) : _RFind(root->_right, key));
		return nullptr;
	}
	void _InOder(const Node* root)const {
		if (root == nullptr)
			return;
		_InOder(root->_left);
		cout << root->_key << ' ';
		_InOder(root->_right);
	}
	void Destroy(Node* root) {
		if (!root) {
			return;
		}
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	Node* Copy(Node* root) {
		if (!root)
			return nullptr;
		Node* newtree = new Node(root->_key);
		newtree->_left = Copy(root->_left);
		newtree->_right = Copy(root->_right);
		return newtree;
	}
	Node* _root = nullptr;
};

