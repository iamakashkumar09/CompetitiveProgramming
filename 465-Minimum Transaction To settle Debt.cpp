/*
 * APPROACH (Backtracking with Positive and Negative Balance Vectors):
 * 
 * 1. Net Balances: Calculate the net balance for each person. If a person 
 *    gives money, their balance decreases. If they receive, it increases.
 * 2. Separation: Separate all NON-ZERO balances into two vectors: 
 *    'pos' (people who are owed money) and 'neg' (people who owe money).
 * 3. Backtracking (The solve function):
 *    - Base Case: If either 'pos' or 'neg' is empty, all debts are settled.
 *    - Take the last negative balance `n = neg.back()` and temporarily remove it.
 *    - Loop through EVERY positive balance `p = pos[i]` to try and settle `n` with `p`.
 *    - Remove `p` from `pos` and calculate the combined remaining balance: `rem = p + n`.
 *    - Three scenarios arise:
 *        a) rem == 0: Both are perfectly settled. Recurse (add 1 transaction).
 *        b) rem > 0:  The positive balance was larger. Push the remaining positive 
 *                     balance back to `pos` and recurse (add 1 transaction).
 *        c) rem < 0:  The negative balance was larger (absolute value). Push the 
 *                     remaining negative balance to `neg` and recurse (add 1 transaction).
 *    - Backtrack: Undo all vector modifications (pop the remainder, re-insert `p`) 
 *                 so the loop can try pairing `n` with the next positive balance.
 *    - Finally, restore `n` to the `neg` vector for the parent recursive calls.
 * 4. Return the minimum transactions found across all possible matching combinations.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int solve(vector<int>& pos, vector<int>& neg) {
        // If either list is empty, all net non-zero debts have been settled
        if (pos.empty() || neg.empty()) return 0;
        
        // Take one negative debt to settle
        int n = neg.back();
        neg.pop_back();
        
        int ans = INT_MAX;
        
        // Try settling this negative debt with every possible positive debt
        for (int i = 0; i < pos.size(); i++) {
            int p = pos[i];
            int rem = p + n;
            int curr = 0;
            
            // Step 1: Temporarily remove the positive balance we are pairing with
            pos.erase(pos.begin() + i);
            
            // Step 2: Settle them and recurse based on the remainder
            if (rem == 0) {
                // Exact match: both are settled
                curr = 1 + solve(pos, neg);
            } else if (rem > 0) {
                // Positive remains: push to pos, recurse, then backtrack
                pos.push_back(rem);
                curr = 1 + solve(pos, neg);
                pos.pop_back();
            } else {
                // Negative remains: push to neg, recurse, then backtrack
                neg.push_back(rem);
                curr = 1 + solve(pos, neg);
                neg.pop_back(); 
            }
            
            // Step 3: Backtrack the removal of the original positive balance
            pos.insert(pos.begin() + i, p);
            
            // Track the minimum transactions needed across all pairings
            ans = min(ans, curr);
        }
        
        // Backtrack the removal of the original negative debt
        neg.push_back(n);
        
        return ans;
    }

    int getMinTransactions(int n, vector<vector<int>>& debt) {
        unordered_map<int, int> um;
        
        // Calculate net balance for each person
        for (int i = 0; i < debt.size(); i++) {
            um[debt[i][0]] -= debt[i][2];
            um[debt[i][1]] += debt[i][2];
        }

        vector<int> pos, neg;
        
        // Separate strictly positive and strictly negative balances
        for (auto &e : um) {
            if (e.second > 0) {
                pos.push_back(e.second);
            } else if (e.second < 0) {
                neg.push_back(e.second);
            }
        }

        return solve(pos, neg);
    }
};

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (cin >> n >> m) {
        vector<vector<int>> debt(m, vector<int>(3));
        for (int i = 0; i < m; ++i) {
            cin >> debt[i][0] >> debt[i][1] >> debt[i][2];
        }
        Solution sol;
        cout << sol.getMinTransactions(n, debt) << "\n";
    }
    return 0;
}
