
#include <stdio.h> 
#include <math.h> 
#include <string.h> 
 
// Function to calculate GCD (Greatest Common Divisor) 
int gcd(int a, int b) { 
    while (b != 0) { 
        int temp = b; 
        b = a % b; 
        a = temp; 
    } 
    return a; 
} 
 
// Function to calculate modular exponentiation: (base^exp) % mod 
long long modExp(long long base, long long exp, long long mod) { 
    long long result = 1; 
    base = base % mod; 
    while (exp > 0) { 
        if (exp % 2 == 1) 
            result = (result * base) % mod; 
        exp = exp >> 1; 
        base = (base * base) % mod; 
    } 
    return result; 
} 
 
// Function to find modular multiplicative inverse using Extended Euclidean 
Algorithm 
int modInverse(int e, int phi) { 
    for (int d = 1; d < phi; d++) { 
        if ((e * d) % phi == 1) 
            return d; 
    } 
    return -1; 
} 
 
// Function to encrypt message 
long long encrypt(int message, int e, int n) { 
    return modExp(message, e, n); 
} 
 
// Function to decrypt message 
long long decrypt(long long cipher, int d, int n) { 
    return modExp(cipher, d, n); 
} 
 
int main() { 
    // Step 1: Choose two prime numbers (p and q) 
    int p = 61;  // First prime number 
    int q = 53;  // Second prime number 
     
    printf("=== RSA ENCRYPTION/DECRYPTION DEMO ===\n\n"); 
    printf("Step 1: Choose two prime numbers\n"); 
    printf("p = %d, q = %d\n\n", p, q); 
     
    // Step 2: Calculate n = p * q (modulus for both keys) 
    int n = p * q; 
    printf("Step 2: Calculate n = p * q\n"); 
    printf("n = %d\n\n", n); 
     
    // Step 3: Calculate Euler's totient function: phi = (p-1) * (q-1) 
    int phi = (p - 1) * (q - 1); 
    printf("Step 3: Calculate phi (Euler's totient)\n"); 
    printf("phi = (p-1) * (q-1) = %d\n\n", phi); 
     
    // Step 4: Choose public exponent e (commonly 65537 or small prime) 
    // e must be: 1 < e < phi and gcd(e, phi) = 1 
    int e = 17;  // Public exponent 
    while (gcd(e, phi) != 1) { 
        e++; 
    } 
    printf("Step 4: Choose public exponent e\n"); 
    printf("e = %d (where gcd(e, phi) = 1)\n\n", e); 
     
    // Step 5: Calculate private exponent d (modular multiplicative inverse 
of e) 
    // d * e ≡ 1 (mod phi) 
    int d = modInverse(e, phi); 
    printf("Step 5: Calculate private exponent d\n"); 
    printf("d = %d (where d * e mod phi = 1)\n\n", d); 
     
    // Display Keys 
    printf("=== KEY GENERATION COMPLETE ===\n"); 
    printf("Public Key (e, n): (%d, %d)\n", e, n); 
    printf("Private Key (d, n): (%d, %d)\n\n", d, n); 
     
    // Step 6: User A sends message to User B 
    printf("=== MESSAGE TRANSMISSION ===\n"); 
    int message; 
    printf("User A: Enter a numeric message to send (0-%d): ", n-1); 
    scanf("%d", &message); 
     
    // Validate input 
    if (message < 0 || message >= n) { 
        printf("Error: Message must be between 0 and %d\n", n-1); 
        return 1; 
    } 
     
    // Step 7: User A encrypts message using User B's public key 
    long long ciphertext = encrypt(message, e, n); 
    printf("\n--- SENDER SIDE (User A) ---\n"); 
    printf("Original Message: %d\n", message); 
    printf("Encrypting using public key (%d, %d)...\n", e, n); 
printf("Encrypted Message (Ciphertext): %lld\n", ciphertext); 
// Step 8: User B receives and decrypts message using private key 
long long decrypted = decrypt(ciphertext, d, n); 
printf("\n--- RECEIVER SIDE (User B) ---\n"); 
printf("Received Ciphertext: %lld\n", ciphertext); 
printf("Decrypting using private key (%d, %d)...\n", d, n); 
printf("Decrypted Message: %lld\n", decrypted); 
// Verify 
printf("\n=== VERIFICATION ===\n"); 
if (message == decrypted) { 
printf("✓ Success! Message decrypted correctly.\n"); 
printf("Original: %d, Decrypted: %lld\n", message, decrypted); 
} else { 
printf("✗ Error in decryption!\n"); 
} 
return 0; 
} 
