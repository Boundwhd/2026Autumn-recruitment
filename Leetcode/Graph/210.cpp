/*课程表II*/
#include "../leetcode.h"

class Solution {
        vector<int> result;
        vector<int> indeg;
        vector<vector<int>> edge;
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            indeg.resize(numCourses);
            edge.resize(numCourses);
            for(auto info : prerequisites) {
                edge[info[1]].push_back(info[0]);
                ++indeg[info[0]];
            }

            queue<int> q;
            for (int i = 0; i < edge.size(); i++) {
                if (indeg[i] == 0) {
                    q.push(i);
                }
            }

            int visit = 0;
            while (!q.empty()) {
                visit++;
                int u = q.front();
                result.push_back(u);
                q.pop();
                for (auto k : edge[u]) {
                    indeg[k]--;
                    if (indeg[k] == 0) {
                        q.push(k);
                    }
                }
            }

            if (visit != numCourses) return {};
            return result;
        }
    };