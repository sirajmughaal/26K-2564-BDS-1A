/**
 *Programmer: Siraj Mughal
 *Class: BDS-1A
 *Roll no: 26K-2564
 *Program: Amicable pair
 *Date:26/oct/2026
 *Desc: Take a number n and printf all the amicable that are under it 
 example: 300 would give you(220,2840
 */ 









#include <stdio.h>

// returns the sum of the proper divisors of x
int sumDivisors(int x) {
    int i;          // i is the number being tested as a divisor
    int sum = 0;    // running sum of divisors

    // no proper divisor is bigger than x / 2
    for (i = 1; i <= x / 2; i++) {
        if (x % i == 0) {
            sum = sum + i;
        }
    }
    return sum;
}

int main() {
    int n;          // upper limit
    int a;          // first number of the pair
    int b;          // sum of divisors of a, second number of the pair
    int pairs = 0;  // number of pairs found
    int ok;         // 1 when the input is valid

    ok = 0;

    while (ok == 0) {
        printf("Enter n: ");
        scanf("%d", &n);
        if (n >= 1) {
            ok = 1;
        }
    }

    printf("Amicable pairs up to %d:\n", n);

    for (a = 2; a <= n; a++) {
        b = sumDivisors(a);
        // b > a makes sure the pair is shown once, smaller first and also skips numbers like 6 and 28 where b == a
        if (b > a && b <= n && sumDivisors(b) == a) {
            printf("(%d, %d)\n", a, b);
            pairs++;
        }
    }

    if (pairs == 0) {
        printf("No amicable pairs found up to %d.\n", n);
    } else {
        printf("Total pairs: %d\n", pairs);
    }

    return 0;
}
