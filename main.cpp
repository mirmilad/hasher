#include "iostream"
#include "hasher.h"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2)
		cout << "usage: hasher INPUT" << endl;

	char hash[GENERIC_HASH_SIZE * 2 + 1];
	calculateGenericHash(argv[1], hash);
	
	cout << "Calculated Hash(HEX String): " << hash << endl;
	return 0;
}
