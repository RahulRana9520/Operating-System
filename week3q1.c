#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;        // process id
    int bt;        // burst time
    int at;        // arrival time
    int ct;        // completion time
    int tat;       // turnaround time
    int wt;        // waiting time
};

// Utility function to calculate averages
void printResults(vector<Process> &procs, vector<int> &gantt) {
    int n = procs.size();
    double totalWT = 0, totalTAT = 0;

    for (auto &p : procs) {
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
        totalWT += p.wt;
        totalTAT += p.tat;
    }

    // Print Gantt chart
    cout << "Gantt Chart : ";
    for (int pid : gantt) {
        cout << "P" << pid << " ";
    }
    cout << "\n";

    cout << "Average waiting time: " << totalWT / n << "\n";
    cout << "Average turnaround time : " << totalTAT / n << "\n";
}

// First Come First Serve
void FCFS(vector<Process> procs) {
    sort(procs.begin(), procs.end(), [](auto &a, auto &b) {
        return a.at < b.at;
    });

    int time = 0;
    vector<int> gantt;

    for (auto &p : procs) {
        time = max(time, p.at);  // wait if CPU idle
        time += p.bt;
        p.ct = time;
        gantt.push_back(p.id);
    }

    printResults(procs, gantt);
}

// Shortest Job First Non-Preemptive
void SJF_NP(vector<Process> procs) {
    int n = procs.size();
    int time = 0, completed = 0;
    vector<int> gantt;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1;
        int mn = INT_MAX;

        // pick available shortest job
        for (int i = 0; i < n; i++) {
            if (!done[i] && procs[i].at <= time && procs[i].bt < mn) {
                mn = procs[i].bt;
                idx = i;
            }
        }

        if (idx == -1) { // no process yet
            time++;
            continue;
        }

        time += procs[idx].bt;
        procs[idx].ct = time;
        done[idx] = true;
        gantt.push_back(procs[idx].id);
        completed++;
    }

    printResults(procs, gantt);
}

// Shortest Job First Preemptive (SRTF)
void SJF_P(vector<Process> procs) {
    int n = procs.size();
    int completed = 0, time = 0;
    vector<int> gantt;
    vector<int> remBT(n);

    for (int i = 0; i < n; i++) remBT[i] = procs[i].bt;

    while (completed < n) {
        int idx = -1;
        int mn = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (procs[i].at <= time && remBT[i] > 0 && remBT[i] < mn) {
                mn = remBT[i];
                idx = i;
            }
        }

        if (idx == -1) { // CPU idle
            time++;
            continue;
        }

        // Execute 1 unit
        remBT[idx]--;
        gantt.push_back(procs[idx].id);
        time++;

        if (remBT[idx] == 0) {
            procs[idx].ct = time;
            completed++;
        }
    }

    // compress Gantt chart (remove repeats)
    vector<int> compact;
    compact.push_back(gantt[0]);
    for (int i = 1; i < gantt.size(); i++) {
        if (gantt[i] != gantt[i - 1])
            compact.push_back(gantt[i]);
    }

    printResults(procs, compact);
}

// Main
int main() {
    int n;
    cout << "Number of processes : ";
    cin >> n;

    vector<Process> procs(n);

    cout << "Burst time : ";
    for (int i = 0; i < n; i++) {
        cin >> procs[i].bt;
        procs[i].id = i;
    }

    cout << "Arrival time : ";
    for (int i = 0; i < n; i++) {
        cin >> procs[i].at;
    }

    int choice;
    cout << "\nChoose Scheduling Policy:\n";
    cout << "1. FCFS\n2. SJF Non-Preemptive\n3. SJF Preemptive\n";
    cin >> choice;

    switch (choice) {
        case 1: FCFS(procs); break;
        case 2: SJF_NP(procs); break;
        case 3: SJF_P(procs); break;
        default: cout << "Invalid choice!\n";
    }
    return 0;
}
