/**
 *Programmer:Siraj Mughal
 *Class: BDS-1A
 *Roll no: 26K-2564
 *Program: Cinema Hall Seat Booking Management System
 *Date:25 Oct 2026
 *Desc: Cinema that takes the rows and columns from user and declares which seat is available starting row/2
 */







#include <stdio.h>

int main() {
    int seats[50][50];   // seating plan, 0 = free, 1 = booked
    int rows, cols;      // number of rows and seats per row
    int i, j;            // i is the row index, j is the seat index
    int k;               // size of the group
    int ok;              // 1 when the input is valid
    int mid;             // middle row
    int d;               // distance from the middle row
    int s;               // 0 means check the row above the middle, 1 means the row below
    int r;               // row currently being searched
    int run;             // free seats seen in a row without a break
    int rowFree;         // free seats in the current row
    int total = 0;       // total free seats in the hall
    int found = 0;       // 1 once a block is found
    int foundRow = -1;   // row of the block
    int start = -1;      // first seat of the block

    // input rows and seats
    for (ok = 0; ok == 0; ) {
        printf("Enter number of rows (1-50): ");
        scanf("%d", &rows);
        if (rows >= 1 && rows <= 50) {
            ok = 1;
        }
    }

    for (ok = 0; ok == 0; ) {
        printf("Enter number of seats per row (1-50): ");
        scanf("%d", &cols);
        if (cols >= 1 && cols <= 50) {
            ok = 1;
        }
    }

    // input seat status
    printf("Enter seat status (0 = available, 1 = booked):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            for (ok = 0; ok == 0; ) {
                scanf("%d", &seats[i][j]);
                if (seats[i][j] == 0 || seats[i][j] == 1) {
                    ok = 1;
                } else {
                    printf("Invalid, enter 0 or 1: ");
                }
            }
        }
    }

    // display seating plan
    printf("\n    ");
    for (j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (i = 0; i < rows; i++) {
        printf("R%-2d ", i);
        for (j = 0; j < cols; j++) {
            if (seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }

    // free seats in each row and in total
    printf("\nFree seats per row: ");
    for (i = 0; i < rows; i++) {
        rowFree = 0;
        for (j = 0; j < cols; j++) {
            if (seats[i][j] == 0) {
                rowFree++;
            }
        }
        printf("%d ", rowFree);
        total = total + rowFree;
    }
    printf("  Total free: %d\n", total);

    // input group size and validate it
    for (ok = 0; ok == 0; ) {
        printf("\nEnter number of customers (1 to %d): ", cols);
        scanf("%d", &k);
        if (k >= 1 && k <= cols) {
            ok = 1;
        } else {
            printf("Invalid size\n");
        }
    }

    // search from the middle row outwards
    mid = rows / 2;
    for (d = 0; d <= rows && found == 0; d++) {
        for (s = 0; s < 2 && found == 0; s++) {
            if (s == 0) {
                r = mid - d;     // smaller row number first
            } else {
                if (d == 0) {
                    continue;    // middle row was already checked
                }
                r = mid + d;
            }
            if (r < 0 || r >= rows) {
                continue;        // row does not exist
            }

            run = 0;
            for (j = 0; j < cols && found == 0; j++) {
                if (seats[r][j] == 0) {
                    run++;
                    if (run == k) {
                        found = 1;
                        foundRow = r;
                        start = j - k + 1;
                    }
                } else {
                    run = 0;     // booked seat, start counting again
                }
            }
        }
    }

    if (found == 1) {
        // book the seats
        for (j = start; j < start + k; j++) {
            seats[foundRow][j] = 1;
        }
        total = total - k;

        printf("\nGroup of %d seated in Row %d Seats %d to %d\n", k, foundRow, start, start + k - 1);

        // display updated plan
        printf("\n    ");
        for (j = 0; j < cols; j++) {
            printf("%d ", j);
        }
        printf("\n");
        for (i = 0; i < rows; i++) {
            printf("R%-2d ", i);
            for (j = 0; j < cols; j++) {
                if (seats[i][j] == 0) {
                    printf("_ ");
                } else {
                    printf("X ");
                }
            }
            printf("\n");
        }
        printf("\nRemaining available seats: %d\n", total);
    } else {
        printf("\n no row has %d consecutive available seats\n", k);
    }

    return 0;
}
