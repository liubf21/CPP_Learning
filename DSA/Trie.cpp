#include<bits/stdc++.h>
using namespace std;

class Trie {
    struct Node{
        unordered_map<char, Node*> mp;
        bool isEnd = false;
    };

    Node* head;
public:
    /** Initialize your data structure here. */
    Trie() {
        head = new Node;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = head;
        for(const auto& c : word)
        {
            if(!p->mp.count(c))
            {
                p->mp[c]=new Node;
            }    
            p=p->mp[c];
        }
        // p->mp['!']=new Node; // 用!标识结束
        p->isEnd=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = head;
        for(const auto& c : word)
        {
            if(p->mp.count(c))
            {
                p=p->mp[c];
            }else{
                return false;
            }
        }
        // if(!p->mp.count('!'))return false;
        return p->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* p = head;
        for(const auto& c : prefix)
        {
            if(p->mp.count(c))
            {
                p=p->mp[c];
            }else{
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */