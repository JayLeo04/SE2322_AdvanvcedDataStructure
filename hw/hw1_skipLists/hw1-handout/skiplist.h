#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cstdint>
// #include <optional>
#include <vector>
#include <string>

namespace skiplist {
using key_type = uint64_t;
// using value_type = std::vector<char>;
using value_type = std::string;
/*首先我们创建skipList的元素节点
 * 每个节点应该具有的属性有：
 * 1. key: 用于排序的关键字
 * 2. value: 用于存储的值
 * 3. level: 用于表示当前节点的层数
 * 4. forward: 用于存储当前节点的下一个节点的指针
 * 5.初始化函数，将forward初始化为level+1个nullptr
 */
struct SkipNode{
public:
    SkipNode(key_type key,value_type value,int level):key(key),value(value),level(0),forward(level+1,nullptr){}

    std::vector<SkipNode*> forward;
    int level;
    key_type key;
    value_type value;
};

/*
 * skipList的属性有：
 * 1. maxLevel: 用于表示skipList的最大层数
 * 2. p: 用于表示随机层数的概率
 * 3. head: 用于表示skipList的头节点
 * 4. randomLevel: 用于生成随机层数
 * 5. put: 用于插入节点
 * 6. get: 用于查找节点
 * 7. query_distance: 用于查询节点的距离
 */
class skiplist_type
{
private:
    int maxLevel=16;
    double p;
    SkipNode* head;
public:
	explicit skiplist_type(double p = 0.5);
	void put(key_type key, const value_type &val);
	//std::optional<value_type> get(key_type key) const;
	std::string get(key_type key) const;
    int randomLevel();
	// for hw1 only
	int query_distance(key_type key) const;
};

} // namespace skiplist

#endif // SKIPLIST_H
