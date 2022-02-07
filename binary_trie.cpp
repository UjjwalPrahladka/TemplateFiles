#include<bits/stdc++.h>
using namespace std;


struct Node {
    int cnt;
    Node *to[2];

    Node(){
        cnt = 0;
        to[0] = to[1] = NULL;
    }

    void increment(){
        cnt++;
    }

    void decrement(){
        cnt--;
    }
};


struct Trie{
    Node *root;

    Trie(){
        root = new Node();
    }

    void insert(int val){
        Node *cur = root;

        for(int i = 30; i >= 0; i--){
            int bit;
            if((1 << i) & val){
                bit = 1;
            }
            else{
                bit = 0;
            }


            if(cur->to[bit] == NULL){
                Node *newnode = new Node();
                cur->to[bit] = newnode;
            }

            cur = cur->to[bit];
            cur->increment();
        }
    }

    void erase(int val){
        Node *cur = root;
        for(int i = 30; i >= 0; i--){
            int bit;
            if((1 << i) & val){
                bit = 1;
            }
            else{
                bit = 0;
            }

            Node *next = cur->to[bit];
            if(next->cnt == 1){
                cur->to[bit] = NULL;
                break;
            }
            else{
                cur = next;
            }
            cur->decrement();
        }
    }


    // find cnt of elements which has ai xor val < lim
    int find(int val, int lim){
        Node *cur = root;
        int ans = 0;
        for(int i = 30; i >= 0 && cur; i--){

            if((1 << i) & val){

                if((1 << i) & lim){
                    ans += (cur->to[1] ? cur->to[1]->cnt : 0);
                    cur = cur->to[0];
                }
                else{
                    cur = cur->to[1];
                }
            }
            else{

                if((1 << i) & lim){
                    ans += (cur->to[0] ? cur->to[0]->cnt : 0);
                    cur = cur->to[1];
                }
                else{
                    cur = cur->to[0];
                }

            }
        }

        return ans;
    }
};
