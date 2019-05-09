#include <vector>
#include <functional>
template<class K, class T>
struct MapPair {
	K first;
	T second;

	MapPair(K first, T second) {
		this->first = first;
		this->second = second;
	}
};

template<class K, class T>
class Map {
public:
	auto begin();
	auto end();
	T get(K key);
	T pop(K key);
	void put(K key, T item);
	//T &operator[](K key);

private:
	vector<MapPair<K, T>> entries;
};

template<class K, class T>
inline auto Map<K, T>::begin()
{
	return entries.begin();
}

template<class K, class T>
inline auto Map<K, T>::end()
{
	return entries.end();
}

template<class K, class T>
inline T Map<K, T>::get(K key)
{
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if ((*i)->first == key) {
			return (*i)->second;
		}
	}
	return NULL;
}

template<class K, class T>
inline T Map<K, T>::pop(K key)
{
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if ((*i)->first == key) {
			MapPair temp = *i;
			entries.erase(i);
			return temp->second;
		}
	}
	return NULL;
}

template<class K, class T>
inline void Map<K, T>::put(K key, T item)
{
	MapPair<K, T> temp = MapPair<K, T>(key, item);
	entries.push_back(temp);
}


/*
template<class K, class T>
inline T & Map<K, T>::operator[](K key)
{
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if (equal_to<K>((*i).first, key)) {
			return (*i).second;
		}
	}
//	ARG I CANT GET THIS TO WORK
}
*/