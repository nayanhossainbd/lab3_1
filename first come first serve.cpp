//Implementation of First-Come, First-Served (FCFS) SchedulingDate: April 18, 2026
//Subject: Operating Systems LabTopic: Process Scheduling Algorithms
//1. ObjectiveTo implement the First-Come, First-Served (FCFS) scheduling algorithm in C++ to calculate and display the Waiting Time (WT) and Turnaround Time (TAT) for a given set of processes with specific arrival and burst times.
//2. TheoryFCFS is a non-preemptive scheduling algorithm where the process that requests the CPU first is allocated the CPU first. 
  //It is managed with a FIFO (First-In, First-Out) queue.Arrival Time (AT): The time at which the process arrives in the ready queue.
  //Burst Time (BT): The time required by the process for CPU execution.Completion Time (CT): The time at which the process finishes its execution.Turnaround Time (TAT): The total time spent by the process in the system.$$TAT = CT - AT$$
  //Waiting Time (WT): The time the process spent waiting in the ready queue.$$WT = TAT - BT$$
//3. Algorithm
  //Input the number of processes.
  //For each process, input its Arrival Time and Burst Time.
  //Sort the processes based on their Arrival Time (essential if inputs are not chronological).
  //Calculate Completion Time for each process:For the first process: $CT = AT + BT$.
    //For subsequent processes: If $AT > CT_{previous}$, then $CT = AT + BT$; 
      //else $CT = CT_{previous} + BT$.Calculate $TAT = CT - AT$ for all processes.
  //Calculate $WT = TAT - BT$ for all processes.
  //Calculate the average TAT and average WT.
//4. Implementation (C++)C++ //
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> proc[i].arrivalTime >> proc[i].burstTime;
    }

    // Sort processes by Arrival Time
    sort(proc.begin(), proc.end(), compareArrival);

    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;

        currentTime = proc[i].completionTime;
        totalTAT += proc[i].turnaroundTime;
        totalWT += proc[i].waitingTime;
    }

    cout << "\n" << setfill('-') << setw(65) << "-" << endl;
    cout << setfill(' ') << setw(5) << "P_ID" << setw(10) << "AT" << setw(10) << "BT" 
         << setw(10) << "CT" << setw(10) << "TAT" << setw(10) << "WT" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(5) << proc[i].id << setw(10) << proc[i].arrivalTime << setw(10) << proc[i].burstTime 
             << setw(10) << proc[i].completionTime << setw(10) << proc[i].turnaroundTime << setw(10) << proc[i].waitingTime << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;

    return 0;
};

// 5. Sample Output
//  Enter the number of processes: 3
//  Enter Arrival Time and Burst Time for Process 1: 0 5
// Enter Arrival Time and Burst Time for Process 2: 1 3
//  Enter Arrival Time and Burst Time for Process 3: 2 8 //
  
