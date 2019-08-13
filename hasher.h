#ifndef _HASHER_H_
#define _HASHER_H_

#include <sodium.h>

#define GENERIC_HASH_SIZE crypto_generichash_BYTES



void log_d(const char* tag, const char* message);

int calculateGenericHash(const char* input, char* output);

void charArrayToHexString(const char* input, int inputLen, char* out);


#endif

