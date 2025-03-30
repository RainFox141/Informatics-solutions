#include <bits/stdc++.h>
using namespace std;

#define int long long       // Use long long for all integer variables
#define endl '\n'           // Newline shortcut

typedef long long ll;
typedef pair<int, int> pii;

signed main() {
    // Optional: redirect input/output from files for local testing
    // freopen("addin.txt", "r", stdin);
    // freopen("addout.txt", "w", stdout);

    // Speed up I/O operations
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, c;
    cin >> r >> c;  // Read number of rows and columns

    int ans = 0;    // Variable to store the final answer

    // Declare 2D arrays for storing the minimum values and dynamic programming results.
    // Both arrays have an extra row and column to simplify boundary conditions.
    int mingrid[r + 1][c + 1];
    int dp[r + 1][c + 1];

    // Initialize arrays with zeros
    memset(mingrid, 0, sizeof(mingrid));
    memset(dp, 0, sizeof(dp));

    // Set the first row and first column of mingrid to INT_MAX.
    // This ensures that the "minimum" comparison works correctly in the DP recurrence.
    for (int i = 0; i <= c; i++) {
        mingrid[0][i] = INT_MAX;
    }
    for (int i = 0; i <= r; i++) {
        mingrid[i][0] = INT_MAX;
    }

    // Process the input grid and build the mingrid table.
    // mingrid[i+1][j+1] will hold the minimum value among:
    // - The current cell value (x)
    // - The value from the top (mingrid[i][j+1])
    // - The value from the left (mingrid[i+1][j])
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int x;
            cin >> x;  // Read the current grid value

            // Determine the minimum value so far from the top or left neighbors.
            int minval = min(mingrid[i][j + 1], mingrid[i + 1][j]);
            // Update mingrid for the current position.
            mingrid[i + 1][j + 1] = min(x, minval);
        }
    }

    // Build the DP table to compute the maximum possible value.
    // The dp recurrence considers two options:
    // 1. Extending from the top (dp[i][j+1]) and adding the contribution of the current column.
    // 2. Extending from the left (dp[i+1][j]) and adding the contribution of the current row.
    // The contribution from the current cell is given by mingrid[i+1][j+1] multiplied by
    // either the number of columns (j+1) or the number of rows (i+1) considered so far.
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            dp[i + 1][j + 1] = max(
                dp[i][j + 1] + mingrid[i + 1][j + 1] * (j + 1),  // Option from above
                dp[i + 1][j] + mingrid[i + 1][j + 1] * (i + 1)     // Option from the left
            );
            // Update the answer with the maximum dp value computed so far.
            ans = max(ans, dp[i + 1][j + 1]);
        }
    }

    // Output the final answer.
    cout << ans;
    return 0;
}
