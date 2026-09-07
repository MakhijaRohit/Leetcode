// https://www.youtube.com/watch?v=AME6baBpswY 

class Solution {
public:
    void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& vis, int m, int n)
    {
        if(i < 0 || j < 0 || i >= m || j >= n || vis[i][j] || grid[i][j] == '0')
            return;

        vis[i][j] = true;

        dfs(i-1, j, grid, vis, m, n);
        dfs(i, j+1, grid, vis, m, n);
        dfs(i+1, j, grid, vis, m, n);
        dfs(i, j-1, grid, vis, m, n);
    }
    int numIslands(vector<vector<char>>& grid) {
        int isIsland = 0;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> vis(m, vector<bool>(n, false));

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == '1' && !vis[i][j])
                {  
                    dfs(i, j, grid, vis, m, n);
                    isIsland++;
                }
            }
        }
        return isIsland;
    }
};