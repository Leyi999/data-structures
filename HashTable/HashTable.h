#pragma once
#include<vector>
using namespace std;

enum class state
{
	EMPTY,
	EXIST,
	DELETED
};
template<class K,class V>
struct  HashData
{
	pair<K, V> _kv;
	state _st;
};
template<class K,class V>
struct HashTable
{
public:
	bool Insert(const pair<K, V>& kv) {
		//负载因子超标（0.75）或者 vector size为0（vector[]禁止访问超过size的部分）扩容
		if (!_vt.size() || _n * 100 / _vt.size() >= 75)
			Reserve(_vt.size() ? 2 * _vt.size() : 10);
		size_t start =kv.first%_vt.size();//key转化为映射值
		size_t cur = start;
		size_t i = 1;//方便在 线性探测和二次探测之间切换
		while (_vt[cur]._st != state::EMPTY) {
			cur = start + i;
			i++;
			cur %= _vt.size();//防止越界
			if (cur == start)
				return false;
		}
		_vt[cur]._kv=kv;
		_vt[cur]._st = state::EXIST;
		_n++;
	}
	HashData<K,V>* Find(const K& key) {
		for (const auto& e : _vt)
			if (e._st == state::EXIST && e._kv.first == key)
				return &e;
		return nullptr;
	}
	bool erase(const K& key) {
		HashData<K,V>* f_ret = Find(key);
		if (f_ret)
			f_ret->_st = state::DELETED;
		else
			return false;
		return true;
	}
private:
	void Reserve(size_t newsize) {
		//重新建立映射
		HashTable<K, V> new_table;
		//给新表的容器设定new size
		new_table._vt.resize(newsize);
		//遍历旧表
		for (const auto& e : _vt)
			//如果存在插入新表（自动建立映射）
			//删除的不用管，重新建立映射（位置改变）后依然能找到
			if (e._st == state::EXIST)
				new_table.Insert(e);
		_vt.swap(new_table._vt);
	}
	size_t _n;
	vector<HashData<K,V>> _vt;
};