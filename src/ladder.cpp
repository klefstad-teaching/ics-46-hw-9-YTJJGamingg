#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " between " << word1 << " and " << word2 << endl;
}

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
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int distance = 0;
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            distance++;
            if (distance > d) return false;
            
            if (len1 > len2) {
                i++;
            } else if (len1 < len2) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    distance += abs(len1 - len2);
    return distance <= d;
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
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
                    cout << "Word ladder found: ";
                    print_word_ladder(new_ladder);
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    cout << "No word ladder found.\n"; 
    return {};
}

void verify_word_ladder() {
}
