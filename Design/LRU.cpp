#include <unordered_map>
#include <list>
#include <iostream>


// implement a LRU cache with a double linked list and a map
class LRUCache
{
    struct LNode
    {
        int key; // for delete the node from map
        int data;
        LNode *pre;
        LNode *next;

        LNode(int key = -1, int data = -1) : key(key), data(data), pre(nullptr), next(nullptr) {}
    };
    int capacity__;
    LNode *head, *tail;
    std::unordered_map<int, LNode *> mp; // key to node, for quick access

    // remove node from list, but not delete it. the user should manage the memory manually
    void removeNode(LNode *node)
    {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    // add node to the head of list
    void addNodeToHead(LNode *node)
    {
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }

public:
    LRUCache(int capacity): capacity__(capacity), head(new LNode()), tail(new LNode())    
    {
        head->next = tail;
        tail->pre = head;
    }

    ~LRUCache()
    {
        LNode *cur = head;
        while (cur)
        {
            LNode *tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    int get(int key)
    {
        if (mp.find(key) == mp.end())
            return -1;
        LNode *use = mp[key];
        removeNode(use);
        addNodeToHead(use);

        return use->data;
    }

    void put(int key, int value)
    {
        if (mp.find(key) != mp.end())
        {
            LNode *use = mp[key];
            use->data = value;
            removeNode(use);
            addNodeToHead(use);
        }
        else
        {
            if (int(mp.size()) == capacity__)
            {
                LNode *tmp = tail->pre;
                removeNode(tmp);
                mp.erase(tmp->key);
                delete tmp;
            }
            LNode *newNode = new LNode(key, value);
            addNodeToHead(newNode);
            mp[key] = newNode;
        }
    }

    void print()
    {
        LNode *cur = head->next;
        while (cur != tail)
        {
            std::cout << cur->key << " " << cur->data << std::endl;
            cur = cur->next;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCacheV2 {
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> mp;
    std::list<std::pair<int, int>> cacheList;
    int capacity__;

public:
    LRUCacheV2(int capacity) : capacity__(capacity) {}

    int get(int key) {
        auto it = mp.find(key);
        if (it == mp.end()) {
            return -1;
        }
        int value = it->second->second;
        // cacheList.erase(it->second);
        // cacheList.push_front(std::make_pair(key, value));
        // mp[key] = cacheList.begin();
        cacheList.splice(cacheList.begin(), cacheList, it->second); // move the node to the front, more efficient
        return value;
    }

    void put(int key, int value) {
        auto it = mp.find(key);
        if (it != mp.end()) {
            // cacheList.erase(it->second);
            // cacheList.push_front(std::make_pair(key, value));
            // mp[key] = cacheList.begin();
            cacheList.splice(cacheList.begin(), cacheList, it->second); // move the node to the front, more efficient
            it->second->second = value;
        } else {
            if (int(cacheList.size()) == capacity__) {
                int keyToDel = cacheList.back().first;
                cacheList.pop_back();
                mp.erase(keyToDel);
            }
            cacheList.push_front(std::make_pair(key, value));
            mp[key] = cacheList.begin();
        }
    }

};

int main() {
    std::cout << "Test LRU Cache" << std::endl;
    LRUCache cache(2);  // Capacity of the cache

    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << "Get 1: " << cache.get(1) << std::endl; // returns 1

    cache.put(3, 3);    // evicts key 2
    std::cout << "Get 2: " << cache.get(2) << std::endl; // returns -1 (not found)

    cache.put(4, 4);    // evicts key 1
    std::cout << "Get 1: " << cache.get(1) << std::endl; // returns -1 (not found)
    std::cout << "Get 3: " << cache.get(3) << std::endl; // returns 3
    std::cout << "Get 4: " << cache.get(4) << std::endl; // returns 4

    std::cout << "Test LRU Cache V2" << std::endl;
    LRUCacheV2 cache2(2);  // Capacity of the cache

    cache2.put(1, 1);
    cache2.put(2, 2);
    std::cout << "Get 1: " << cache2.get(1) << std::endl; // returns 1

    cache2.put(3, 3);    // evicts key 2
    std::cout << "Get 2: " << cache2.get(2) << std::endl; // returns -1 (not found)

    cache2.put(4, 4);    // evicts key 1
    std::cout << "Get 1: " << cache2.get(1) << std::endl; // returns -1 (not found)
    std::cout << "Get 3: " << cache2.get(3) << std::endl; // returns 3
    std::cout << "Get 4: " << cache2.get(4) << std::endl; // returns 4

    return 0;
}

