#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> Strlist;
        for (auto word : wordList) {
            Strlist.insert(word);
        }

        if (Strlist.find(endWord) == Strlist.end()) return 0;

        unordered_map<string, int> visited_map; // 记录每个字母的在路径中的长度
        queue<string> que;
        que.push(beginWord);
        visited_map.insert({beginWord, 1});

        while (!que.empty()) {
            string word = que.front();
            que.pop();
            int path = visited_map[word];
            for (int i = 0; i < word.size(); i++) {     //一个单词的n * 26种变换
                string new_word = word;
                for (int j = 0; j < 26; j++) {
                    new_word[i] = j + 'a';
                    if (new_word == endWord) {
                        return path + 1;
                    }

                    if (new_word[i] == word[i]) continue;
                    
                    if (Strlist.find(new_word) == Strlist.end() || visited_map.find(new_word) != visited_map.end()) {
                        continue;
                    }
                    que.push(new_word);
                    visited_map.insert({new_word, path + 1});
                }
            }
        }
        return 0;
    }
};