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
	template<class K, class T, class KOT, class HSF = DefultHSF<K>>
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
		template<class K, class T, class KOT, class HSF >
		friend struct __iterator;
		typedef __iterator<K, T, KOT,  HSF> iterator;
		typedef __iterator<K, T, KOT,  HSF> const_iterator;
		HashTable() {
			;
		}
		HashTable(const HashTable& ht) {
			for (auto e : ht._vt)
				Insert(e);
		}
		HashTable& operator =(HashTable ht) {
			_vt.swap(ht._vt);
			return *this;
		}
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
			if (Find(kot(data)))
				return make_pair(iterator(nullptr,this),false);
			//负载因子超标（1.0）或者 vector size为0（vector[]禁止访问超过size的部分）扩容
			if (!_vt.size() || _n * 100 / _vt.size() >= 100)
				//Reserve(_vt.size() ? 2 * _vt.size() : 10);
				Reserve(GetNextPrime(_vt.size()));//用素数可以一定程度上降低冲突
			HSF hf;
			size_t start = hf(kot(data)) % _vt.size();//key转化为映射值
			auto newnode= new Node(data) ;
			newnode->_next = _vt[start];
			_vt[start] = newnode;
			_n++;
			return make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key)const {
			KOT kot;
			HSF hf;
			if (_vt.size() == 0)
				return iterator(nullptr,this);
			size_t start = hf(key) % _vt.size();
			Node* cur = _vt[start];
			while (cur) {
				if (kot(cur->_data) == key)
					return iterator(cur,this);
				cur = cur->_next;
			}
			return iterator(nullptr, this);
		}
		bool erase(const K& key) {
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
		size_t GetNextPrime(size_t prime)const
		{
			const int PRIMECOUNT = 28;
			static const size_t primeList[PRIMECOUNT] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};

			// 获取比prime大那一个素数
			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}

			return primeList[i];
		}
		void Reserve(size_t newsize) {
			//超极端场景
			if (newsize == _vt.size())
				return;
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
	template<class K, class T, class KOT, class HSF>
	struct __iterator {
		typedef HashData<T> Node;
		typedef __iterator<K, T, KOT, HSF> Self;
		const HashTable<K, T, KOT, HSF>* _pht;//拿到整张表的指针
		Node* _pnode;
		__iterator( Node* pnode,  const HashTable<K, T, KOT, HSF>* pht)
			:_pnode(pnode),_pht(pht)
		{
			;
		}
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
		T& operator*() {
			return _pnode->_data;
		}
		T* operator->() {
			return &_pnode->_data;
		}
		bool operator!=(const Self& it)const {
			return it._pnode != _pnode;
		}
		bool operator ==(const Self& it)const {
			return it._pnode == _pnode;
		}
		operator bool()const{
			return _pnode != nullptr;
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
