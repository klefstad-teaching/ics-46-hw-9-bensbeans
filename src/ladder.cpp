#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " for words " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;
    int differences = 0;
    int i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            differences++;
            if (differences > d) return false; 

            if (len1 > len2) i++;  
            else if (len1 < len2) j++; 
            else { i++; j++; } 
        } else {
            i++; j++;  
        }
    }

    differences += (len1 - i) + (len2 - j);
    return differences <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> _get_neighbor(const string& current_word, const set<string>& dictionary, set<string>& visited) {
    vector<string> neighbors;
    for (const string& word : dictionary) {
        if (is_adjacent(current_word, word) && !visited.count(word)) {
            neighbors.push_back(word);
        }
    }
    return neighbors;
}

bool _expand(queue<vector<string>>& ladder_queue, set<string>& visited, const vector<string>& current_ladder, const vector<string>& neighbors, const string& end_word, int& steps) {
    for (const string& neighbor : neighbors) {
        visited.insert(neighbor);
        vector<string> new_ladder = current_ladder;
        new_ladder.push_back(neighbor);
        if (neighbor == end_word) {
            cout << "Ladder found in " << steps << " steps." << endl;
            ladder_queue.push(new_ladder);
            return true; 
        }
        ladder_queue.push(new_ladder);
    }
    return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and End words cannot be the same!");
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    int steps = 0;

    while (!ladder_queue.empty()) {
        steps++;
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        vector<string> neighbors = _get_neighbor(last_word, word_list, visited);
        if (_expand(ladder_queue, visited, ladder, neighbors, end_word, steps)) {
            return ladder_queue.back(); 
        }
    }

    cout << "No ladder after " << steps << " steps." << endl;
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
        cout << "Word ladder not found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ladder[i];
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
