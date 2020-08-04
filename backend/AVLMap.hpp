#pragma once

#include "Map.hpp"
#include "avl.hpp"

template <typename K, typename V>
class AVLMap : public Map<K, V>{
public:
    AVLMap(){
        Map<K, V>::mapData = new avl<typename Map<K, V>::Pair>();
    }
};