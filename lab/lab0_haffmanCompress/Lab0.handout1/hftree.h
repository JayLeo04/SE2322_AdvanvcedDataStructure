#ifndef HFTREE_H
#define HFTREE_H

#include <string>
#include <map>
#include "memory"
#include <queue>
#include <utility>

class hfTree
{

private:
    // TODO: Your code here
    // Define a struct Node to represent the node of the huffman tree
    struct Node
    {
        std::string character;
        int frequency;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(std::string character, int frequency, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr)
            : character(std::move(character)), frequency(frequency), left(std::move(left)), right(std::move(right)) {}

            std::string getMinData() const{
            if (this->left == nullptr && this->right == nullptr) {
                return character;  // 如果是叶子节点，直接返回节点的数据
            }
            std::string minData = this->character;  // 初始化最小字典序为当前节点的数据
            if (this->left != nullptr) {
                std::string leftMinData = this->left->getMinData();  // 递归获取左子树的最小字典序
                if (leftMinData < minData) {
                    minData = leftMinData;  // 更新最小字典序
                }
            }
            if (this->right != nullptr) {
                std::string rightMinData = this->right->getMinData();  // 递归获取右子树的最小字典序
                if (rightMinData < minData) {
                    minData = rightMinData;  // 更新最小字典序
                }
            }
            return minData;
        }
    };

    struct NodeCompare {
        bool operator()(const std::shared_ptr<hfTree::Node>& lhs, const std::shared_ptr<hfTree::Node>& rhs) {
            if (lhs->frequency == rhs->frequency) { // If frequencies are equal
                std::string minDataA = lhs->getMinData();  // 获取树a中所有节点的最小字典序
                std::string minDataB = rhs->getMinData();  // 获取树b中所有节点的最小字典序
                return minDataA < minDataB;  // 比较最小字典序
            }
            return lhs->frequency > rhs->frequency; // Otherwise, compare by frequency
        }
    };

    std::string text;
    static std::map<std::string, std::string> codingTable;
    static std::shared_ptr<Node> root;
    std::map<std::string, int> singleFrequencies;
    std::map<std::string, int> multiFrequencies;
    void calculateFrequencies(const std::string &txt);
    static void generateCodingTable(const std::shared_ptr<Node> &node, const std::string &code);

public:
    enum class Option
    {
        SingleChar,
        MultiChar
    };
    hfTree(const std::string &text, Option op);
    static std::map<std::string, std::string> getCodingTable();
};

#endif