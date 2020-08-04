#pragma once

#include "Map.hpp"
#include "bst.hpp"

template <typename K, typename V>
class BSTMap : Map<K, V>{
public:
    BSTMap(){
        mapData = bstBase();
    }
};