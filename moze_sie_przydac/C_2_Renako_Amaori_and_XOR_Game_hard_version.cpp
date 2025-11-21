#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

// Maximum number of bits to consider (since a_i, b_i <= 10^6 < 2^20)
const int MAX_BITS = 20;

// DP table: dp[k][state]
// k: current bit (from MAX_BITS-1 down to 0)
// state: 0 (Tie), 1 (Ajisai winning in MSBs), 2 (Mai winning in MSBs)
// The value of dp[k][state] is the final outcome: 0 (Tie), 1 (Ajisai), 2 (Mai)
int dp[MAX_BITS][3];

// Global variables for the current test case
int N;
vector<int> A, B;
int S; // Invariant XOR sum: S = XOR(A) XOR XOR(B)

// Helper function to extract the k-th bit
int get_bit(int val, int k) {
    return (val >> k) & 1;
}

/**
 * @brief Solves the game using Dynamic Programming on the bit position.
 * * @param k Current bit position (MSB to LSB).
 * @param state Current leading status (0: Tie, 1: Ajisai winning, 2: Mai winning).
 * @return int The final outcome (0: Tie, 1: Ajisai, 2: Mai) under optimal play.
 */
int solve_dp(int k, int state) {
    // Base case: no more bits. The winner is determined by the previous bits (state).
    if (k < 0) {
        if (state == 1) return 1; 
        if (state == 2) return 2;
        return 0;
    }

    if (dp[k][state] != -1) {
        return dp[k][state];
    }

    // 1. Determine control and the initial XOR sum X_initial for bit k
    
    // X_initial: XOR sum of all A[i] bits at position k.
    // This is the value of X if no swaps occur.
    int X_initial = 0; 
    int count_A = 0; // Number of odd indices i where a_i^k != b_i^k (Ajisai's control)
    int count_M = 0; // Number of even indices i where a_i^k != b_i^k (Mai's control)

    for (int i = 0; i < N; ++i) {
        int a_bit = get_bit(A[i], k);
        int b_bit = get_bit(B[i], k);
        
        X_initial ^= a_bit;

        if (a_bit != b_bit) {
            // Swappable pair
            if ((i + 1) % 2 != 0) { // i+1 is odd (Ajisai's turn)
                count_A++;
            } else { // i+1 is even (Mai's turn)
                count_M++;
            }
        }
    }
    
    // 2. Determine the set of achievable XOR sums for Ajisai (A_k)
    vector<int> achievable_X;
    
    // If no one can swap, X is fixed. Otherwise, both 0 and 1 are achievable due to parity control.
    bool fixed = (count_A == 0 && count_M == 0);
    if (fixed) {
        achievable_X = {X_initial};
    } else {
        // If one or both players have control, they can collectively ensure 
        // that the total number of swaps (which flips the parity of X) is even or odd.
        achievable_X = {0, 1};
    }
    
    // 3. Determine who chooses the value of X from A_k
    // Ajisai controls if they have at least one swappable index.
    bool ajisai_chooses = (count_A > 0);
    // Mai controls only if Ajisai has NO control and Mai has control.
    bool mai_chooses = (count_A == 0 && count_M > 0);

    // 4. Find the optimal outcome
    int best_outcome;
    
    if (fixed) {
        // Only one X is possible, just take the result
        best_outcome = 2; // Temporary value
    } else if (ajisai_chooses) {
        // Ajisai maximizes their outcome: 1 (Win) > 0 (Tie) > 2 (Loss)
        best_outcome = 2; 
    } else { // mai_chooses
        // Mai minimizes Ajisai's outcome (Maximizes Mai's): 2 (Loss) > 0 (Tie) > 1 (Win)
        best_outcome = 1; 
    }

    for (int X : achievable_X) {
        // Calculate Y (Mai's XOR bit)
        int S_k = get_bit(S, k);
        int Y = X ^ S_k;

        // Calculate the next state (new_state) based on the current state and (X, Y)
        int new_state = state; 
        if (state == 0) { // Only change state if currently tied
            if (X == 1 && Y == 0) { 
                new_state = 1; // Ajisai takes the lead
            } else if (X == 0 && Y == 1) { 
                new_state = 2; // Mai takes the lead
            }
        }

        // Recursively find the outcome from the next bit
        int current_outcome = solve_dp(k - 1, new_state);

        // Update the best_outcome based on who controls
        if (fixed) {
            // Since there's only one choice, the outcome is that choice.
            best_outcome = current_outcome;
            break; // Exit loop since there's only one choice
        } else if (ajisai_chooses) {
            // Ajisai maximizes the outcome: (1 > 0 > 2)
            if (current_outcome == 1) {
                best_outcome = 1; 
            } else if (current_outcome == 0 && best_outcome != 1) {
                best_outcome = 0; 
            }
        } else { // mai_chooses
            // Mai minimizes Ajisai's outcome: (2 > 0 > 1)
            if (current_outcome == 2) {
                best_outcome = 2; 
            } else if (current_outcome == 0 && best_outcome != 2) {
                best_outcome = 0; 
            }
        }
    }

    return dp[k][state] = best_outcome;
}

void solve() {
    cin >> N;
    A.resize(N);
    B.resize(N);
    S = 0;

    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
        S ^= (A[i] ^ B[i]);
    }

    // Initialize DP table
    for (int i = 0; i < MAX_BITS; ++i) {
        for (int j = 0; j < 3; ++j) {
            dp[i][j] = -1;
        }
    }

    // The game starts from the MSB in a Tie state (0)
    int result = solve_dp(MAX_BITS - 1, 0);

    if (result == 1) {
        cout << "Ajisai" << endl;
    } else if (result == 2) {
        cout << "Mai" << endl;
    } else {
        cout << "Tie" << endl;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}