#include<bits/stdc++.h>
using namespace std;


struct Node {
    int cnt, val;
    Node *to[2];

    Node(){
        cnt = 0;
        to[0] = to[1] = NULL;
        val = -1;
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
            int bit = ((1 << i) & val) > 0;

            if(cur->to[bit] == NULL){
                Node *newnode = new Node();
                cur->to[bit] = newnode;
            }

            cur = cur->to[bit];
            cur->cnt++;
        }
        cur->val = val;
    }

    void erase(int val){
        Node *cur = root;
        for(int i = 30; i >= 0; i--){
            int bit = ((1 << i) & val) > 0;

            Node *next = cur->to[bit];
            if(next->cnt == 1){
                cur->to[bit] = NULL;
                break;
            }
            else{
                cur = next;
            }
            cur->cnt--;
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

    int findMax(int x_or){
        Node* cur = root;
        for(int i = 30; i >= 0; i--){
            if((1 << i) & x_or){
                if(cur->to[0] == NULL) cur = cur->to[1];
                else cur = cur->to[0];
            }
            else{
                if(cur->to[1] == NULL) cur = cur->to[0];
                else cur = cur->to[1];
            }
        }
        return cur->val;
    }

    int findMin(int x_or){
        Node* cur = root;
        for(int i = 30; i >= 0; i--){
            if((1 << i) & x_or){
                if(cur->to[1] == NULL) cur = cur->to[0];
                else cur = cur->to[1];
            }
            else{
                if(cur->to[0] == NULL) cur = cur->to[1];
                else cur = cur->to[0];
            }
        }
        return cur->val;
    }

};