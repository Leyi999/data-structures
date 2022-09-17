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
		//�������ӳ��꣨0.75������ vector sizeΪ0��vector[]��ֹ���ʳ���size�Ĳ��֣�����
		if (!_vt.size() || _n * 100 / _vt.size() >= 75)
			Reserve(_vt.size() ? 2 * _vt.size() : 10);
		size_t start =kv.first%_vt.size();//keyת��Ϊӳ��ֵ
		size_t cur = start;
		size_t i = 1;//������ ����̽��Ͷ���̽��֮���л�
		while (_vt[cur]._st != state::EMPTY) {
			cur = start + i;
			i++;
			cur %= _vt.size();//��ֹԽ��
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
		//���½���ӳ��
		HashTable<K, V> new_table;
		//���±�������趨new size
		new_table._vt.resize(newsize);
		//�����ɱ�
		for (const auto& e : _vt)
			//������ڲ����±��Զ�����ӳ�䣩
			//ɾ���Ĳ��ùܣ����½���ӳ�䣨λ�øı䣩����Ȼ���ҵ�
			if (e._st == state::EXIST)
				new_table.Insert(e);
		_vt.swap(new_table._vt);
	}
	size_t _n;
	vector<HashData<K,V>> _vt;
};