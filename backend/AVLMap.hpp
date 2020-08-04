#pragma once

#include "Map.hpp"
#include "avl.hpp"

template <typename K, typename V>
class BSTMap : public Map<K, V>{
public:
    AVLMap(){
        Map<K, V>::mapData = new avl<typename Map<K, V>::Pair>();
    }
};