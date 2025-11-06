#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
 
// Function to encrypt plaintext using the cipher key 
void encrypt(char *text, char *key, char *result) { 
    int i; 
    for (i = 0; text[i] != '\0'; i++) { 
        if (isalpha(text[i])) { 
            // Convert to uppercase and map A-Z (0-25) to key position 
            char upper = toupper(text[i]); 
            result[i] = key[upper - 'A']; 
        } else { 
            // Keep spaces and other characters unchanged 
            result[i] = text[i]; 
        } 
    } 
    result[i] = '\0';  // Null terminate the string 
} 
 
// Function to decrypt ciphertext using the cipher key 
void decrypt(char *text, char *key, char *result) { 
    int i, j; 
    for (i = 0; text[i] != '\0'; i++) { 
        if (isalpha(text[i])) { 
            // Find position of cipher character in key 
            char upper = toupper(text[i]); 
            for (j = 0; j < 26; j++) { 
                if (key[j] == upper) { 
                    // Map back to original letter (A-Z) 
                    result[i] = 'A' + j; 
                    break; 
                } 
            } 
        } else { 
            // Keep spaces and other characters unchanged 
            result[i] = text[i]; 
        } 
    } 
    result[i] = '\0';  // Null terminate the string 
} 
 
int main() { 
    char plaintext[100]; 
    char key[27];  // 26 letters + null terminator 
    char ciphertext[100]; 
    char decrypted[100]; 
     
    // Get plaintext from user 
    printf("Enter the plaintext to encrypt: "); 
    fgets(plaintext, sizeof(plaintext), stdin); 
    // Remove newline character if present 
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
     
    // Get cipher key from user 
    printf("Enter the cipher key (26 unique letters for A-Z substitution): 
"); 
    fgets(key, sizeof(key), stdin); 
    // Remove newline character if present 
    key[strcspn(key, "\n")] = '\0'; 
     
    // Validate key length 
    if (strlen(key) != 26) { 
        printf("Error: Cipher key must be exactly 26 letters!\n"); 
        return 1; 
    } 
     
    // Convert key to uppercase 
    for (int i = 0; i < 26; i++) { 
        key[i] = toupper(key[i]); 
    } 
     
    printf("\n"); 
     
    // Encrypt the plaintext 
    encrypt(plaintext, key, ciphertext); 
    printf("Original Plaintext: %s\n", plaintext); 
    printf("Cipher Key:         %s\n", key); 
    printf("Encrypted:          %s\n\n", ciphertext); 
     
    // Decrypt the ciphertext 
    decrypt(ciphertext, key, decrypted); 
    printf("Decrypted:          %s\n", decrypted); 
     
    return 0; 
}
