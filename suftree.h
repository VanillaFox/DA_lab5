#pragma once
#include <map>
#include <iostream>
#include <memory>

const std::string TERM_SYMBOL = "$";

class TSufTree{
    class TNode{
        public:
            TNode* sufLink = nullptr;
            int start;
            int* end;
            bool leaf;
            std::map<char, TNode*> children;
            TNode(int first, int* second, bool ans);
            ~TNode();
    };

    int activeLenght = 0, activeEdge = -1;
    TNode* root = new TNode(-1, new int(-1), false);
    TNode* activeNode = root, *lastCreatedNode;
    int countSuf = 0;
    std::string str;
    int curEnd = -1;
    void RuleOne();
    void RuleTwo(TNode* node);
    void RuleThree();
    void Extension(int position);
    void Print(TNode* node);
    void DeleteTree(TNode* node);
    void BuildTree();

    public:
    TSufTree();
    ~TSufTree();
    void PrintTree();
    std::string MinLex();
};
