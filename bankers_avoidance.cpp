#include <iostream>
#include <vector>
using namespace std;

class BankersAlgorithm {
private:
    int numProcesses;                // Number of processes
    int numResources;                // Number of resource types
    vector<vector<int>> max;         // Max demand of each process
    vector<vector<int>> allocation;  // Resources allocated to each process
    vector<vector<int>> need;        // Remaining need of each process
    vector<int> available;           // Available instances of each resource

public:
    // Constructor to initialize the system
    BankersAlgorithm(int processes, int resources, vector<vector<int>> maxMatrix, vector<vector<int>> allocMatrix, vector<int> availVector)
        : numProcesses(processes), numResources(resources), max(maxMatrix), allocation(allocMatrix), available(availVector) {
        // Calculate the need matrix: Need[i][j] = Max[i][j] - Allocation[i][j]
        need.resize(numProcesses, vector<int>(numResources));
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }
    }

    // Function to check if the system is in a safe state
    bool isSafeState() {
        vector<int> work = available;  // Work vector represents the available resources during execution
        vector<bool> finish(numProcesses, false);  // Finish vector to indicate if a process has finished
        vector<int> safeSequence;  // To store the safe sequence of process execution

        // Keep track of the number of finished processes
        int finishedProcesses = 0;

        while (finishedProcesses < numProcesses) {
            bool processAllocated = false;

            // Try to find a process that can be allocated resources
            for (int i = 0; i < numProcesses; i++) {
                if (!finish[i]) {
                    bool canAllocate = true;

                    // Check if process `i`'s need can be satisfied with available resources
                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }

                    // If all the needs can be satisfied
                    if (canAllocate) {
                        // Assume process `i` finishes, and release its resources back to work
                        for (int j = 0; j < numResources; j++) {
                            work[j] += allocation[i][j];
                        }

                        // Mark the process as finished
                        finish[i] = true;
                        finishedProcesses++;
                        processAllocated = true;

                        // Add this process to the safe sequence
                        safeSequence.push_back(i);
                    }
                }
            }

            // If no process was allocated resources in this round, the system is in an unsafe state
            if (!processAllocated) {
                cout << "System is in an UNSAFE state.\n";
                return false;
            }
        }

        // If all processes finished, the system is in a safe state
        cout << "System is in a SAFE state.\nSafe sequence is: ";
        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;

        return true;
    }

    // Function to request resources for a process
    bool requestResources(int processId, vector<int> request) {
        // Check if request is less than or equal to the need of the process
        for (int i = 0; i < numResources; i++) {
            if (request[i] > need[processId][i]) {
                cout << "Error: Process " << processId << " has exceeded its maximum claim.\n";
                return false;
            }
        }

        // Check if request is less than or equal to available resources
        for (int i = 0; i < numResources; i++) {
            if (request[i] > available[i]) {
                cout << "Resources are not available for process " << processId << " request.\n";
                return false;
            }
        }

        // Pretend to allocate the resources (temporarily assume the request is granted)
        for (int i = 0; i < numResources; i++) {
            available[i] -= request[i];
            allocation[processId][i] += request[i];
            need[processId][i] -= request[i];
        }

        // Check if this leads to a safe state
        if (isSafeState()) {
            // If it's safe, the resources are officially allocated
            return true;
        } else {
            // If it's not safe, rollback the allocation
            for (int i = 0; i < numResources; i++) {
                available[i] += request[i];
                allocation[processId][i] -= request[i];
                need[processId][i] += request[i];
            }
            return false;
        }
    }
};

int main() {
    int numProcesses = 5;
    int numResources = 3;

    // Maximum demand of each process
    vector<vector<int>> maxMatrix = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to each process
    vector<vector<int>> allocMatrix = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Available resources
    vector<int> availVector = {3, 3, 2};

    // Initialize the Banker's Algorithm system
    BankersAlgorithm ba(numProcesses, numResources, maxMatrix, allocMatrix, availVector);

    // Check if the system is in a safe state
    ba.isSafeState();

    // Request resources for a process
    vector<int> request = {1, 0, 2};  // Example request
    int processId = 1;

    cout << "\nProcess " << processId << " is requesting resources: ";
    for (int i = 0; i < request.size(); i++) {
        cout << request[i] << " ";
    }
    cout << endl;

    if (ba.requestResources(processId, request)) {
        cout << "Resources have been allocated to process " << processId << ".\n";
    } else {
        cout << "Resources cannot be allocated to process " << processId << ".\n";
    }

    return 0;
}
