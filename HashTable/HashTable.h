#pragma once
#include<vector>
#include<string>
using namespace std;
	template<class K>
	struct DefultHSF//默认的哈希值转换
	{
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};
	template<>//针对string的特化
	struct DefultHSF<string>
	{
		size_t operator()(const string& key) {
			size_t ret = 0;
			for (const auto& ch : key)
				ret = ret * 131 + ch;
			return ret;
		}
	};

namespace CloseHash {
	enum class state
	{
		EMPTY,
		EXIST,
		DELETED
	};
	template<class K, class V>
	struct  HashData
	{
		pair<K, V> _kv;
		state _st = state::EMPTY;
	};
	template<class K, class V, class HSF = DefultHSF<K>>
	struct HashTable
	{
	public:
		bool Insert(const pair<K, V>& kv) {
			//负载因子超标（0.75）或者 vector size为0（vector[]禁止访问超过size的部分）扩容
			if (!_vt.size() || _n * 100 / _vt.size() >= 75)
				Reserve(_vt.size() ? 2 * _vt.size() : 10);
			HSF hf;
			size_t start = hf(kv.first) % _vt.size();//key转化为映射值
			size_t cur = start;
			size_t i = 1;//方便在 线性探测和二次探测之间切换
			while (_vt[cur]._st != state::EMPTY) {
				cur = start + i;
				i++;
				cur %= _vt.size();//防止越界
				if (cur == start)
					return false;
			}
			_vt[cur]._kv = kv;
			_vt[cur]._st = state::EXIST;
			_n++;
			return true;
		}
		HashData<K, V>* Find(const K& key) {
			if (_vt.size() == 0)
				return nullptr;
			HSF hf;
			size_t start = hf(key) % _vt.size();
			size_t i = 1;
			for (size_t cur = start; _vt[cur]._st != state::EMPTY; cur = start + i) {
				cur %= _vt.size();
				if (_vt[cur]._st != state::DELETED && _vt[cur]._kv.first == key)
					return &_vt[cur];
				i++;
			}
			return nullptr;
		}
		bool erase(const K& key) {
			HashData<K, V>* f_ret = Find(key);
			if (f_ret) {
				f_ret->_st = state::DELETED;
				_n--;
				return true;
			}
			return false;
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
					new_table.Insert(e._kv);
			_vt.swap(new_table._vt);
		}
		size_t _n = 0;
		vector<HashData<K, V>> _vt;
	};
}
namespace OpenHash {

	template<class K, class V>
	struct  HashData
	{
		HashData(const pair<K, V>& kv) 
		:_kv(kv),_next(nullptr)
		{ 
			;
		}
		pair<K, V> _kv;
		HashData<K,V>* _next;
	};
	template<class K, class V, class HSF = DefultHSF<K>>
	struct HashTable
	{
	public:
		~HashTable() {
			for (auto& e : _vt) {
				HashData<K, V>* cur = e;
				while (cur) {
					HashData<K, V>* next = cur->_next;
					delete cur;
					cur = next;
				}
				e = nullptr;
			}
		}
		bool Insert(const pair<K, V>& kv) {
			//负载因子超标（1.0）或者 vector size为0（vector[]禁止访问超过size的部分）扩容
			if (!_vt.size() || _n * 100 / _vt.size() >= 100)
				Reserve(_vt.size() ? 2 * _vt.size() : 10);
			HSF hf;
			size_t start = hf(kv.first) % _vt.size();//key转化为映射值
			auto newnode= new HashData<K, V>(kv) ;
			newnode->_next = _vt[start];
			_vt[start] = newnode;
			_n++;
			//size_t cur = start;
			//size_t i = 1;//方便在 线性探测和二次探测之间切换
			//while (_vt[cur]._st != state::EMPTY) {
			//	cur = start + i;
			//	i++;
			//	cur %= _vt.size();//防止越界
			//	if (cur == start)
			//		return false;
			//}
			//_vt[cur]._kv = kv;
			//_vt[cur]._st = state::EXIST;
			//_n++;
			return true;
		}
		HashData<K, V>* Find(const K& key) {
			if (_vt.size() == 0)
				return nullptr;
			HSF hf;
			size_t start = hf(key) % _vt.size();
			HashData<K, V>* cur = _vt[start];
			while (cur) {
				if (cur->_kv.first == key)
					return cur;
				cur = cur->_next;
			}
			/*		size_t i = 1;
			for (size_t cur = start; _vt[cur]._st != state::EMPTY; cur = start + i) {
				cur %= _vt.size();
				if (_vt[cur]._st != state::DELETED && _vt[cur]._kv.first == key)
					return &_vt[cur];
				i++;
			}*/
			return nullptr;
		}
		bool erase(const K& key) {
			/*HashData<K, V>* f_ret = Find(key);
			if (f_ret) {
				f_ret->_st = state::DELETED;
				_n--;
				return true;
			}*/
			//单链表删除要保存pev,所以不能复用find
			//直接用双向带头循环也可以（list容器），但单链表已经足够，且不复用也不影响效率。
			HSF hsf;
			size_t hashi = hsf(key)%_vt.size();
			HashData<K, V>* pev = nullptr;
			HashData<K, V>* cur = _vt[hashi];
			while (cur) {
				if (cur->_kv.first == key) {
					//注意pev如果为空，代表删除头节点，要特殊处理。
					//不能删了就不管了，因为链表的结构是 *p(就是这里的_vt[hashi]) 指向 node,node.*p 指向 node;
					pev ? pev->_next = cur->_next : _vt[hashi] = cur->_next;
					delete cur;
					return true;
				}
				pev = cur;
				cur = cur->_next;
			}
			return false;
		}
	private:
		void Reserve(size_t newsize) {
			HSF hf;
			//转移节点
			vector<HashData<K, V>*> new_vt;
			new_vt.resize(newsize, nullptr);
			for (auto& e : _vt) {
				HashData<K, V>* cur = e;
				while (cur) {
					//用哈希值对size取模
					size_t ni = hf(cur->_kv.first) % newsize;
					//头插前保存下一个
					HashData<K, V>* next = cur->_next;
					//头插方法
					cur->_next = new_vt[ni];
					new_vt[ni] = cur;
					
					cur = next;
				}
				//相当于遍历原vt中的每条链表，把它们的节点全部转移
				//最后把原vt链表置为nullptr
				e = nullptr;
			}
			//交换vt
			_vt.swap(new_vt);
		//拷贝节点
			//重新建立映射
			//HashTable<K, V> new_table;
			////给新表的容器设定new size
			//new_table._vt.resize(newsize);
			////遍历旧表
			//for (const auto& e : _vt) {
			//	//如果存在插入新表（自动建立映射）
			//	HashData<K, V>* cur = e;
			//	while (cur) {
			//		new_table.Insert(cur->_kv);
			//		cur = cur->_next;
			//	}
			//}
		}
		size_t _n = 0;
		vector<HashData<K, V>*> _vt;
	};
}