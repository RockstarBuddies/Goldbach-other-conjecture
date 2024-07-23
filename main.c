#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Function to create a sieve of primes up to a certain limit
void sieve_of_eratosthenes(bool *is_prime, int limit) {
    for (int i = 2; i <= limit; ++i) {
        is_prime[i] = true;
    }
    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }
}

// Function to check if a number is prime
bool is_prime(int num, bool *is_prime) {
    return is_prime[num];
}

// Function to check if an odd composite can be written as the sum of a prime and twice a square
bool check_goldbach(int num, bool *is_prime) {
    for (int p = 2; p < num; ++p) {
        if (is_prime[p]) {
            int remainder = num - p;
            if (remainder % 2 == 0) {
                int n = remainder / 2;
                int sqrt_n = (int)sqrt(n);
                if (sqrt_n * sqrt_n == n) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int limit = 10000;
    bool *is_prime = (bool*)malloc((limit + 1) * sizeof(bool));
    sieve_of_eratosthenes(is_prime, limit);

    int smallest_odd_composite = 0;
    for (int i = 9; i <= limit; i += 2) {
        if (!is_prime[i]) {
            if (!check_goldbach(i, is_prime)) {
                smallest_odd_composite = i;
                break;
            }
        }
    }

    printf("The smallest odd composite number that cannot be written as the sum of a prime and twice a square is %d\n", smallest_odd_composite);

    free(is_prime);
    return 0;
}
