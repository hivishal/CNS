#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
 
char matrix[5][5]; 
 
// Create 5x5 matrix from key (I and J share one spot) 
void createMatrix(char *key) { 
    int used[26] = {0}, k = 0; 
    used['J'-'A'] = 1;  // J treated as I 
     
    // Add key letters first 
    for (int i = 0; key[i]; i++) { 
        char ch = toupper(key[i]); 
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch) && !used[ch-'A']) { 
            matrix[k/5][k%5] = ch; 
            used[ch-'A'] = 1; 
            k++; 
        } 
    } 
     
    // Add remaining letters 
    for (int i = 0; i < 26; i++) { 
        if (!used[i]) { 
            matrix[k/5][k%5] = 'A' + i; 
            k++; 
        } 
    } 
} 
 
// Find letter position in matrix 
void findPos(char ch, int *r, int *c) { 
    if (ch == 'J') ch = 'I'; 
    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < 5; j++) 
            if (matrix[i][j] == ch) { *r = i; *c = j; return; } 
} 
 
// Encrypt/decrypt a pair of letters 
void processPair(char a, char b, char *out1, char *out2, int mode) { 
    int r1, c1, r2, c2; 
    findPos(a, &r1, &c1); 
    findPos(b, &r2, &c2); 
     
    if (r1 == r2) {  // Same row - shift horizontally 
        *out1 = matrix[r1][(c1 + mode + 5) % 5]; 
        *out2 = matrix[r2][(c2 + mode + 5) % 5]; 
    } else if (c1 == c2) {  // Same column - shift vertically 
        *out1 = matrix[(r1 + mode + 5) % 5][c1]; 
        *out2 = matrix[(r2 + mode + 5) % 5][c2]; 
    } else {  // Rectangle - swap columns 
        *out1 = matrix[r1][c2]; 
        *out2 = matrix[r2][c1]; 
    } 
} 
 
int main() { 
    char key[100], msg[100], clean[200] = ""; 
     
    printf("Enter key: "); 
    fgets(key, sizeof(key), stdin); 
    key[strcspn(key, "\n")] = 0;  // Remove newline 
     
    printf("Enter message: "); 
    fgets(msg, sizeof(msg), stdin); 
    msg[strcspn(msg, "\n")] = 0;  // Remove newline 
     
    // Build matrix 
    createMatrix(key); 
     
    // Clean message: uppercase, replace J with I 
    for (int i = 0; msg[i]; i++) { 
        char ch = toupper(msg[i]); 
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch)) { 
            int len = strlen(clean); 
            // Add X between duplicate letters 
            if (len > 0 && clean[len-1] == ch) strcat(clean, "X"); 
            strncat(clean, &ch, 1); 
        } 
    } 
    if (strlen(clean) % 2) strcat(clean, "X");  // Pad if odd length 
     
    // Encrypt 
    char encrypted[200] = ""; 
    for (int i = 0; i < strlen(clean); i += 2) { 
        char c1, c2; 
        processPair(clean[i], clean[i+1], &c1, &c2, 1);  // mode=1 for 
encrypt 
        strncat(encrypted, &c1, 1); 
        strncat(encrypted, &c2, 1); 
    } 
     
    // Decrypt 
    char decrypted[200] = ""; 
    for (int i = 0; i < strlen(encrypted); i += 2) { 
        char c1, c2; 
        processPair(encrypted[i], encrypted[i+1], &c1, &c2, -1);  // 
mode=-1 for decrypt 
        strncat(decrypted, &c1, 1); 
        strncat(decrypted, &c2, 1); 
    } 
     
    printf("\nOriginal: %s\n", clean); 
    printf("Encrypted: %s\n", encrypted); 
    printf("Decrypted: %s\n", decrypted); 
     
    return 0; 
} 
