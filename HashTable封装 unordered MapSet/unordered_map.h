#pragma once
using namespace std;
#include<iostream>
#include"HashTable.h"

template<class K,class V,class HSF = DefultHSF<K>>
class unordered_map {
public:
	struct KeyOfT
	{
		const K& operator()(const pair<K,V>& kv) {
			return kv.first;
		}
	};
	typedef typename HashTable<K, pair<K, V>, KeyOfT>::iterator iterator;
	typedef typename HashTable<K, pair<K, V>, KeyOfT>::const_iterator const_iterator;
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
	pair<iterator,bool> insert(const pair<K, V>& kv) {
		return ht.Insert(kv);
	}
	V& operator[](const K& key) {
		return insert(make_pair(key, V())).first->second;
	}
private:
	HashTable<K, pair<K,V>, KeyOfT,HSF> ht;
};