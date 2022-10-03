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
			//�������ӳ��꣨0.75������ vector sizeΪ0��vector[]��ֹ���ʳ���size�Ĳ��֣�����
			if (!_vt.size() || _n * 100 / _vt.size() >= 75)
				Reserve(_vt.size() ? 2 * _vt.size() : 10);
			HSF hf;
			size_t start = hf(kv.first) % _vt.size();//keyת��Ϊӳ��ֵ
			size_t cur = start;
			size_t i = 1;//������ ����̽��Ͷ���̽��֮���л�
			while (_vt[cur]._st != state::EMPTY) {
				cur = start + i;
				i++;
				cur %= _vt.size();//��ֹԽ��
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
			//���½���ӳ��
			HashTable<K, V> new_table;
			//���±�������趨new size
			new_table._vt.resize(newsize);
			//�����ɱ�
			for (const auto& e : _vt)
				//������ڲ����±��Զ�����ӳ�䣩
				//ɾ���Ĳ��ùܣ����½���ӳ�䣨λ�øı䣩����Ȼ���ҵ�
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
			//�������ӳ��꣨1.0������ vector sizeΪ0��vector[]��ֹ���ʳ���size�Ĳ��֣�����
			if (!_vt.size() || _n * 100 / _vt.size() >= 100)
				Reserve(_vt.size() ? 2 * _vt.size() : 10);
			HSF hf;
			size_t start = hf(kv.first) % _vt.size();//keyת��Ϊӳ��ֵ
			auto newnode= new HashData<K, V>(kv) ;
			newnode->_next = _vt[start];
			_vt[start] = newnode;
			_n++;
			//size_t cur = start;
			//size_t i = 1;//������ ����̽��Ͷ���̽��֮���л�
			//while (_vt[cur]._st != state::EMPTY) {
			//	cur = start + i;
			//	i++;
			//	cur %= _vt.size();//��ֹԽ��
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
			//������ɾ��Ҫ����pev,���Բ��ܸ���find
			//ֱ����˫���ͷѭ��Ҳ���ԣ�list�����������������Ѿ��㹻���Ҳ�����Ҳ��Ӱ��Ч�ʡ�
			HSF hsf;
			size_t hashi = hsf(key)%_vt.size();
			HashData<K, V>* pev = nullptr;
			HashData<K, V>* cur = _vt[hashi];
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
		void Reserve(size_t newsize) {
			HSF hf;
			//ת�ƽڵ�
			vector<HashData<K, V>*> new_vt;
			new_vt.resize(newsize, nullptr);
			for (auto& e : _vt) {
				HashData<K, V>* cur = e;
				while (cur) {
					//�ù�ϣֵ��sizeȡģ
					size_t ni = hf(cur->_kv.first) % newsize;
					//ͷ��ǰ������һ��
					HashData<K, V>* next = cur->_next;
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