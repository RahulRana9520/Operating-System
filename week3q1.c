#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int id;        // process id
    int bt;        // burst time
    int at;        // arrival time
    int ct;        // completion time
    int tat;       // turnaround time
    int wt;        // waiting time
};

// Utility function to calculate averages
void printResults(struct Process procs[], int n, int gantt[], int gsize) {
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        procs[i].tat = procs[i].ct - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        totalWT += procs[i].wt;
        totalTAT += procs[i].tat;
    }

    // Print Gantt chart
    printf("Gantt Chart : ");
    for (int i = 0; i < gsize; i++) {
        printf("P%d ", gantt[i]);
    }
    printf("\n");

    printf("Average waiting time: %.2lf\n", totalWT / n);
    printf("Average turnaround time : %.2lf\n", totalTAT / n);
}

// First Come First Serve
int cmp_at(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->at - p2->at;
}

void FCFS(struct Process procs[], int n) {
    qsort(procs, n, sizeof(struct Process), cmp_at);

    int time = 0;
    int gantt[100], gsize = 0;

    for (int i = 0; i < n; i++) {
        if (time < procs[i].at)
            time = procs[i].at;
        time += procs[i].bt;
        procs[i].ct = time;
        gantt[gsize++] = procs[i].id;
    }

    printResults(procs, n, gantt, gsize);
}

// Shortest Job First Non-Preemptive
void SJF_NP(struct Process procs[], int n) {
    int time = 0, completed = 0;
    int gantt[100], gsize = 0;
    int done[100] = {0};

    while (completed < n) {
        int idx = -1, mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && procs[i].at <= time && procs[i].bt < mn) {
                mn = procs[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        time += procs[idx].bt;
        procs[idx].ct = time;
        done[idx] = 1;
        gantt[gsize++] = procs[idx].id;
        completed++;
    }
    printResults(procs, n, gantt, gsize);
}

// Shortest Job First Preemptive (SRTF)
void SJF_P(struct Process procs[], int n) {
    int completed = 0, time = 0;
    int gantt[1000], gsize = 0;
    int remBT[100], i;
    for (i = 0; i < n; i++) remBT[i] = procs[i].bt;

    while (completed < n) {
        int idx = -1, mn = INT_MAX;
        for (i = 0; i < n; i++) {
            if (procs[i].at <= time && remBT[i] > 0 && remBT[i] < mn) {
                mn = remBT[i];
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        remBT[idx]--;
        gantt[gsize++] = procs[idx].id;
        time++;
        if (remBT[idx] == 0) {
            procs[idx].ct = time;
            completed++;
        }
    }
    // compress Gantt chart (remove repeats)
    int compact[100], csize = 0;
    compact[csize++] = gantt[0];
    for (i = 1; i < gsize; i++) {
        if (gantt[i] != gantt[i - 1])
            compact[csize++] = gantt[i];
    }
    printResults(procs, n, compact, csize);
}

// Main
int main() {
    int n, i;
    printf("Number of processes : ");
    scanf("%d", &n);

    struct Process procs[100];

    printf("Burst time : ");
    for (i = 0; i < n; i++) {
        scanf("%d", &procs[i].bt);
        procs[i].id = i;
    }

    printf("Arrival time : ");
    for (i = 0; i < n; i++) {
        scanf("%d", &procs[i].at);
    }

    int choice;
    printf("\nChoose Scheduling Policy:\n");
    printf("1. FCFS\n2. SJF Non-Preemptive\n3. SJF Preemptive\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: FCFS(procs, n); break;
        case 2: SJF_NP(procs, n); break;
        case 3: SJF_P(procs, n); break;
        default: printf("Invalid choice!\n");
    }
    return 0;
}
