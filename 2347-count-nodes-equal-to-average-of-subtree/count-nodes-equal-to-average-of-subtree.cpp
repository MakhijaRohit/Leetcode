/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int result;
    pair<int, int> solve(TreeNode* root)
    {
        if(!root)
            return {0, 0};

        int totalSum = 0;
        int totalCount = 0;
        int avg = 0;

        auto P1 = solve(root->left);
        auto P2 = solve(root->right);

        totalSum = P1.first + P2.first + root->val;
        totalCount = P1.second + P2.second + 1;

        avg = totalSum / totalCount;

        if(avg == root->val)
            result = result + 1;

        return {totalSum, totalCount};
    }
    int averageOfSubtree(TreeNode* root) {
        result = 0;

        solve(root);

        return result;
    }
};