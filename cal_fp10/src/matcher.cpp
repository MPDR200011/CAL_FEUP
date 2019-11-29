/*
 * matcher.cpp
 */
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<int> KMPComputePrefixFunction(string pattern) {
	size_t m = pattern.length();
	vector<int> pi(m);
	pi[0] = -1;

	int k = 0;
	int q = 1;
	for (; q < m; q++) {
		if (pattern[k] == pattern[q]) {
			pi[q] = pi[k];
		} else {
			pi[q] = k;
			k = pi[k];
			while (k >= 0 && pattern[k] != pattern[q]) {
				k = pi[k];
			}
		}
		k++;
	}
	
	pi[q] = k;

	return pi;
}

int kmpMatcher(string text, string pattern) {
	size_t textLength = text.length();
	size_t patternLenght = pattern.length();

	vector<int> pi = KMPComputePrefixFunction(pattern);

	int nP = 0;
	int k = 0;
	int j = 0;
	while (j < textLength) {
		if (pattern[k] == text[j]) {
			j++;
			k++;
			if (k == patternLenght) {
				nP++;
				k = pi[k];
			}

		} else {
			k = pi[k];
			if (k < 0) {
				j++;
				k++;
			}
		}
	}

	return nP;
}


int numStringMatching(string filename, string toSearch) {

	ifstream input;
    input.open(filename);
    
	if (!input.is_open()) {
		cout << "nao abriu\n";
	}

	int sum = 0;
	string line;
	while (getline(input, line)) {
		sum += kmpMatcher(line, toSearch);
	}

	input.close();

	return sum;
}


int editDistance(string pattern, string text) {
	// TODO
	return 0;
}

float numApproximateStringMatching(string filename,string toSearch) {
	// TODO
	return 0;
}
