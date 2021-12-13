static int x = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(0);
    return 0;
}();
class LRUCache {
public:

    class DLL
    {
        public :
            int key;
            int val;
            DLL* prev;
            DLL* next;

            DLL(int key, int val) : key(key), val(val),next(nullptr), prev(nullptr){}
    };

    void addNode(DLL *newNode)
    {
        DLL *temp = head->next;
        temp->prev = newNode;
        newNode->next = temp;
        head->next =newNode;
        newNode->prev = head;
    }

    void deleteNode(DLL *delNode)
    {
        DLL *prevDel = delNode->prev;
        DLL *nextDel = delNode->next;
        prevDel->next = nextDel;
        nextDel->prev = prevDel;
    }


    int cap;
    unordered_map<int,DLL*> mp;
    DLL *head = new DLL(-1,-1);
    DLL *tail = new DLL(-1,-1);

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(mp.find(key)!=mp.end())
        {
            DLL *nodeInMap = mp[key];
            int val = nodeInMap->val;
            mp.erase(key);
            deleteNode(nodeInMap);
            addNode(new DLL(key,val));
            mp[key] = head->next;
            return val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(mp.find(key) != mp.end()) {
            DLL* existingnode = mp[key];
            mp.erase(key);
            deleteNode(existingnode);
        }
        if(mp.size() == cap)
        {
            mp.erase((tail->prev)->key);
            deleteNode((tail->prev));
        }
        addNode(new DLL(key, value));
        mp[key] = head->next;
        return;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
