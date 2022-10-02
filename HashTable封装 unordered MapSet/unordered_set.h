#pragma once
#include"HashTable.h"
template<class K, class HSF = DefultHSF<K>>
class unordered_set {
public:
	struct KeyOfT
	{
		const K& operator()(const K& key) {
			return key;
		}
	};
	typedef typename HashTable<K, K, KeyOfT>::iterator iterator;
	typedef typename HashTable<K, K, KeyOfT>::const_iterator const_iterator;
	iterator begin() {
		return ht.begin();
	}
	iterator end() {
		return ht.end();
	}
	const_iterator begin()const {
		return ht.cbegin();
	}
	const_iterator end()const {
		return ht.cend();
	}
	pair<iterator, bool> insert(const K& data) {
		return ht.Insert(data);
	}

private:
	HashTable<K,K,KeyOfT,HSF> ht;
};