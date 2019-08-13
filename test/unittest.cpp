#include "gtest/gtest.h"
#include "hasher.h"

namespace {

TEST(HEXString, Null_Check) {
	char hash[1];
	char* input = NULL;
	charArrayToHexString(input, 0, hash);
	EXPECT_EQ(hash[0], '\0');
}

TEST(HEXString, 00_Check) {
	char hex[3];
	const char* input = "\x00";
	charArrayToHexString(input, 1, hex);
	EXPECT_STREQ(hex, "00");
}

TEST(HEXString, FF_Check) {
	char hex[3];
	const char* input = "\xff";
	charArrayToHexString(input, 1, hex);
	EXPECT_STREQ(hex, "FF");
}

TEST(HEXString, F0_Check) {
	char hex[3];
	const char* input = "\xf0";
	charArrayToHexString(input, 1, hex);
	EXPECT_STREQ(hex, "F0");
}

TEST(HEXString, Test_1) {
	char hex[17];
	const char* input = "\x01\x23\x45\x67\x89\xab\xcd\xef";
	charArrayToHexString(input, 8, hex);
	EXPECT_STREQ(hex, "0123456789ABCDEF");
}

TEST(CalculateHash, Test_1) {
	const char* input = "";
	char hash[2 * GENERIC_HASH_SIZE + 1];
	calculateGenericHash(input, hash);
	EXPECT_STREQ(hash, "0E5751C026E543B2E8AB2EB06099DAA1D1E5DF47778F7787FAAB45CDF12FE3A8");
}

TEST(CalculateHash, Test_2) {
	const char* input = "Hello";
	char hash[2 * GENERIC_HASH_SIZE + 1];
	calculateGenericHash(input, hash);
	EXPECT_STREQ(hash, "8B7CA7D27D9FC55FA30ABFE515B3AFB24E3FE89FDD02E2AC92BCA2C96680642E");
}

TEST(CalculateHash, Test_3) {
	const char* input = "Adjust";
	char hash[2 * GENERIC_HASH_SIZE + 1];
	calculateGenericHash(input, hash);
	EXPECT_STREQ(hash, "B0D6F01506E00C2EFFDF1153C755469E89C61C79201A38F29FE145A458CF5480");
}

TEST(CalculateHash, Test_4) {
	const char* input = "Sample Input";
	char hash[2 * GENERIC_HASH_SIZE + 1];
	calculateGenericHash(input, hash);
	EXPECT_STREQ(hash, "143CF31BC9D2421DEB856E0C3AC0E865FF475F7DB9436A7E044C74B5E3A7C90E");
}

TEST(CalculateHash, Test_5) {
	const char* input = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Dolor sed viverra ipsum nunc aliquet bibendum enim. In massa tempor nec feugiat. Nunc aliquet bibendum enim facilisis gravida. Nisl nunc mi ipsum faucibus vitae aliquet nec ullamcorper. Amet luctus venenatis lectus magna fringilla. Volutpat maecenas volutpat blandit aliquam etiam erat velit scelerisque in. Egestas egestas fringilla phasellus faucibus scelerisque eleifend. Sagittis orci a scelerisque purus semper eget duis. Nulla pharetra diam sit amet nisl suscipit. Sed adipiscing diam donec adipiscing tristique risus nec feugiat in. Fusce ut placerat orci nulla. Pharetra vel turpis nunc eget lorem dolor. Tristique senectus et netus et malesuada.";
	char hash[2 * GENERIC_HASH_SIZE + 1];
	calculateGenericHash(input, hash);
	EXPECT_STREQ(hash, "DF9C695339691778641C7FFA733CD55B5ABEC5AF655DA50D1D086CEF16E4BE0C");
}

}

//int main(int argc, char **argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
