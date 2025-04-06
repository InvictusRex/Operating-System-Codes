# Operating-System-Codes

This repository contains C programs for Operating Systems implementations, including CPU scheduling, memory allocation, process synchronization, and file handling.

---

## 📁 Repository Structure & Descriptions

### 🧠 CPU Scheduling

Algorithms to decide the order in which processes are executed by the CPU.

- **FCFS_no_arrival_time.c** – First Come First Serve algorithm without considering arrival time.
- **FCFS_with_arrival_time.c** – FCFS scheduling with processes arriving at different times.
- **Priority_non_preemptive.c** – Non-preemptive priority scheduling where higher priority processes are chosen first.
- **Priority_preemptive.c** – Preemptive version where a higher priority process can interrupt a lower one.
- **Round_robin.c** – Round Robin scheduling with time slicing for fairness.
- **SJF_non_preemptive.c** – Shortest Job First algorithm (non-preemptive), selecting shortest burst time.
- **SJF_preemptive.c** – Preemptive SJF, also known as Shortest Remaining Time First.

---

### 📦 Contiguous Memory Allocation

Demonstrates strategies to allocate memory blocks in contiguous fashion.

- **Best_Fit.c** – Allocates the smallest block that fits the request.
- **First_Fit.c** – Allocates the first available block that is large enough.
- **Worst_Fit.c** – Allocates the largest block to reduce leftover space.

---

### 🔐 General Problems

Common synchronization and concurrency control problems.

- **Dining_Philosopher_monitors.c** – Dining Philosophers solution using monitor-style logic.
- **Dining_Philosopher_semaphores.c** – Uses semaphores to avoid deadlock in the Dining Philosophers problem.
- **File_Locking.c** – Demonstrates file locking using `fcntl()` for concurrent file access.
- **Reader_Writer.c** – Classic Reader-Writer synchronization problem implementation using semaphores.

---

### 📄 Page Replacement Algorithms

Algorithms used in virtual memory to manage page frames.

- **FIFO.c** – First-In-First-Out strategy for replacing pages.
- **LRU.c** – Least Recently Used strategy using timestamps.
- **Optimal.c** – Replaces the page that won't be used for the longest period (ideal but impractical in real life).

---

### 🔄 Producer & Consumer

Synchronization problems involving bounded buffer and multiple producers/consumers.

- **Producer_Consumer_circular_buffer.c** – Uses a circular buffer to efficiently handle producer-consumer synchronization.
- **Producer_Consumer_multiple.c** – Supports multiple producers and consumers using semaphores.
- **Producer_Consumer_single.c** – Basic implementation with one producer and one consumer.

---

## 🛠️ Compilation & Execution

Use GCC to compile the programs:

```bash
gcc filename.c -o outputname.o
./outputname.o
```
