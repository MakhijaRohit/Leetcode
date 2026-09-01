class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        /*
        कचरे की नंबरिंग (Mapping Litter): हमने पूरे ग्रिड में घूमकर जहाँ भी 'L' था, उसे एक ID दे दी (जैसे पहले कचरे को 0, दूसरे को 1). इससे हमें mask में बिट्स सेट करने में आसानी होगी.
        */

        int m = classroom.size();
        int n = classroom[0].size();

        map<pair<int, int>, int> litter_map;

        int start_row = -1, start_col = -1;

        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(classroom[i][j] == 'S')
                {
                    start_row = i;
                    start_col = j;
                }
                else if(classroom[i][j] == 'L')
                {
                    litter_map[{i, j}] = litter_map.size();
                }
            }
        }

        int total_litters = litter_map.size();
        int target_mask = (1 << total_litters) - 1;

        /*
        स्टेट और ऊर्जा (State Tracking): max_energy_at_state[r][c][mask] का मतलब है कि रो r, कॉलम c पर, mask जितने कचरे उठाने के बाद हमारे पास अधिकतम कितनी ऊर्जा बची है.
        */

        vector<vector<vector<int>>> max_energy_at_state(m, vector<vector<int>>(n, vector<int>(1 << total_litters, -1)));

        queue<vector<int>> q;
        q.push({start_row, start_col, 0});
        max_energy_at_state[start_row][start_col][0] = energy;
        
        int moves = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        /*
        BFS का काम: हम शुरुआती बिंदु 'S' से चलना शुरू करते हैं. हर कदम पर ऊर्जा 1 कम होती है
        */
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto curr = q.front();
                q.pop();
                
                int r = curr[0];
                int c = curr[1];
                int mask = curr[2];
                int curr_e = max_energy_at_state[r][c][mask];
                
                // यदि सारा कचरा साफ हो गया है, तो यही न्यूनतम स्टेप्स हैं
                if (mask == target_mask) {
                    return moves;
                }
                
                // अगर इस स्टेट पर वर्तमान ऊर्जा पुरानी ऊर्जा से कम है, तो इसे स्किप करें
                if (curr_e == 0) continue; 

                /*
                कंडीशन चेक:
                अगर हम 'R' पर कदम रखते हैं, तो ऊर्जा दोबारा energy (फुल) हो जाती है.
                अगर हम नए 'L' पर जाते हैं, तो mask में उस कचरे की बिट को 1 कर देते हैं (next_mask |= (1 << litter_idx)).
                अगर हमारी बची हुई ऊर्जा 0 हो जाती है और वह जगह 'R' नहीं है, तो हम आगे नहीं बढ़ सकते.
                */
                
                // 4 दिशाओं में चलें
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    
                    // बाउंड्री और ऑब्सटैकल चेक
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int next_e = curr_e - 1; // 1 कदम चलने पर ऊर्जा -1 हुई
                        int next_mask = mask;
                        
                        // यदि नए सेल में कचरा 'L' है
                        if (classroom[nr][nc] == 'L') {
                            int litter_idx = litter_map[{nr, nc}];
                            next_mask |= (1 << litter_idx); // उस कचरे की बिट को 1 सेट करें
                        }
                        
                        // यदि नए सेल में रीसेट 'R' है, तो ऊर्जा फुल हो जाएगी
                        if (classroom[nr][nc] == 'R') {
                            next_e = energy;
                        }
                        
                        // यदि इस नए स्टेट पर हमें पहले से ज़्यादा ऊर्जा मिल रही है, तभी आगे बढ़ें
                        if (next_e > max_energy_at_state[nr][nc][next_mask]) {
                            max_energy_at_state[nr][nc][next_mask] = next_e;
                            q.push({nr, nc, next_mask});
                        }
                    }
                }
            }
            moves++; // हर लेवल के बाद कदम बढ़ाएं
        }
        
        return -1; // यदि सारा कचरा साफ करना असंभव हो
    }
};