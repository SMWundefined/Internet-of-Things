#include <Arduino.h>

#include "mbedtls/aes.h"
#include "mbedtls/pk.h"

#define AES_BLOCK_SIZE  16

// For 128 bit key, the key must be exactly 16 bytes
char * key = "abcdefghijklmnop";


void setup() {
  Serial.begin(115200);

  // The maximum length the library supports a single 16 byte block of data
  char *input = "Hello Lora World";
  unsigned char cipherText[AES_BLOCK_SIZE];

  mbedtls_aes_context aes;

  // Encrypting Data using AES
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)input, cipherText);
  mbedtls_aes_free(&aes);

  Serial.println();
  Serial.print("Encrypted Data: ");
  for (int i = 0; i < AES_BLOCK_SIZE; i++) {
    // Print each byte as a hexadecimal 
    // string with two characters padded
    // with a leading zero if needed
    Serial.printf("%02x", (int) cipherText[i]);
  }
  Serial.println();

  // Decrypting AES Data using ecb mode
/**
  char decryptedText[17];
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*) key, 128);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)cipherText, (unsigned char*)decryptedText);
  mbedtls_aes_free(&aes);
  Serial.print("Decoded Data: ");
  Serial.print(decryptedText);
  Serial.println(); 
  **/
}

void loop() {}
