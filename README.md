# BGU Fitness Studio Management System

## Introduction

Welcome to the BGU Fitness Studio Management System! This C++ program simulates the operations of a fitness studio, allowing you to manage trainers, workout sessions, and customer orders. This README provides essential information to understand, compile, and run the program successfully.

## Table of Contents

1. [Assignment Goals](#assignment-goals)
2. [Assignment Definition](#assignment-definition)
   - [Program Flow](#program-flow)
   - [Classes](#classes)
   - [Ordering Strategies](#ordering-strategies)
   - [Actions](#actions)
   - [Input File Format](#input-file-format)
3. [Implementation Details](#implementation-details)
   - [Provided Files](#provided-files)
   - [File Structure](#file-structure)
   - [Compilation](#compilation)
   - [Testing](#testing)
4. [Examples](#examples)
5. [Recommendations](#recommendations)

## Assignment Goals

The objective is to design an object-oriented system in C++, utilizing classes, standard data structures, and C++ properties like the "Rule of 5." Focus on efficient memory handling to avoid leaks.

## Assignment Definition

### Program Flow

The program starts with a configuration file as the first command-line argument. It opens the studio, performs various actions based on user input, and ends when the user enters the "closeall" action.

### Classes

- **Studio:** Manages trainers and workout plans.
- **Trainer:** Represents a trainer with available spots, session status, workout plans, and customers.
- **Workout:** Represents a workout with an ID, name, price, and type.
- **Customer:** Abstract class for different customer types with a workout ordering strategy.
- **BaseAction:** Abstract class for different action classes, enabling logging.

### Ordering Strategies

- **Sweaty Customer (swt):** Orders all cardio activities.
- **Cheap Customer (chp):** Orders the cheapest workout.
- **Heavy Muscle Customer (mcl):** Orders all anaerobic exercises from most expensive to cheapest.
- **Full Body Customer (fbd):** Orders the cheapest cardio, most expensive mixed, and cheapest anaerobic exercises.

### Actions

- **OpenTrainer:** Opens a trainer's session and assigns customers.
- **Order:** Starts a workout session with ordered workouts.
- **MoveCustomer:** Moves a customer between trainers.
- **Close:** Closes a trainer's session and prints the salary.
- **CloseAll:** Closes all workout sessions and exits.
- **PrintWorkoutOptions:** Prints available workout options.
- **PrintTrainerStatus:** Prints a status report of a given trainer.
- **PrintActionsLog:** Prints all user-performed actions.
- **BackupStudio:** Saves all studio information in a global variable called "backup."
- **RestoreStudio:** Restores the backed-up studio status.

### Input File Format

The input file contains the number of trainers, trainer capacities, and workout options. Comments and empty lines should be ignored.

## Implementation Details

### Provided Files

- Studio.h
- Trainers.h
- Action.h
- Customer.h
- Workout.h
- Main.cpp

### File Structure

```plaintext
.
├── src/
│   ├── (your .cpp files)
├── include/
│   ├── (your .h or .hpp files)
├── bin/
│   ├── (compiled executable - studio)
├── makefile
```

### Compilation

- The makefile should compile .cpp files into the bin/ folder, creating an executable named "studio."

### Testing

- Your program will be tested with different scenarios and input files.
- Ensure your program compiles without warnings or errors on department computers.
- Valgrind will be used to check for memory leaks.

## Examples

See the assignment page for input and output examples.

## Recommendations

1. Implement the Rule of Five as needed.
2. Re-download and re-test your submission on the department's computers after submission.
3. Avoid modifying the signature of provided functions.
4. Ensure your program compiles and runs without errors on the lab UNIX machine.

Good luck! 🏋️‍♂️
