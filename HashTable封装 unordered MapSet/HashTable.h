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
	//提前声明
	template<class K, class T, class KOT, class Ref, class Ptr, class HSF = DefultHSF<K>>
	struct __iterator;
	//开散列
	// 不在直接存kv，存T，T可能是pair或者k，用配套的kot取key
	//template<class K, class V>
	template<class T>
	struct  HashData
	{
		HashData(const T& data) 
		:_data(data),_next(nullptr)
		{ 
			;
		}
		T _data;
		HashData<T>* _next;
	};
	//T 和 kot就可以适配map和set的不同情况 传K是为了find 和 erase的传参
	template<class K, class T,class KOT, class HSF = DefultHSF<K>>
	struct HashTable
	{
	public:
		template<class K, class T, class KOT, class Ref, class Ptr, class HSF >
		friend struct __iterator;
		typedef __iterator<K, T, KOT, T&, T*, HSF> iterator;
		typedef __iterator<K, T, KOT, const T&, const T*, HSF> const_iterator;

		iterator begin() {
			for (const auto& e : _vt) {
				if (e)
					return iterator(e, this);
			}
			return end();
		}
		iterator end() {
			return iterator(nullptr, this);
		}
		const_iterator cbegin()const {
			for (const auto& e : _vt) {
				if (e)
					return const_iterator(e, this);
			}
			return cend();
		}
		const_iterator cend()const {
			return const_iterator(nullptr, this);
		}
		
		typedef HashData<T> Node;
		~HashTable() {
			for (auto& e : _vt) {
				Node* cur = e;
				while (cur) {
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				e = nullptr;
			}
		}
		pair<iterator,bool> Insert(const T& data) {
			KOT kot;
			//负载因子超标（1.0）或者 vector size为0（vector[]禁止访问超过size的部分）扩容
			if (!_vt.size() || _n * 100 / _vt.size() >= 100)
				Reserve(_vt.size() ? 2 * _vt.size() : 10);
			HSF hf;
			size_t start = hf(kot(data)) % _vt.size();//key转化为映射值
			auto newnode= new Node(data) ;
			newnode->_next = _vt[start];
			_vt[start] = newnode;
			_n++;
			return make_pair(iterator(newnode, this), true);
		}
		Node* Find(const K& key) {
			KOT kot;
			HSF hf;
			if (_vt.size() == 0)
				return nullptr;
			size_t start = hf(key) % _vt.size();
			Node* cur = _vt[start];
			while (cur) {
				if (kot(cur->_data) == key)
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
			/*Node* f_ret = Find(key);
			if (f_ret) {
				f_ret->_st = state::DELETED;
				_n--;
				return true;
			}*/
			//单链表删除要保存pev,所以不能复用find
			//直接用双向带头循环也可以（list容器），但单链表已经足够，且不复用也不影响效率。
			HSF hsf;
			size_t hashi = hsf(key)%_vt.size();
			Node* pev = nullptr;
			Node* cur = _vt[hashi];
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
			KOT kot;
			//转移节点
			vector<Node*> new_vt;
			new_vt.resize(newsize, nullptr);
			for (auto& e : _vt) {
				Node* cur = e;
				while (cur) {
					//用哈希值对size取模
					size_t ni = hf(kot(cur->_data)) % newsize;
					//头插前保存下一个
					Node* next = cur->_next;
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
			//	Node* cur = e;
			//	while (cur) {
			//		new_table.Insert(cur->_kv);
			//		cur = cur->_next;
			//	}
			//}
		}
		size_t _n = 0;
		vector<Node*> _vt;
	};
	//封装迭代器
	template<class K, class T, class KOT,class Ref ,class Ptr, class HSF>
	struct __iterator {
		typedef HashData<T> Node;
		typedef __iterator<K, T, KOT, Ref, Ptr, HSF> Self;
		HashTable<K, T, KOT, HSF>* _pht;//拿到整张表的指针
		__iterator(Node* pnode, HashTable<K, T, KOT, HSF>* pht)
			:_pnode(pnode),_pht(pht)
		{
			;
		}
		Node* _pnode;
		Self& operator ++() {
			KOT kot;
			HSF hf;
			Node* old = _pnode;
			Node* cur = _pnode->_next;
			if (!cur) {
				//根据key算当前在表中的位置，然后往后面找第一个不为空的桶
				size_t curhi = (hf(kot(old->_data))%_pht->_vt.size()) + 1;
				for (size_t i = curhi; i < _pht->_vt.size(); i++) {
					if (_pht->_vt[i]) {
						_pnode = _pht->_vt[i];
						return *this;
					}
				}
				//如果找不到 则把迭代器置为nullptr，目的是为了和end想等
				cur = nullptr;
			}
			_pnode = cur;
			return *this;
		}
		Self operator ++(int) {
			Self old = *this;
			++(*this);
			return old;
		}
		Ref operator*() {
			return _pnode->_data;
		}
		Ptr operator->() {
			return &_pnode->_data;
		}
		bool operator!=(const Self& it)const {
			return it._pnode != _pnode;
		}
		bool operator ==(const Self& it)const {
			return it._pnode == _pnode;
		}
	/*	Self begin() {
			KOT kot;
			HSF hf;
			for (size_t i = curhi; i < _pht->_vt.size() && _pht->_vt[i]; i++) {
				_pnode = _pht->_vt[i];
				return this;
			}
			return end();
		}
		Self end() {
			return __iterator(nullptr, _pht);
		}*/
	};
