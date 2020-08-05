#ifndef _MAP_H
#define _MAP_H

#include "Tree.hpp"
#include <vector>
#include <stdexcept>

template <typename K, typename V>
class Map {
public:
	struct Pair {
        K key;
        V value;

        Pair();
        Pair(K key_); //valueless key. should only be used for comparisson with valued keys
        Pair(K key_, V value_);

        bool operator>(const Pair& other) { return key > other.key;};
        bool operator>=(const Pair& other) { return key >= other.key; };
        bool operator<(const Pair& other) { return key < other.key; };
        bool operator<=(const Pair& other) { return key <= other.key; };
        bool operator==(const Pair& other) { return key == other.key; };
        bool operator!=(const Pair& other) { return key != other.key; };
    };

	V& operator[](K key);
	void remove(K key);


	virtual ~Map() = 0;
	
protected:
	Tree<Pair>* mapData;
};

template <typename K, typename V>
V& Map<K, V>::operator[](K key) {
    try {
        return mapData->getRef(Pair(key)).value;
    }
    catch (std::out_of_range&) {
        mapData->insert(Pair(key));
        return mapData->getRef(Pair(key)).value;
    }
}

template <typename K, typename V>
void Map<K, V>::remove(K key){
	mapData->remove(Pair(key));
}

template <typename K, typename V>
Map<K, V>::Pair::Pair() {
    key = K();
    value = V();
}

template <typename K, typename V>
Map<K, V>::Pair::Pair(K key_) {
    key = key_;
    value = V();
}

template <typename K, typename V>
Map<K, V>::Pair::Pair(K key_, V value_) {
    key = key_;
    value = value_;
}

template <typename K, typename V>
Map<K, V>::~Map() {
	delete mapData;
}

#endif
