# 🍽️ Philosophers

**Philosophers** is a classical concurrency problem implementation developed in C as part of the 42 Network curriculum. The project simulates the dining philosophers problem to practice process synchronization, deadlock avoidance, and thread safety.

---

## 🎯 Project Objectives

- Simulate the Dining Philosophers problem using multithreading or multiprocessing  
- Manage forks (resources) shared by philosophers to avoid deadlocks  
- Implement synchronization using mutexes or semaphores  
- Enforce timing constraints (eating, sleeping, thinking)  
- Handle philosopher lifecycle and proper termination  

---

## 🛠️ Features

- Create one thread/process per philosopher  
- Control access to forks to prevent race conditions  
- Detect and prevent deadlock and starvation  
- Output philosopher status messages (taking forks, eating, sleeping, thinking, died) with timestamps  
- Configurable number of philosophers and timing parameters  

---

## 🛠️ Technologies

- C  
- POSIX threads (`pthread`) or processes (`fork`)  
- Mutexes or semaphores  
- Unix/Linux environment  

---

## 🧪 How to Compile and Run

```bash
# Clone repo and compile
git clone git@github.com:mouadsrk/Philosopher.git
cd Philosopher
make

# Run with arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
./philo 5 800 200 200 7
