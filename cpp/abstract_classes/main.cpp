#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
  public:
    LRUCache(int c){cp = c;};
    virtual void set(int k, int v) {
      auto k_it = mp.find(k);
      Node* n;
      if (k_it == mp.end()) {
        n = new Node(k,v);
        mp.insert(std::pair<int,Node*>(k,n));
      }
      else {
        n = mp[k];
        n->value = v;
      }

      if (mp.size() <= 1) {
        head = n;
        tail = n;
      } else {
        head->prev = n; // b --> a
        n->next = head;   // a --> b
        head = n; // a <-> b <-> c ...
      }
      
      int size = mp.size();
      // if capacity has been exceeded we have to remove the tail
      if (size > cp) {
        Node* last = tail;
        tail = last->prev; // update tail to be second last node
        if (tail != NULL) { tail->next = NULL; }
        mp.erase(last->key); // remove the previous tail
        delete last;
      }

    }

    virtual int get(int k) {
      auto it = mp.find(k);
      if (it == mp.end()) {
        return -1;
      }
      else {
        Node* n = mp.at(k);
        int val = n->value;
        
        // Connect the prev of n with the next of n, thereby removing n from the linked list
        auto n_prev = n->prev;
        auto n_next = n->next;
        if (n_prev != NULL) { n_prev->next = n_next; }
        if (n_next != NULL) { n_next->prev = n_prev; }
        
        // Now make n the head of the linked list
        head->prev = n;
        n->next = head;
        n->prev = NULL;
        head = n;

        return val;
      }
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
