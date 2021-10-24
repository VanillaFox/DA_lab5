#include <iostream>
#include <vector>
#include <chrono>
#include "suftree.h"

int main(){
    std::string answer;
    {
        auto start = std::chrono::steady_clock::now();   
        TSufTree tree;
        answer = tree.MinLex();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Suftree time: " <<  elapsed_seconds.count() << std::endl;
    }
    {
        auto start = std::chrono::steady_clock::now();   
        std::string text;
        std::cin >> text;
        std::vector<std::string> strs;
        
        for(int i = 0; i < text.size(); i++){
            text.append(text, 0, 1);
            text.erase(text.begin());
            strs.push_back(text);
        }
        int curbest = 0;
        for(int i = 1; i < strs.size(); i++){
            for(int j = 0; j < strs.size(); j++){
                if(strs[i][j] == strs[curbest][j]){
                    continue;
                }
                if(strs[i][j] < strs[curbest][j]){
                    curbest = i;
                }
                break;
            }
        }
        answer = strs[curbest];
        auto end = std::chrono::steady_clock::now();   
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "NaivAlgo time: " <<  elapsed_seconds.count() << std::endl;
    }
}