# Dining Philosophers Problem

This project is a multithreaded simulation of the dining philosophers problem implemented in C. It utilizes the pthread library for threading and mutexes.

## Project Structure

```
├── includes/
│   └── philo.h
├── Makefile
└── src/
    ├── actions.c
    ├── exit.c
    ├── init.c
    ├── main.c
    └── routine.c
```

## How to Run

To compile the project, run the following command in the terminal:

```
make
```

To run the program, use the following command:

```
./philo num_philosophers time_to_die time_to_eat time_to_sleep [max_times_to_eat]
```

Where:

- `num_philosophers`: Number of philosophers and also the number of forks.
- `time_to_die`: Time in milliseconds a philosopher waits before dying.
- `time_to_eat`: Time in milliseconds a philosopher takes to eat.
- `time_to_sleep`: Time in milliseconds a philosopher sleeps.
- `max_times_to_eat` (optional): Maximum number of times each philosopher must eat.

## Code Overview

The `main` function is located in `main.c`. It initializes the philosophers and their properties, creates threads for each philosopher, and handles cleanup at the end.

The philosopher's properties and actions are defined in `philo.h` and implemented in `init.c`, `actions.c`, and `routine.c`.

## Implementation Details

- `philo.h`: Header file containing the definitions of philosopher's properties and actions.
- `Makefile`: Makefile for compiling the project.
- `actions.c`: Implementation of philosopher actions such as picking up forks, eating, and sleeping.
- `exit.c`: Handles program exit and cleanup operations.
- `init.c`: Initializes philosophers and their properties.
- `main.c`: Contains the `main` function responsible for program execution flow.
- `routine.c`: Implements the routine followed by each philosopher.
