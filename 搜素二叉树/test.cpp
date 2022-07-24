#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
//SearchBinaryNode
template<typename K>
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
	bool insert(const K& key=K()) {
		if (!_root) {
			_root = new Node(key);
			return true;
		}
		Node* parent,* cur;
		parent = nullptr;
		cur = _root;
		while (cur!=nullptr) {//parent指向最后一个节点
			if(key == cur->_key)
				return false;
			parent = cur;
			cur = ((key > cur->_key) ? cur->_right : cur->_left);
		}
		cur = new Node(key);//插入key
		cur->_key > parent->_key ? parent->_right = cur : parent->_left = cur;
		return true;
	}
	const Node* Find(const K& key)const {
		for (Node* cur = _root; cur; cur = (key > cur->_key) ? cur->_right : cur->_left) 
			if (cur->_key == key) return cur;
		return nullptr;
	}
	void InOder()const {
		_InOder(_root);
	}
protected:
	void _InOder(const Node* root)const {
		if (root == nullptr)
			return;
		_InOder(root->_left);
		std::cout << root->_key << ' ';
		_InOder(root->_right);
	}
	Node* _root=nullptr;
};
int main() {
	SBTree <int>sbt1;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	for (auto e : a)
		sbt1.insert(e);
	sbt1.InOder();
	std::cout << (sbt1.Find(8))->_key;
	return 0;
}