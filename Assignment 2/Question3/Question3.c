/**
 *Programmer: Siraj Mughal
 *Class: BDS-1A
 *Roll No: 26K-2564
 *Program: Greenhouse sensor
 *Date:26/Oct/2026
 *Desc: Stores greenhouse temperature points at the sensor with the highest average and how it ran throughout
 */

#include <stdio.h>

// takes readings
void inputReadings(int t[][50], int sensors, int hours) {
    int i; // i is the sensor
    int j; // j is the hour

    for (i = 0; i < sensors; i++) {
        printf("Sensor %d (enter %d readings): ", i + 1, hours);
        for (j = 0; j < hours; j++) {
            scanf("%d", &t[i][j]);
        }
    }
}

//for one sensor
void analyzeSensor(int r[], int hours, int *total, float *avg, int *max, int *min,
                   int *critical, int *warning, int *streak) {
    int j; // j is the hour
    int cur = 0; // current run of readings at 35 or above

    *total = 0;
    *max = r[0];
    *min = r[0];
    *critical = 0;
    *warning = 0;
    *streak = 0;

    for (j = 0; j < hours; j++) {
        *total = *total + r[j];

        if (r[j] > *max) {
            *max = r[j];
        }
        if (r[j] < *min) {
            *min = r[j];
        }

        if (r[j] >= 40) {
            (*critical)++;
        } else if (r[j] >= 35) {
            (*warning)++;
        }

        if (r[j] >= 35) {
            cur++;
            if (cur > *streak) {
                *streak = cur;
            }
        } else {
            cur = 0; // below 35, so the streak is over
        }
    }

    *avg = (float)(*total) / hours;
}

// the highest average sensor
int highestAverage(int t[][50], int sensors, int hours, float *bestAvg) {
    int i; // i is the sensor
    int j; // j is the hour
    int sum; // sum for one sensor
    int best = 0; // best sensor so far
    float avg; // average for one sensor

    *bestAvg = -1000;
    for (i = 0; i < sensors; i++) {
        sum = 0;
        for (j = 0; j < hours; j++) {
            sum = sum + t[i][j];
        }
        avg = (float)sum / hours;
        if (avg > *bestAvg) {
            *bestAvg = avg;
            best = i;
        }
    }
    return best + 1;
}

int main() {
    int t[20][50]; // row = sensor, column = hour
    int sensors; // number of sensors
    int hours; // readings per sensor
    int i; // i is the sensor
    int total, max, min, critical, warning, streak;
    float avg;
    int ok; // 1 when the input is ok
    int best; // sensor with the best average
    float bestAvg; // its average

    ok = 0;

    while (ok == 0) {
        printf("Enter number of sensors (1-20): ");
        scanf("%d", &sensors);
        if (sensors >= 1 && sensors <= 20) {
            ok = 1;
        }
    }

    ok = 0;

    while (ok == 0) {
        printf("Enter number of hourly readings (1-50): ");
        scanf("%d", &hours);
        if (hours >= 1 && hours <= 50) {
            ok = 1;
        }
    }

    inputReadings(t, sensors, hours);

    printf("\n");
    for (i = 0; i < sensors; i++) {
        analyzeSensor(t[i], hours, &total, &avg, &max, &min, &critical, &warning, &streak);
        printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", i + 1, total, avg, max, min);
        printf("Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, streak);
    }

    best = highestAverage(t, sensors, hours, &bestAvg);
    printf("\nHighest average: Sensor %d (%.2f)\n", best, bestAvg);

    return 0;
}
