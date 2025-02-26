/*最小基因变化*/
#include "../leetcode.h"

class Solution {
    public:
        int minMutation(string startGene, string endGene, vector<string>& bank) {
            if ((startGene == endGene)) return 0;

            unordered_set<string> bankSet(bank.begin(), bank.end());

            if (bankSet.find(endGene) == bankSet.end()) {
                return -1;
            }

            vector<char> mutations = {'A', 'C', 'G', 'T'};
            queue<pair<string, int>> q;
            q.push({startGene, 0});

            unordered_set<string> visited;
            visited.insert(startGene);


            while (!q.empty()){
                auto curr = q.front();
                q.pop();
                auto currGene = curr.first;
                int steps = curr.second;
                
                for (int i = 0; i < 8; i++) {
                    char originalChar = currGene[i];

                    for (char c : mutations) {
                        if (c == originalChar){
                            continue;
                        }

                        string newGene = currGene;
                        newGene[i] = c;

                        if (newGene == endGene) {
                            return steps + 1;
                        }
                        
                        if (bankSet.find(newGene) != bankSet.end() && visited.find(newGene) == visited.end()){
                            visited.insert(newGene);
                            q.push({newGene, steps + 1});
                        }
                    }
                }
            }
            return -1;
        }
};

