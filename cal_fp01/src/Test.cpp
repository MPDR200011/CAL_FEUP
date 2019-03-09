#include "Defs.h"
#include "Factorial.h"
#include "Change.h"
#include "Sum.h"
#include "Partitioning.h"

#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"
#include "cute/cute_runner.h"

void factorialTest()
{
        ASSERT_EQUAL(120,factorialRecurs(5));
        ASSERT_EQUAL(3628800,factorialRecurs(10));
        ASSERT_EQUAL(120,factorialDinam(5));
        ASSERT_EQUAL(3628800,factorialDinam(10));
}

void calcChangeTest()
{
	int numCoins = 3;
	int coinValues[] = {1, 2, 5};


	ASSERT_EQUAL("5;",calcChange(5, numCoins, coinValues));
	ASSERT_EQUAL("5;5;5;1;",calcChange(16, numCoins, coinValues));
	ASSERT_EQUAL("",calcChange(0, numCoins, coinValues));

	int numCoins2 = 2;
	int coinValues2[] = {2, 5};
	ASSERT_EQUAL("-", calcChange(1, numCoins2, coinValues2));
	ASSERT_EQUAL("5;2;",calcChange(7, numCoins2, coinValues2));

	int numCoins3 = 3;
	int coinValues3[] = {1, 4, 5};
	ASSERT_EQUAL("4;4;",calcChange(8, numCoins3, coinValues3));

}


void calcSumArrayTest()
{
	int sequence[5] = {4,7,2,8,1};
	int sequence2[9] = {6,1,10,3,2,6,7,2,4};

	ASSERT_EQUAL("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
	ASSERT_EQUAL("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
}

void partitioningTest()
{
	ASSERT_EQUAL(3025,s_recursive(9,3));
	ASSERT_EQUAL(22827,s_recursive(10,6));
	ASSERT_EQUAL(3025,s_dynamic(9,3));
	ASSERT_EQUAL(22827,s_dynamic(10,6));
	ASSERT_EQUAL(22827,s_dynamic(10,6));
	ASSERT_EQUAL(5,b_recursive(3));
	ASSERT_EQUAL(1382958545,b_recursive(15));
	ASSERT_EQUAL(5,b_dynamic(3));
	ASSERT_EQUAL(203,b_dynamic(6));
	ASSERT_EQUAL(1382958545,b_dynamic(15));
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
    s.push_back(CUTE(factorialTest));
    s.push_back(CUTE(calcChangeTest));
    s.push_back(CUTE(calcSumArrayTest));
    s.push_back(CUTE(partitioningTest));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
