#include <bits/stdc++.h>

using namespace std;

void recurse(vector<int> &left, int n) {
	if (n <= 1) {
		for(int i = 0; i < left.size(); i++) {
			cout << left[i] << " ";
		}

		if (n == 1) {
			cout << 1;		
		}
		cout << endl;
		return;
	}

    // 2 2
    // 2 1 1
    // 
    // 1
    // 1 2
    // 1 1

    left.push_back(2);

	// merge
	recurse(left, n - 2);

    left.pop_back();

    // 1 1 1
    // 1 1
    // 1 1 1
    // 1 1 

    left.push_back(1);
	// no merge
	recurse(left, n - 1);

    left.pop_back();

    // 1         n - 4
    // 1 1       n - 3
    // 1 1 1     n - 2
    // 1 1 1     n - 2
    // 1 1 1 1 1 n - 1

}

int main() {
    int n;
	cin >> n;

    vector<int> inp;
	recurse(inp, n);
}
