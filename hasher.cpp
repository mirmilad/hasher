#include "hasher.h"
#include <iostream>
#include <string.h>

#include <sodium.h>

#include <android/log.h>

using namespace std;

#define TAG "Hasher"

void log_d(const char* tag, const char* message) {
        __android_log_write(ANDROID_LOG_DEBUG, tag, message);
}

int calculateGenericHash(const char* input, char* output) {

        log_d(TAG, "try to calculate hash");
        if (sodium_init() < 0) {
                // Can not init library
                log_d(TAG, "can not init libsodium");
                return -1;
        }

        unsigned char hash[GENERIC_HASH_SIZE];

        log_d(TAG, "calculating ...");
        crypto_generichash(hash, sizeof hash,
                   (unsigned char*)input, strlen(input),
                   NULL, 0);


        log_d(TAG, "converting hash to hexstring");
        charArrayToHexString((char*)hash, GENERIC_HASH_SIZE, output);

        return 0;
}

void charArrayToHexString(const char* input, int inputLen, char* out) {
        if(input == NULL) {
		sprintf(out, "");
		return;
	}
	int i;
        for (i = 0; i < inputLen; i++)
        {
                sprintf(out + 2 * i, "%02X", (unsigned char)input[i]);
        }
}


