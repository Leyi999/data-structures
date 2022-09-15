#pragma once
#include"RBTree.h"
template<class K>
class set {
public:
	struct KOfSet {
		const K& operator()(const K& data) {
			return data;
		}
	};
	typedef typename RBTree<K, K, KOfSet>::iterator iterator;
	typedef typename RBTree<K, K, KOfSet>::const_iterator const_iterator;
	pair<iterator,bool> insert(const K& data) {
		return _Tree.insert(data);
	}

	iterator begin()  {
		return _Tree.begin();
	}
	iterator end() {
		return _Tree.end();
	}

	const_iterator begin() const {
		return _Tree.begin();
	}
	const_iterator end() const {
		return _Tree.end();
	}
	void LevelOrder() {
		_Tree.LevelOrder();
	}
private:
	RBTree<K, K, KOfSet> _Tree;
};