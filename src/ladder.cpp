#include "ladder.h"

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true;

    if (word1.length() == word2.length()) {
        int diff_count = 0;
        for (size_t i = 0; i < word1.length(); ++i) {
            if (word1[i] != word2[i]) {
                diff_count++;
            }
        }
        return diff_count == 1;
    } else if (abs((int)word1.length() - (int)word2.length()) == 1) {
        const string& longer = word1.length() > word2.length() ? word1 : word2;
        const string& shorter = word1.length() > word2.length() ? word2 : word1;
        
        size_t i = 0, j = 0;
        bool diff_found = false;
        
        while (i < longer.length() && j < shorter.length()) {
            if (longer[i] != shorter[j]) {
                if (diff_found) {
                    return false;
                }
                diff_found = true;
                i++;
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
    return false;
}
    

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) return false;
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
    for (int i = 0; i <= len1; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= len2; ++j) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;

            dp[i][j] = min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + cost
            });
        }
    }
    return dp[len1][len2] <= d;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start word and end word cannot be the same");
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    print_word_ladder(new_ladder);
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    print_word_ladder({});
    return {};
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " between " << word1 << " and " << word2 << endl;
}


#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
