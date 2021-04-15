#include <iostream>
#include <stdio.h>
#include <openssl/sha.h> // For sha1

using namespace std; 

int main() {

    unsigned char plainText[] = "compute sha1";
    unsigned char hashValue[20];

    SHA1(plainText,sizeof(plainText),hashValue);

    for (int i = 0; i < 20; i++) {
        printf("%02x",hashValue[i]);
    }
	printf("\n");

    char output[41];
    char *c_output = output;


    for (int i = 0; i < 20; i++, c_output += 2) {
        snprintf(c_output, 3, "%02x", hashValue[i]);
    }

    for (int i = 0; i < 40; i++) {
        //printf("%c",output[i]);
		if(output[i] == 48) {
			printf("%d\n",i);
		}
    }

	
	
    return 0;

}
