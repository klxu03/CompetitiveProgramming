#include <bits/stdc++.h>

using namespace std;

void recurse(vector<int> left, int n) {
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

    vector<int> copy = left;
    copy.push_back(2);

	// merge
	recurse(copy, n - 2);

    copy.pop_back();
    copy.push_back(1);
	// no merge
	recurse(copy, n - 1);
}

int main() {
    int n;
	cin >> n;
	recurse({}, n);
}
