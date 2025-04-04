#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

vector<string> playlistManager(const vector<string>& actions) {
    vector<string> playlist;
    stack<string> history;

    for (const string& action : actions) {
        if (action.find("addSong('") == 0) {
            string song = action.substr(9, action.size() - 11); // Extract song name
            playlist.push_back(song);
            history.push(song); // Store for undo
        } 
        else if (action == "undo()") {
            if (!history.empty()) {
                string lastSong = history.top();
                history.pop();
                auto it = find(playlist.begin(), playlist.end(), lastSong);
                if (it != playlist.rend()) {
                    playlist.erase((it + 1).base()); // Erase last occurrence
                }
            }
        }
    }
    
    return playlist;
}

// Please don't remove the code below
int main() {
    string input;
    getline(cin, input);

    vector<string> actions;
    string action;
    stringstream ss(input.substr(1, input.size() - 2)); // Remove brackets

    while (getline(ss, action, ',')) {
        actions.push_back(action.substr(action.find('"') + 1, action.rfind('"') - action.find('"') - 1));
    }

    vector<string> result = playlistManager(actions);

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i != result.size() - 1) cout << ", ";
    }
    cout << "]";
    // Please don't remove the code above
}
