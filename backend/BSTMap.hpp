#pragma once

#include "Map.hpp"
#include "bst.hpp"

template <typename K, typename V>
class BSTMap : public Map<K, V>{
public:
    BSTMap(){
        Map<K, V>::mapData = new bst<typename Map<K, V>::Pair>();
    }
};