#include <bits/stdc++.h>
using namespace std;

struct Node{
    char val;
    map<char, Node*> next;
    int cnt;
};

struct Trie{
    Node* root;

    void init(){
        root = new Node();
        root->cnt = 0;
        root->val = '$';
    }

    void insert(string& s){
        Node* cur = root;
        for(char c: s){
            if(cur->next.find(c) == cur->next.end()){
                Node* newnode = new Node();
                newnode->val = c;
                newnode->cnt = 0;
                cur->next[c] = newnode;
            }

            cur = cur->next[c];
        }
        cur->cnt++;
    }

    int find(string& s){
        Node* cur = root;
        for(char c: s){
            if(cur->next.find(c) == cur->next.end()) return 0;
            cur = cur->next[c];
        }

        return cur->cnt;
    }

};