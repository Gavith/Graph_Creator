//Map class that I might use in the future

#include <vector>
#include <functional>
template<class K, class T>
struct MapPair {//for the actual entries
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
	T& get(K key);
	T pop(K key);
	void put(K key, T item);
	void set(K key, T item);
	//T &operator[](K key);

private:
	std::vector<MapPair<K, T>> entries;
};

template<class K, class T>
inline auto Map<K, T>::begin()//for iteration
{
	return entries.begin();
}

template<class K, class T>
inline auto Map<K, T>::end()//for iteration
{
	return entries.end();
}

template<class K, class T>
inline T& Map<K, T>::get(K key)//returns the entry based on a key
{
	for (auto i = entries.begin(); i != entries.end(); i++) {//goes through all
		if ((*i).first == key) {//if it matches
			return (*i).second;
		}
	}
	throw "Key does not exist.";//error handling cuz I cant return null
}

template<class K, class T>
inline T Map<K, T>::pop(K key)//same thing to get, just removes it
{
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if ((*i)->first == key) {
			MapPair<K, T> temp = *i;
			entries.erase(i);
			return temp->second;
		}
	}
	throw "Key does not exist.";
}

template<class K, class T>
inline void Map<K, T>::put(K key, T item)//a push function
{
	MapPair<K, T> temp = MapPair<K, T>(key, item);
	entries.push_back(temp);
}

template<class K, class T>
inline void Map<K, T>::set(K key, T item)//setting so I can update
{
	for (auto i = entries.begin(); i != entries.end(); i++) {
		if ((*i).first == key) {
			(*i).second = item;
		}
	}
}