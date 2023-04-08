#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    size_t space,
    std::string word,
    std::set<std::string>& answer);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> answer;
    size_t space = count(in.begin(), in.end(), '-');
    helper(in, floating, dict, space, "", answer);
    return answer;
}

// Define any helper functions here
void helper(const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    size_t space,
    std::string word,
    std::set<std::string>& answer){   

    //base case: all letters have been filled in
    if(word.size() == in.size()){ 
        if(dict.count(word)) { 
            //if word in the dictionary, add it to the set
            answer.insert(word); 
        }
        return;
    }
    //case1: a letter already exists in this position
    else if(in[word.size()] != '-'){ 
        // add it to the current word
        word += in[word.size()];
        helper(in, floating, dict, space, word, answer);
    }

    //case2: empty spot exists in this position
    else{
        // all remaining space are empty
        if(space == floating.size()){
            for(size_t i = 0; i < floating.size(); i++){
                std::string curr = floating;
                char letter = curr[i];
                curr.erase(i, 1);
                helper(in, curr, dict, space - 1, word + letter, answer);
                curr.insert(i, 1, letter);
        }
    }
        // some but not all remaining space are empty
        else{
            for(char letter = 'a'; letter <= 'z'; letter++){
                std::string curr = floating;
                if(curr.find(letter) != std::string::npos){
                    curr.erase(curr.find(letter), 1);
                }
                helper(in, curr, dict, space - 1, word + letter, answer);
            }
        }
    }
}