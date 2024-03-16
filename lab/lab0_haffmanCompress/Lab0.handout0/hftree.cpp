#include "hfTree.h"
#include <queue>
#include <functional>
#include <algorithm>



// Node比较函数，用于优先队列


// 构造函数
hfTree::hfTree(const std::string &text, const Option op): text(text), option(op) {
    calculateFrequencies();
    buildTree();
    generateCodingTable(root, "");
}

// 计算频率函数
void hfTree::calculateFrequencies() {
    // 当选项为单个字符时，计算单个字符频率
    if (option == Option::SingleChar) {
        for (char c : text) {
            frequencies[std::string(1, c)]++;
        }
    }
        // 当选项为连续两个字符时，计算单个字符及连续两个字符频率
    else {
        std::map<std::string, int> comboFrequencies;
        for (size_t i = 0; i < text.length(); ++i) {
            frequencies[std::string(1, text[i])]++; // 单个字符
            if (i < text.length() - 1) {
                std::string combo = text.substr(i, 2); // 连续两个字符
                comboFrequencies[combo]++;
            }
        }

        // 在所有连续两个字符的组合中选择出现频率最高的前三个字符组合
        std::vector<std::pair<std::string, int>> comboFreqVec(comboFrequencies.begin(), comboFrequencies.end());
        // 根据频率和字典序进行排序
        std::sort(comboFreqVec.begin(), comboFreqVec.end(), [](const auto &x, const auto &y) {
            return x.second != y.second ? x.second > y.second : x.first < y.first;
        });

        // 选取频率最高的前三个字符组合
        int combosToAdd = std::min(3, static_cast<int>(comboFreqVec.size()));
        for (int i = 0; i < combosToAdd; ++i) {
            std::string combo = comboFreqVec[i].first;
            int freq = comboFreqVec[i].second;

            // 键入频率表并从原表中移除单个字符频率
            frequencies[combo] = freq;
            frequencies[std::string(1, combo[0])] -= freq;
            frequencies[std::string(1, combo[1])] -= freq;

            // 若减去后频率为0则移除单个字符
            if (frequencies[std::string(1, combo[0])] <= 0) {
                frequencies.erase(std::string(1, combo[0]));
            }
            if (frequencies[std::string(1, combo[1])] <= 0) {
                frequencies.erase(std::string(1, combo[1]));
            }
        }
    }
}

void hfTree::buildTree() {
    // 创建一个优先队列来存储树节点（使用上面定义的比较函数）
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare> pq;

    // 将频率表(frequencies)中每个字符的频率转换为树节点并添加到优先队列中
    for (auto &freq : frequencies) {
        pq.push(std::make_shared<Node>(Node{freq.first[0], freq.second}));
    }

    // 循环直至优先队列中只剩下一个节点
    while (pq.size() > 1) {
        // 取出两个频率最小的节点
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();

        // 创建一个新的父节点，其频率为两个子节点频率之和
        auto parent = std::make_shared<Node>(Node{'*', left->frequency + right->frequency});
        parent->left = left;
        parent->right = right;

        // 将新的父节点加入优先队列
        pq.push(parent);
    }

    // 队列中最后一个节点即为哈夫曼树的根节点
    root = pq.top();
}

void hfTree::generateCodingTable(const std::shared_ptr<Node>& node, const std::string& code) {
    // 递归基，当遇到叶子节点时
    if (node->left == nullptr && node->right == nullptr) {
        // 将字符（或字符组合）与其相应的编码添加到编码表中
        codingTable[std::string(1, node->character)] = code;
        return;
    }

    // 遍历左子树，编码字符串添加0
    if (node->left != nullptr) {
        generateCodingTable(node->left, code + "0");
    }

    // 遍历右子树，编码字符串添加1
    if (node->right != nullptr) {
        generateCodingTable(node->right, code + "1");
    }
}

std::map<std::string, std::string> hfTree::getCodingTable()
{
    // TODO: Your code here
    if (codingTable.empty() && root != nullptr) {
        generateCodingTable(root, "");
    }
    return codingTable;
}

hfTree::~hfTree() {

}