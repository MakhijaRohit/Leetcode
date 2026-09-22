#include <vector>
#include <iostream>

using namespace std;

// Flattened node structure to represent a segment in the tree
struct SegmentNode {
    int prod = 1;
    // Using a fixed size or a dynamically sized array per problem constraints.
    // Since k is typically small (e.g., <= 100 or specific constraints), vector or inline array works.
    vector<int> remain; 
};

class Solution {
    int n;
    int K;
    vector<SegmentNode> tree;

    // In-place merge to avoid object copies
    void mergeNodes(const SegmentNode& left, const SegmentNode& right, SegmentNode& res) {
        res.prod = (1LL * left.prod * right.prod) % K;
        
        // Zero out the target array cleanly
        fill(res.remain.begin(), res.remain.end(), 0);
        
        // Accumulate left side remains
        for (int j = 0; j < K; ++j) {
            if (left.remain[j] > 0) {
                res.remain[j] += left.remain[j];
            }
        }
        
        // Transition right side remains based on the left total product
        long long leftProd = left.prod;
        for (int j = 0; j < K; ++j) {
            if (right.remain[j] > 0) {
                int nextRem = (j * leftProd) % K;
                res.remain[nextRem] += right.remain[j];
            }
        }
    }

    void build(const vector<int>& nums, int cur, int left, int right) {
        tree[cur].remain.assign(K, 0);
        if (left == right) {
            int val = nums[left] % K;
            tree[cur].remain[val] = 1;
            tree[cur].prod = val;
            return;
        }
        int mid = left + (right - left) / 2;
        build(nums, 2 * cur + 1, left, mid);
        build(nums, 2 * cur + 2, mid + 1, right);
        mergeNodes(tree[2 * cur + 1], tree[2 * cur + 2], tree[cur]);
    }

    void update(int cur, int lo, int hi, int idx, int val) {
        if (lo == hi) {
            fill(tree[cur].remain.begin(), tree[cur].remain.end(), 0);
            tree[cur].remain[val] = 1;
            tree[cur].prod = val;
            return;
        }
        int mid = lo + (hi - lo) / 2;
        if (idx <= mid) {
            update(2 * cur + 1, lo, mid, idx, val);
        } else {
            update(2 * cur + 2, mid + 1, hi, idx, val);
        }
        mergeNodes(tree[2 * cur + 1], tree[2 * cur + 2], tree[cur]);
    }

    // Optimization: Pass an external accumulator node by reference to eliminate copy overhead
    void query(int cur, int lo, int hi, int ql, int qr, SegmentNode& accumulator, bool& isFirst) {
        if (ql <= lo && hi <= qr) {
            if (isFirst) {
                accumulator.prod = tree[cur].prod;
                accumulator.remain = tree[cur].remain;
                isFirst = false;
            } else {
                // Temporary buffer to avoid overwrite mid-computation
                static SegmentNode temp;
                if (temp.remain.size() != K) temp.remain.resize(K);
                mergeNodes(accumulator, tree[cur], temp);
                accumulator = temp;
            }
            return;
        }
        int mid = lo + (hi - lo) / 2;
        if (ql <= mid) {
            query(2 * cur + 1, lo, mid, ql, qr, accumulator, isFirst);
        }
        if (qr > mid) {
            query(2 * cur + 2, mid + 1, hi, ql, qr, accumulator, isFirst);
        }
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // Optimize standard I/O operations for LeetCode
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        n = nums.size();
        K = k;
        tree.resize(4 * n);
        
        build(nums, 0, 0, n - 1);
        
        vector<int> res;
        res.reserve(queries.size());
        
        SegmentNode accNode;
        accNode.remain.resize(K);

        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1] % K;
            int start = q[2];
            int xi = q[3];
            
            // Step 1: Perform the point update
            update(0, 0, n - 1, idx, val);
            
            // Step 2: Query the range from [start, n-1]
            bool isFirst = true;
            query(0, 0, n - 1, start, n - 1, accNode, isFirst);
            
            // Step 3: Fetch the calculated count matching the remainder xi
            res.push_back(accNode.remain[xi]);
        }
        
        return res;
    }
};
