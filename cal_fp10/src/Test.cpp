#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"
#include "cute/cute_runner.h"

using namespace std;

int kmpMatcher(string text, string pattern);
int editDistance(string pattern, string text);
int numStringMatching(string filename, string toSearch);
float numApproximateStringMatching(string filename, string toSearch);

void test_kmpMatcher() {
	ASSERT_EQUAL(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

	ASSERT_EQUAL(0, kmpMatcher("", "a"));
	ASSERT_EQUAL(1, kmpMatcher("a", "a"));

}

void test_editDistance() {
	ASSERT_EQUAL(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
	ASSERT_EQUAL(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

	ASSERT_EQUAL(1, editDistance("", "b"));
	ASSERT_EQUAL(1, editDistance("a", ""));
	ASSERT_EQUAL(1, editDistance("a", "b"));
	ASSERT_EQUAL(0, editDistance("", ""));
	ASSERT_EQUAL(0, editDistance("a", "a"));
}

void test_numStringMatching() {
	int num1 = numStringMatching("text1.txt", "estrutura de dados");
	ASSERT_EQUAL(3, num1);

	int num2=numStringMatching("text2.txt", "estrutura de dados");
	ASSERT_EQUAL(2,num2);
}

void test_numApproximateStringMatching() {
	float dist1 = numApproximateStringMatching("text1.txt", "estrutur");
	ASSERT_EQUAL_DELTA(7.76, dist1, 0.01);

	float dist2=numApproximateStringMatching("text2.txt", "estrutur");
	ASSERT_EQUAL_DELTA(7.49, dist2, 0.01);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(test_kmpMatcher));
	s.push_back(CUTE(test_numStringMatching));
	s.push_back(CUTE(test_editDistance));
	s.push_back(CUTE(test_numApproximateStringMatching));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}



