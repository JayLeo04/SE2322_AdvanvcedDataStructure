#include "skiplist.h"
#include <optional>

namespace skiplist {
/*
 * skiplist_type初始化函数
 * 用于初始化skiplist_type的属性
 * @param p: 用于表示随机层数的概率
 */
skiplist_type::skiplist_type(double p) {
    this->p = p;
    head = new SkipNode(0,0,maxLevel);
}

int skiplist_type::randomLevel(){
    int level = 0;
    while (level < maxLevel && (rand() % 100) < p * 100) {
        level++;
    }
    return level;
}

void skiplist_type::put(key_type key, const value_type &val) {
    SkipNode* update[maxLevel+1];
    SkipNode* x = head;
    for (int i = maxLevel; i >= 0; i--) {
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x == nullptr || x->key != key) {
        int level = randomLevel();
        if (level > maxLevel) {
            for (int i = maxLevel + 1; i <= level; i++) {
                update[i] = head;
            }
            maxLevel = level;
        }
        x = new SkipNode(key, val, level);
        for (int i = 0; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    } else {
        x->value = val;
    }
}
std::string skiplist_type::get(key_type key) const {
    SkipNode* x = head;
    for (int i = maxLevel; i >= 0; i--) {
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != nullptr && x->key == key) {
        return x->value;
    } else {
        return "";
    }
}
int skiplist_type::query_distance(key_type key) const {
    SkipNode* x = head;
    int distance = 0;
    for (int i = maxLevel; i >= 0; i--) {
        while (x->forward[i] != nullptr && x->forward[i]->key < key) {
            x = x->forward[i];
            distance++;
        }
    }
    x = x->forward[0];
    if (x != nullptr && x->key == key) {
        return distance;
    } else {
        return -1;
    }
}


} // namespace skiplist
