# Pet Shelter Management System

A C++ console application for managing a pet shelter's records. The system allows users to maintain a database of pets with their details and perform various operations through an interactive menu interface.

## Features

- **Pet Management**
  - Add new pets with unique IDs
  - List all pets in the shelter
  - Remove pets from records
  - Edit pet details:
    - Name
    - Type
    - Color
    - Age

- **Data Persistence**
  - Stores pet records in a binary file (`shelter.dat`)
  - Uses fixed-width record format for efficient random access
  - Maintains file integrity during updates and deletions

## Technical Implementation

- **Class Structure**
  - `Pet`: Represents individual pets with their attributes
  - `Shelter`: Manages the collection of pets and file operations
  - `Menu`: Implements hierarchical menu system
  - `MenuItem`: Abstract base class for menu items
  - `MenuCommand`: Handles executable menu commands

- **File Operations**
  - Binary file I/O for data persistence
  - Random access file operations
  - Fixed-width record format

## Building and Running

1. Ensure you have a C++ compiler installed (e.g., g++)
2. Compile the project:
```sh
g++ *.cpp -std=c++17 -o shelter