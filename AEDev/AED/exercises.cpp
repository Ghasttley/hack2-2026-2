//
// Created by LENOVO on 02/09/2026.
//

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <iostream>

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        ListNode* it= head;
        while(it->next!=nullptr){
            if(it->val > it->next->val){
                int temp= it->val;
                it->val=it->next->val;
                it->next->val=temp;
            }
            it=it->next;
        }
        return head;

    }
};