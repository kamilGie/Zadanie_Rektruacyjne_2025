#include "unordered_map"
struct trieNode {
    std::unordered_map<char, trieNode> children;
    bool isEnd = false;
};
