class Solution {
public:
    bool isRectangleOverlap(std::vector<int>& rec1, std::vector<int>& rec2) {
        // A rectangle overlaps only if both X-axis and Y-axis intervals overlap
        return rec1[0] < rec2[2] && rec2[0] < rec1[2] && // X-axis check
               rec1[1] < rec2[3] && rec2[1] < rec1[3];   // Y-axis check
    }
};
