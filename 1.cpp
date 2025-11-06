#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char message[], int shift) {
    for(int i = 0; message[i] != '\0'; i++) {
        if(isalpha(message[i])) {
            if(isupper(message[i])) {
                message[i] = ((message[i] - 'A' + shift) % 26) + 'A';
            } else {
                message[i] = ((message[i] - 'a' + shift) % 26) + 'a';
            }
        }
    }
}

void decrypt(char message[], int shift) {
    encrypt(message, 26 - shift);
}

int main() {
    char message[100];
    int shift;

    printf("=== COVERT COMMUNICATION SYSTEM ===\n\n");

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);

    shift = shift % 26;
    if(shift < 0) shift += 26;

    printf("\n");
    printf("Original Message: %s\n", message);

    encrypt(message, shift);
    printf("Encrypted Message: %s\n", message);
    printf("(Safe for transmission - interceptors see gibberish)\n\n");

    decrypt(message, shift);
    printf("Decrypted Message: %s\n", message);
    printf("(Original message recovered by operative with key)\n");

    return 0;
}
