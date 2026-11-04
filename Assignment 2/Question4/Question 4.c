/**
 *Programmer: Siraj Mughal
 *Class: BDS-1A
 *Roll No: 26K-2464
 *Program: Bakery Records
 *Date:26/Oct/2026
 *Desc: Takes a bakery's festival orders gives out highest, average, and best sales and chart with daily sales
 */
#include <stdio.h>

// keeps asking for valid days
int getValidDays() {
    int days;
    int ok; // 1 when the input is ok

    ok = 0;

    while (ok == 0) {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days >= 1 && days <= 7) {
            ok = 1;
        } else {
            printf("Invalid number of days.\n");
        }
    }

    return days;
}

// takes the orders of one day shows its figures and gives back the total
float calculateDailySales(int dayNumber) {
    int n; // number of orders
    int i; // i is the order we are on
    float amount; // one order amount
    float total = 0; // total for the day
    float max = 0; // highest order of the day
    int ok; // 1 when the input is ok

    ok = 0;

    while (ok == 0) {
        printf("\nDay %d - Number of orders: ", dayNumber);
        scanf("%d", &n);
        if (n >= 1) {
            ok = 1;
        } else {
            printf("There must be at least one order.\n");
        }
    }

    for (i = 1; i <= n; i++) {
        ok = 0;
        while (ok == 0) {
            printf("Order %d amount: ", i);
            scanf("%f", &amount);
            if (amount > 0) {
                ok = 1;
            } else {
                printf("Amount must be greater than zero.\n");
            }
        }

        total = total + amount;
        if (amount > max) {
            max = amount;
        }
    }

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", total / n);
    printf("Highest order: Rs. %.2f\n", max);

    return total;
}

// the highest sales
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int i; // i is the day
    int best = 0; // best day so far

    for (i = 1; i < numberOfDays; i++) {
        // only a bigger value replaces it
        if (dailySales[i] > dailySales[best]) {
            best = i;
        }
    }
    return best + 1;
}

// one * for every full Rs. 100
void displayBarChart(float dailySales[], int numberOfDays) {
    int i; // i is the day
    int j; // j counts the stars
    int stars; // stars for this day

    for (i = 0; i < numberOfDays; i++) {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    float dailySales[7]; // sales of each day
    float festivalTotal = 0;
    int days; // festival days
    int i; // i is the day
    int best; // best day

    days = getValidDays();

    for (i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal = festivalTotal + dailySales[i];
    }

    best = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", best);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[best - 1]);

    printf("\n===== DAILY SALES BAR CHART =====\n");
    displayBarChart(dailySales, days);

    return 0;
}
