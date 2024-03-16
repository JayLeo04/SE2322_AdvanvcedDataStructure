#include "hftree.h"
#include "algorithm"
std::map<std::string, std::string> hfTree::codingTable;
std::shared_ptr<hfTree::Node> hfTree::root;

hfTree::hfTree(const std::string &text, const Option op)
{
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare> pq;

    // TODO: Your code here
    calculateFrequencies(text);
    switch (op) {
        case Option::SingleChar:
            for (auto &freq : singleFrequencies) {
                pq.push(std::make_shared<Node>(Node{freq.first, freq.second}));
            }
            break;
        case Option::MultiChar:
            // 处理字符组合，选择频率最高的前三个组合
            std::vector<std::pair<int, std::string>> topCombinations;
            for (const auto &freq : multiFrequencies) {
                topCombinations.emplace_back(freq.second, freq.first);
            }
            // 按频率降序和字典升序排列
            std::sort(topCombinations.begin(), topCombinations.end(), [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) {
                if (a.first != b.first) {
                    return a.first > b.first; // 频率更高的在前
                }
                return a.second < b.second; // 字典序小的在前
            });
            // 仅保留频率最高的前三个组合
            if (topCombinations.size() > 3) {
                topCombinations.resize(3);
            }
            // 对应地更新频率表，并添加到优先队列
            for (const auto &comb : topCombinations) {
                pq.push(std::make_shared<Node>(Node{comb.second, comb.first}));
                for (char ch : comb.second) {
                    // 减少相应单字符的频率
                    if (singleFrequencies.find(std::string(1, ch)) != singleFrequencies.end()) {
                        singleFrequencies[std::string(1, ch)] -= comb.first;
                    }
                }
            }
            // 添加剩余的单字符到优先队列
            for (auto &freq : singleFrequencies) {
                if (freq.second > 0) { // 仅添加频率非0的字符
                    pq.push(std::make_shared<Node>(Node{freq.first, freq.second}));
                }
            }
            break;
    }
    while (pq.size() > 1) {
        // 取出两个频率最小的节点
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();
        // 创建一个新的父节点，其频率为两个子节点频率之和
        auto parent = std::make_shared<Node>("*", left->frequency + right->frequency, left, right);
        parent->left = left;
        parent->right = right;
        // 将新的父节点加入优先队列
        pq.push(parent);
    }
    root = pq.top();
}

void hfTree::calculateFrequencies(const std::string &txt){
    for(char c : txt){
        singleFrequencies[std::string(1, c)]++;
    }
    for(size_t i = 0; i < txt.length(); ++i){
        multiFrequencies[txt.substr(i, 2)]++;
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

void hfTree::generateCodingTable(const std::shared_ptr<Node>& node, const std::string& code) {
    // 递归基，当遇到叶子节点时
    if (node->left == nullptr && node->right == nullptr) {
        // 将字符（或字符组合）与其相应的编码添加到编码表中
        codingTable[node->character] = code;
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