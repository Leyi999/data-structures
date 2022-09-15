#pragma once
#include"RBTree.h"
template<class K,class V>
class map {
public:
	struct KOfMap {
		const K& operator()(const pair<K,V>&data) {
			return data.first;
		}
	};
	typedef typename RBTree<K, pair<K, V>, KOfMap>::iterator iterator;
	typedef typename RBTree<K, pair<K, V>, KOfMap>::const_iterator const_iterator;

	typedef RBTreeNode<pair<K,V>> Node;
	iterator find(K key) {
		return _Tree.find(key);
	}
	iterator begin() {
		return _Tree.begin();
	}
	
	iterator end() {
		return _Tree.end();
	}
	pair<iterator,bool> insert(pair<K, V> data) {
		return _Tree.insert(data);		
	}
	V& operator[](const K key) {
		return (insert(make_pair(key, V())).first)->second;
	}
	void LevelOrder() {
		_Tree.LevelOrder();
	}
private:
	RBTree<K, pair<K, V>, KOfMap> _Tree;
};