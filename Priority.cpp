//Priority CPU Job Scheduling Implementation

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int pID;
    int arrivalTime;
    int burstTime;
    int priority;       // The priority of the process (lower value means higher priority)
    int completionTime;
    int waitingTime;
    int turnAroundTime;

    // Constructor
    Process(int pID, int arrivalTime, int burstTime, int priority) {
        this->pID = pID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->completionTime = 0;
        this->waitingTime = 0;
        this->turnAroundTime = 0;
    }

    // Display process details
    void display() const {
        cout << "Process ID: " << pID << ", Arrival Time: " << arrivalTime
             << ", Burst Time: " << burstTime << ", Priority: " << priority
             << ", Completion Time: " << completionTime << ", Waiting Time: " << waitingTime
             << ", Turnaround Time: " << turnAroundTime << endl;
    }
};

// Comparator to sort processes by priority first, then arrival time
bool comparePriority(const Process &a, const Process &b) {
    if (a.priority == b.priority) {
        return a.arrivalTime < b.arrivalTime;  // If priority is same, use arrival time (FCFS)
    }
    return a.priority < b.priority;  // Lower priority number means higher priority
}

int main() {
    int n;
    cout << "Enter the Number of Processes for Priority Scheduling: ";
    cin >> n;

    vector<Process> processes;

    // Input processes
    for (int i = 0; i < n; i++) {
        int pID, arrivalTime, burstTime, priority;
        cout << "Enter pID: ";
        cin >> pID;
        cout << "Enter Arrival Time: ";
        cin >> arrivalTime;
        cout << "Enter Burst Time: ";
        cin >> burstTime;
        cout << "Enter Priority (Lower value means higher priority): ";
        cin >> priority;

        processes.push_back(Process(pID, arrivalTime, burstTime, priority));
    }

    // Sort processes by priority and arrival time
    sort(processes.begin(), processes.end(), comparePriority);

    int currentTime = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Non-preemptive Priority Scheduling
    for (int i = 0; i < n; i++) {
        // Calculate when the CPU will be available for the current process
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate completion, turnaround, and waiting times
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnAroundTime;

        currentTime += processes[i].burstTime;  // Update current time
    }

    // Display process information
    cout << "\nProcess Scheduling Results (Priority Non-Preemptive):\n";
    for (const auto &p : processes) {
        p.display();
    }

    // Calculate and display average waiting time and turnaround time
    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnAroundTime = (double)totalTurnaroundTime / n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnAroundTime << endl;

    return 0;
}
