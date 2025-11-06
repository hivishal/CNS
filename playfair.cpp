#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void hillCipher(char message[], int key[][3], int keySize) {
    int len = strlen(message);
    int msgVector[MAX];
    int cipherVector[MAX];
    int k = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            msgVector[k++] = toupper(message[i]) - 'A';
        }
    }

    while (k % keySize != 0) {
        msgVector[k++] = 'X' - 'A';
    }

    printf("\nEncrypted Message: ");

    for (int i = 0; i < k; i += keySize) {
        for (int row = 0; row < keySize; row++) {
            cipherVector[i + row] = 0;
            for (int col = 0; col < keySize; col++) {
                cipherVector[i + row] += key[row][col] * msgVector[i + col];
            }
            cipherVector[i + row] = cipherVector[i + row] % 26;
            printf("%c", cipherVector[i + row] + 'A');
        }
    }
    printf("\n");
}

int main() {
    char message[MAX];
    int keySize;
    int key[3][3];

    printf("=== Hill Cipher Encryption ===\n\n");

    printf("Enter key matrix size (2 or 3): ");
    scanf("%d", &keySize);

    if (keySize < 2 || keySize > 3) {
        printf("Invalid size! Use 2 or 3.\n");
        return 1;
    }

    printf("\nEnter the %dx%d key matrix (row by row):\n", keySize, keySize);
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            printf("Key[%d][%d]: ", i, j);
            scanf("%d", &key[i][j]);
        }
    }

    while (getchar() != '\n');

    printf("\nEnter message to encrypt: ");
    fgets(message, MAX, stdin);
    message[strcspn(message, "\n")] = 0;

    hillCipher(message, key, keySize);

    return 0;
}
