/*课程表*/
/*广度优先算法*/
#include "../leetcode.h"

class Solution {
    vector<vector<int>> edges;
    vector<int> indeg;
    public:
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
            edges.resize(numCourses);
            indeg.resize(numCourses);
            for (auto info : prerequisites) {
                edges[info[1]].push_back(info[0]);
                indeg[info[0]]++;
            }

            queue<int> q;
            for (int i = 0; i < numCourses; i++) {
                if(indeg[i] == 0) {
                    q.push(i);
                }
            }

            int visited = 0;
            while(!q.empty()) {
                visited++;
                int node = q.front();
                q.pop();
                for (auto k : edges[node]) {
                    indeg[k]--;
                    if (indeg[k] == 0) {
                        q.push(k);
                    }
                }
            }
            return visited == numCourses;
        }
    };