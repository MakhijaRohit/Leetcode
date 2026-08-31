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
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // Agar list me 3 se kamm nodes hai to critical point hona possible nhi hai.
        if(!head || !head->next || !head->next->next)
        {
            return {-1, -1};
        }

        int minDistance = INT_MAX;
        int first_cp = -1;
        int prev_cp = -1;
        int index = 1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while(curr->next != nullptr)
        {
            ListNode* nextNode = curr->next;

            bool isMaxima = (curr->val > prev->val && curr->val > nextNode->val);
            bool isMinima = (curr->val < prev->val && curr->val < nextNode->val);

            if(isMaxima || isMinima)
            {
                // Agar ye pehla hi critical point hai
                if(first_cp == -1)
                {
                    first_cp = index;
                }
                else
                {
                    // Agar pehle bhi mil chuke hai, to vatmaan index aur pichle index ha antarr nikale
                    minDistance = min(minDistance, index - prev_cp);
                }
                // ab iss point ko pichla bna de taaki aage tulna ho sake
                prev_cp = index;
            }
            // Pointers ko aage badaye
            prev = curr;
            curr = nextNode;
            index++;
        }

        // Agar minDistance badla hi nhi, iska matlab hume 2 critical points mile hi nhi
        if(minDistance == INT_MAX)
        {
            return {-1, -1};
        }

        // Max Distance
        int maxDistance = prev_cp - first_cp;

        return {minDistance, maxDistance};
    }
};