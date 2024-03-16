#ifndef HFTREE_H
#define HFTREE_H

#include <string>
#include <map>
#include <memory>
#include <queue>

enum class Option
{
    SingleChar,
    MultiChar
};

class hfTree
{

private:
    // TODO: Your code here
    // Define a struct Node to represent the node of the huffman tree
    struct Node{
        char character;
        int frequency;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(char character, int frequency, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr)
                : character(character), frequency(frequency), left(left), right(right) { }
    };
    std::string text;
    std::map<std::string, std::string> codingTable;
    // Define a struct Compare to compare the frequency of two nodes
    std::shared_ptr<Node> root;
    std::map<std::string, int> frequencies;
    Option option;
    void calculateFrequencies();
    void buildTree();
    void generateCodingTable(const std::shared_ptr<Node>& node, const std::string& code);



public:
    // Define an enum class Option to represent the encoding method

    hfTree(const std::string &text, const Option op);
    std::map<std::string, std::string> getCodingTable();
    ~hfTree();
};

#endif