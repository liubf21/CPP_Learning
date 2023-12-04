#include <map>

using std::map;

// implement a LRU cache with a double linked list and a map
class LRUCache
{
    struct LNode
    {
        int key = -1;
        int data = -1;
        LNode *pre = nullptr;
        LNode *next = nullptr;
    };
    int capacity__;
    int size__;
    LNode *head, *tail;
    map<int, LNode *> mp;

public:
    LRUCache(int capacity)
    {
        capacity__ = capacity;
        size__ = 0;
        head = new LNode();
        tail = new LNode();
        head->next = tail;
        tail->pre = head;
    }

    int get(int key)
    {
        if (mp.count(key) && mp[key]->data != -1)
        {
            LNode *use = mp[key];
            use->pre->next = use->next;
            use->next->pre = use->pre;

            use->next = head->next;
            use->pre = head;
            head->next->pre = use;
            head->next = use;

            return use->data;
        }
        else
            return -1;
    }

    void put(int key, int value)
    {
        if (mp.count(key))
        {
            // if(mp[key]->data==-1)
            // {
            //     mp[key]->pre=head;
            //     mp[key]->next=head;
            //     head->next->pre = mp[key];
            //     head->next = mp[key];
            //     size__++; // 注意
            // }else{
            LNode *use = mp[key];
            use->pre->next = use->next;
            use->next->pre = use->pre;

            use->next = head->next;
            use->pre = head;
            head->next->pre = use;
            head->next = use;
            // }
            mp[key]->data = value;
        }
        else
        {
            LNode *add = new LNode();
            mp[key] = add;
            add->key = key;
            add->data = value;
            // cout<<"add"<<key<<" "<<value<<endl;

            add->pre = head;
            add->next = head->next;
            head->next->pre = add;
            head->next = add;

            size__++;
        }
        if (size__ > capacity__)
        {
            LNode *del = tail->pre;
            tail->pre = del->pre;
            del->pre->next = tail;
            // del->pre = nullptr;
            // del->next = nullptr;
            // del->data = -1;
            // cout<<"del"<<del->key<<endl;
            mp.erase(del->key); // 通过将data标识为 -1 过不了，而erase却能过
            // delete del;
            size__--;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */