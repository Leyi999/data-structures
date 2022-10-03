#pragma once
#include<vector>
#include<string>
using namespace std;
	template<class K>
	struct DefultHSF//Ĭ�ϵĹ�ϣֵת��
	{
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};
	template<>//���string���ػ�
	struct DefultHSF<string>
	{
		size_t operator()(const string& key) {
			size_t ret = 0;
			for (const auto& ch : key)
				ret = ret * 131 + ch;
			return ret;
		}
	};
	//��ǰ����
	template<class K, class T, class KOT, class HSF = DefultHSF<K>>
	struct __iterator;
	//��ɢ��
	// ����ֱ�Ӵ�kv����T��T������pair����k�������׵�kotȡkey
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
	//T �� kot�Ϳ�������map��set�Ĳ�ͬ��� ��K��Ϊ��find �� erase�Ĵ���
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
			//�������ӳ��꣨1.0������ vector sizeΪ0��vector[]��ֹ���ʳ���size�Ĳ��֣�����
			if (!_vt.size() || _n * 100 / _vt.size() >= 100)
				//Reserve(_vt.size() ? 2 * _vt.size() : 10);
				Reserve(GetNextPrime(_vt.size()));//����������һ���̶��Ͻ��ͳ�ͻ
			HSF hf;
			size_t start = hf(kot(data)) % _vt.size();//keyת��Ϊӳ��ֵ
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
			//������ɾ��Ҫ����pev,���Բ��ܸ���find
			//ֱ����˫���ͷѭ��Ҳ���ԣ�list�����������������Ѿ��㹻���Ҳ�����Ҳ��Ӱ��Ч�ʡ�
			HSF hsf;
			size_t hashi = hsf(key)%_vt.size();
			Node* pev = nullptr;
			Node* cur = _vt[hashi];
			while (cur) {
				if (cur->_kv.first == key) {
					//ע��pev���Ϊ�գ�����ɾ��ͷ�ڵ㣬Ҫ���⴦��
					//����ɾ�˾Ͳ����ˣ���Ϊ����Ľṹ�� *p(���������_vt[hashi]) ָ�� node,node.*p ָ�� node;
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

			// ��ȡ��prime����һ������
			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}

			return primeList[i];
		}
		void Reserve(size_t newsize) {
			//�����˳���
			if (newsize == _vt.size())
				return;
			HSF hf;
			KOT kot;
			//ת�ƽڵ�
			vector<Node*> new_vt;
			new_vt.resize(newsize, nullptr);
			for (auto& e : _vt) {
				Node* cur = e;
				while (cur) {
					//�ù�ϣֵ��sizeȡģ
					size_t ni = hf(kot(cur->_data)) % newsize;
					//ͷ��ǰ������һ��
					Node* next = cur->_next;
					//ͷ�巽��
					cur->_next = new_vt[ni];
					new_vt[ni] = cur;
					
					cur = next;
				}
				//�൱�ڱ���ԭvt�е�ÿ�����������ǵĽڵ�ȫ��ת��
				//����ԭvt������Ϊnullptr
				e = nullptr;
			}
			//����vt
			_vt.swap(new_vt);
		//�����ڵ�
			//���½���ӳ��
			//HashTable<K, V> new_table;
			////���±�������趨new size
			//new_table._vt.resize(newsize);
			////�����ɱ�
			//for (const auto& e : _vt) {
			//	//������ڲ����±��Զ�����ӳ�䣩
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
	//��װ������
	template<class K, class T, class KOT, class HSF>
	struct __iterator {
		typedef HashData<T> Node;
		typedef __iterator<K, T, KOT, HSF> Self;
		const HashTable<K, T, KOT, HSF>* _pht;//�õ����ű��ָ��
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
				//����key�㵱ǰ�ڱ��е�λ�ã�Ȼ���������ҵ�һ����Ϊ�յ�Ͱ
				size_t curhi = (hf(kot(old->_data))%_pht->_vt.size()) + 1;
				for (size_t i = curhi; i < _pht->_vt.size(); i++) {
					if (_pht->_vt[i]) {
						_pnode = _pht->_vt[i];
						return *this;
					}
				}
				//����Ҳ��� ��ѵ�������Ϊnullptr��Ŀ����Ϊ�˺�end���
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
