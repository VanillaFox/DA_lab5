#include "suftree.h"

TSufTree::TNode::TNode(int first, int *second, bool ans): start(first), 
                                                        end(second), 
                                                        leaf(ans){}

TSufTree::TNode::~TNode(){}

void TSufTree::DeleteTree(TNode* node){
    for(auto it: node->children){
        DeleteTree(it.second);
    }
    if(!node->leaf){
        delete node->end;
    }
    delete node;
}

TSufTree::~TSufTree(){
    DeleteTree(root);   
}

TSufTree::TSufTree(){
    std::string text;
    std::cin >> text;
    str = text;
    str += str;
    BuildTree();
}

void TSufTree::BuildTree(){
    str += TERM_SYMBOL;
    for(int i = 0; i < str.size(); i++){
        Extension(i);
    }
}

void TSufTree::Extension(int position){
    curEnd++;
    lastCreatedNode = nullptr;
    countSuf++;
    while(countSuf){
        if(activeLenght == 0){
            activeEdge = position;
        }
        if(!activeNode->children[str[activeEdge]]){
            activeNode->children[str[activeEdge]] = new TNode(position, &curEnd, true);
            RuleTwo(activeNode);
            lastCreatedNode = activeNode;
        }
        else{
            TNode* nextNode = activeNode->children[str[activeEdge]];
            int edgeLenght = *(nextNode->end) - nextNode->start + 1;
            if(activeLenght >= edgeLenght){
                activeEdge += edgeLenght;
                activeLenght -= edgeLenght;
                activeNode = nextNode;
                continue;
            }
            if(str[nextNode->start + activeLenght] == str[position]){
                RuleTwo(activeNode);
                activeLenght++;
                break;
            }
            TNode* add = new TNode(nextNode->start, new int(nextNode->start+activeLenght-1), false);
            activeNode->children[str[activeEdge]] = add;
            nextNode->start += activeLenght;
            add->children.insert(std::make_pair(str[position], new TNode(position, &curEnd, true)));
            add->children.insert(std::make_pair(str[nextNode->start], nextNode));
            RuleTwo(add);
            lastCreatedNode = add;    
        }
        countSuf--;
        if(activeNode == root){
            if(activeLenght){
                RuleOne();
            }
        }else{
            RuleThree();
        }
    }
}

void TSufTree::RuleTwo(TNode* node){
    if(lastCreatedNode != nullptr){
        lastCreatedNode->sufLink = node;
    }
}

void TSufTree::RuleOne(){
    activeEdge++;
    activeLenght--;
}

void TSufTree::RuleThree(){
    if(activeNode->sufLink){
        activeNode = activeNode->sufLink;
    }else{
        activeNode = root;
    }
}

std::string TSufTree::MinLex(){
    std::string result;
    TNode* next = root;

    while(result.size() < (str.size()-1)/2){
        std::map<char, TNode*>::iterator it = next->children.begin();
        if(it->first == '$'){
            it++;
        }
        next = it->second;
        for(int i = next->start; i <= *(next->end); i++){
            result += str[i];
            if(result.size() == (str.size()-1)/2){
                break;
            }
        }
    }
    return result;
}

void TSufTree::Print(TNode* node){
    if(node == root){
        std::cout << "\\root \n";
    }
    else{
        std::cout << std::endl;
        std::cout << "\\node <" << str[node->start]<< ">(" << node->start << ", " << *node->end << ")\n";
    }
    if(node->children.size()){
        std::cout << "children:\n";
        for(auto it = node->children.begin(); it != node->children.end(); it++){
            std::cout << "\\node <" << it->first << "> ";
        }
        std::cout << std::endl; 

        for(auto &it: node->children){
            Print(it.second);
        }
    }
}

void TSufTree::PrintTree(){
    Print(root);
}