#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
 
// Function to encrypt plaintext using Vigenère cipher 
void encrypt(char plaintext[], char key[], char ciphertext[]) { 
    int textLen = strlen(plaintext); 
    int keyLen = strlen(key); 
     
    for (int i = 0; i < textLen; i++) { 
        // Get corresponding key character (repeat key cyclically) 
        char keyChar = key[i % keyLen]; 
         
        // Shift plaintext character by key character value 
        // Formula: C = (P + K) mod 26 
        ciphertext[i] = ((plaintext[i] - 'a') + (keyChar - 'a')) % 26 + 
'a'; 
    } 
    ciphertext[textLen] = '\0'; // Null terminate the string 
} 
 
// Function to decrypt ciphertext using Vigenère cipher 
void decrypt(char ciphertext[], char key[], char plaintext[]) { 
    int textLen = strlen(ciphertext); 
    int keyLen = strlen(key); 
     
    for (int i = 0; i < textLen; i++) { 
        // Get corresponding key character (repeat key cyclically) 
        char keyChar = key[i % keyLen]; 
         
        // Reverse the shift to get original character 
        // Formula: P = (C - K + 26) mod 26 
        plaintext[i] = ((ciphertext[i] - 'a') - (keyChar - 'a') + 26) % 26 
+ 'a'; 
    } 
    plaintext[textLen] = '\0'; // Null terminate the string 
} 
 
int main() { 
    // Input plaintext and key 
    char plaintext[] = "wearediscoveredsaveyourself"; 
    char key[] = "deceptive"; 
     
    char ciphertext[100];  // To store encrypted text 
    char decrypted[100];   // To store decrypted text 
     
    printf("Plaintext:  %s\n", plaintext); 
    printf("Key:        %s\n", key); 
     
    // Encrypt the message 
    encrypt(plaintext, key, ciphertext); 
    printf("\nEncrypted:  %s\n", ciphertext); 
     
    // Decrypt the message 
    decrypt(ciphertext, key, decrypted); 
    printf("Decrypted:  %s\n", decrypted); 
     
    return 0; 
} 
