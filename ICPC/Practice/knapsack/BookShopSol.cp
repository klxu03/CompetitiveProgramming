#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	int x;
	cin >> n >> x;
	vector<int> cost(n);
	vector<int> pages(n);

	for (int i = 0; i < n; i++) {
		cin >> cost[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> pages[i];
	}
	
	/*
	 * dp[i][j] is the most number of pages that can be bought from
	 * the first i books and by spending at most j amount of money.
	 */
	vector<vector<int>> dp(n + 1, vector<int>(x + 1));
	for (int i = 1; i <= n; i++) {
		int curr_cost = cost[i - 1];
		int curr_pages = pages[i - 1];
		for (int j = 1; j <= x; j++) {
			/*
			 * if the current book is not bought, the the number of pages is 
			 * the same as number of pages bought for first i-1 books using 
			 * j amount of money
			 */
			dp[i][j] = dp[i - 1][j];
			if (curr_cost <= j) {
				/*
				 * if the current book can be bought, then store the most 
				 * number of pages using the remaining money after buying
				 * the current book plus the pages for the current book.
				 */
				dp[i][j] = max(dp[i][j], dp[i - 1][j - curr_cost] + curr_pages);
			}
		}
	}
	cout << dp[n][x] << '\n';
}