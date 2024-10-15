#include <iostream>
#include <vector>
using namespace std;

class WorstFitAllocator {
private:
    vector<int> memoryBlocks; // Available memory blocks
    vector<int> allocatedBlocks; // Allocation results for processes

public:
    // Constructor to initialize memory blocks
    WorstFitAllocator(vector<int> blocks) {
        memoryBlocks = blocks;
        allocatedBlocks.resize(blocks.size(), -1); // Initialize all allocations as -1 (unallocated)
    }

    // Function to allocate memory to processes using Worst-Fit algorithm
    void allocateMemory(vector<int> processSizes) {
        for (int i = 0; i < processSizes.size(); i++) {
            int worstIndex = -1;
            int maxRemaining = -1;

            // Try to find the worst (largest) memory block that fits the process
            for (int j = 0; j < memoryBlocks.size(); j++) {
                if (memoryBlocks[j] >= processSizes[i] && memoryBlocks[j] > maxRemaining) {
                    maxRemaining = memoryBlocks[j];
                    worstIndex = j;
                }
            }

            // If a suitable block is found, allocate it
            if (worstIndex != -1) {
                memoryBlocks[worstIndex] -= processSizes[i];
                allocatedBlocks[i] = worstIndex; // Record which block was used
            } else {
                // If no suitable memory block is found
                cout << "Process " << i + 1 << " with size " << processSizes[i] << " could not be allocated memory.\n";
            }
        }
    }

    // Function to display allocation results
    void displayAllocation() {
        cout << "\nAllocation Results:\n";
        for (int i = 0; i < allocatedBlocks.size(); i++) {
            if (allocatedBlocks[i] != -1) {
                cout << "Process " << i + 1 << " allocated to memory block " << allocatedBlocks[i] + 1 << "\n";
            }
        }
    }

    // Function to display the remaining memory blocks after allocation
    void displayRemainingMemory() {
        cout << "\nRemaining Memory in Blocks:\n";
        for (int i = 0; i < memoryBlocks.size(); i++) {
            cout << "Block " << i + 1 << ": " << memoryBlocks[i] << " KB remaining\n";
        }
    }
};

int main() {
    // Memory blocks (in KB)
    vector<int> memoryBlocks = {100, 500, 200, 300, 600};

    // Process sizes (in KB)
    vector<int> processSizes = {212, 417, 112, 426};

    // Initialize the Worst-Fit memory allocator
    WorstFitAllocator allocator(memoryBlocks);

    // Allocate memory to processes
    allocator.allocateMemory(processSizes);

    // Display the allocation results
    allocator.displayAllocation();

    // Display remaining memory in blocks after allocation
    allocator.displayRemainingMemory();

    return 0;
}