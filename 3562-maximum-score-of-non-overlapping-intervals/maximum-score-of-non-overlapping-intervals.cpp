#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold the total score and the sorted list of selected indices
struct Element {
    long long weight = 0;
    vector<int> indices;

    // Custom comparator to handle tie-breaking for maximum score and lexicographically smallest indices
    bool isBetterThan(const Element& other) const {
        if (this->weight != other.weight) {
            return this->weight > other.weight;
        }
        // If weights are equal, the lexicographically smaller array of indices is preferred
        return this->indices < other.indices;
    }
};

struct Interval {
    int start;
    int end;
    int weight;
    int id;

    // Sort primarily by start time to facilitate binary searching forward
    bool operator<(const Interval& other) const {
        if (start != other.start) return start < other.start;
        return end < other.end;
    }
};

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& input_intervals) {
        int n = input_intervals.size();
        vector<Interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            intervals[i] = {input_intervals[i][0], input_intervals[i][1], input_intervals[i][2], i};
        }

        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // Precompute the next non-overlapping interval index for each interval using binary search
        vector<int> next_idx(n);
        for (int i = 0; i < n; ++i) {
            int low = i + 1, high = n, ans = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (mid < n && intervals[mid].start > intervals[i].end) {
                    ans = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            next_idx[i] = ans;
        }

        // dp[i][j] stores the best Element considering intervals from index i to n-1 with j intervals remaining to pick
        vector<vector<Element>> dp(n + 1, vector<Element>(5));

        // Bottom-up DP processing from back to front
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j <= 4; ++j) {
                // Option 1: Skip the current interval
                Element best = dp[i + 1][j];

                // Option 2: Take the current interval
                Element take;
                take.weight = intervals[i].weight;
                take.indices = {intervals[i].id};

                int next = next_idx[i];
                if (next < n && j > 1) {
                    take.weight += dp[next][j - 1].weight;
                    // Merge indices
                    take.indices.insert(take.indices.end(), dp[next][j - 1].indices.begin(), dp[next][j - 1].indices.end());
                }
                
                // Keep indices sorted to easily evaluate lexicographical order
                sort(take.indices.begin(), take.indices.end());

                // Select the better choice between taking or skipping
                if (take.isBetterThan(best)) {
                    best = take;
                }

                dp[i][j] = best;
            }
        }

        return dp[0][4].indices;
    }
};
