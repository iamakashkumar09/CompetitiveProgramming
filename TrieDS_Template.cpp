#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. The Node Structure
struct node {
    node *child[26];
    int prefix;             // Counts how many words pass through this node
    vector<string> wend;    // Stores the exact word(s) that end at this node

    node() {
        prefix = 0;
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
    }
};

// 2. The Trie Structure and Methods
struct trie {
    node *root;

    trie() {
        root = new node();
    }

    // Insert a word into the Trie
    void insert(string word) {
        node *curr = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (curr->child[index] == NULL) {
                curr->child[index] = new node();
            }
            curr = curr->child[index];
            curr->prefix++; // Increment traffic counter
        }
        curr->wend.push_back(word); // Store the full word at the end
    }

    // Check if an EXACT word exists
    bool searchWord(string word) {
        node *curr = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (curr->child[index] == NULL) {
                return false;
            }
            curr = curr->child[index];
        }
        return curr->wend.size() > 0;
    }

    // Find exactly how many words start with this prefix
    int countWordsStartingWith(string prefixStr) {
        node *curr = root;
        for (int i = 0; i < prefixStr.length(); i++) {
            int index = prefixStr[i] - 'a';
            if (curr->child[index] == NULL) {
                return 0; // Branch died early
            }
            curr = curr->child[index];
        }
        return curr->prefix; // O(1) return once we reach the node
    }

    // Delete a word (logical deletion by decrementing counters)
    void deleteWord(string word) {
        // IMPORTANT: Always ensure the word exists before deleting
        if (!searchWord(word)) return; 

        node *curr = root;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            curr = curr->child[index];
            curr->prefix--; // Decrement traffic counter
        }
        curr->wend.pop_back(); // Remove one instance of the word
    }
};

// --- Example Usage ---

int main() {
    trie myTrie;
    
    myTrie.insert("apple");
    myTrie.insert("app");
    myTrie.insert("apricot");
    myTrie.insert("bat");

    cout << "Does 'app' exist? " << myTrie.searchWord("app") << endl; // 1 (true)
    cout << "Words starting with 'ap': " << myTrie.countWordsStartingWith("ap") << endl; // 3
    
    myTrie.deleteWord("app");
    cout << "Words starting with 'ap' after deleting 'app': " << myTrie.countWordsStartingWith("ap") << endl; // 2
    
    return 0;
}
