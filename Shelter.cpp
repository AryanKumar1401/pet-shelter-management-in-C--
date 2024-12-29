#include "Shelter.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <fstream>

using namespace std;

Shelter::Shelter(const std::string& directory, int newlineSize) : newlineSize(newlineSize) {
    // Calculate the correct record size
    // sizeof(int) for ID + 16 bytes for Name + 11 bytes for Type + 11 bytes for Color + sizeof(int) for Age
    recordSize = sizeof(int) + 16 + 11 + 11 + sizeof(int);

    // Set the file path
    filePath = directory + "/shelter.dat";

    // Open the file
    shelterFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!shelterFile) {
    // If opening in read/write mode fails, create the file
    std::ofstream createFile(filePath, std::ios::app);
    createFile.close();

    // Reopen in read/write mode
    shelterFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    }
    if (!shelterFile.is_open()) {
        throw std::runtime_error("Failed to open shelter.dat file.");
    }
    // Load pets from the file into memory
    loadPetsFromFile();
}

Shelter::~Shelter() {
    shelterFile.close();
}

void Shelter::loadPetsFromFile() {
    shelterFile.seekg(0, std::ios::beg);
    int offset = 0;

    while (true) {
        int id = 0, age = 0;
        char name[17] = {0}, type[12] = {0}, color[12] = {0};

        // Read fixed-size records
        if (!shelterFile.read(reinterpret_cast<char*>(&id), sizeof(int)))
            break;

        shelterFile.read(name, 16);
        shelterFile.read(type, 11);
        shelterFile.read(color, 11);
        if (!shelterFile.read(reinterpret_cast<char*>(&age), sizeof(int)))
            break;

        // Trim whitespace from strings
        std::string petName(name), petType(type), petColor(color);
        petName = petName.substr(0, petName.find_last_not_of(' ') + 1);
        petType = petType.substr(0, petType.find_last_not_of(' ') + 1);
        petColor = petColor.substr(0, petColor.find_last_not_of(' ') + 1);

        // Store pet and its file offset
        Pet pet(id, petName, petType, petColor, age);
        mPets[id] = pet;
        petFileOffsets[id] = offset;
        
        offset += recordSize;
    }
}

void Shelter::savePetToFile(const Pet& pet) {
    if (!shelterFile.is_open()) {
        std::cerr << "Error: File is not open." << std::endl;
        return;
    }

    // Get the file offset for this pet
    int offset = petFileOffsets[pet.getID()];
    shelterFile.clear();
    shelterFile.seekp(offset, std::ios::beg);

    if (!shelterFile) {
        std::cerr << "Error: Failed to seek to offset." << std::endl;
        return;
    }

    // Prepare data with fixed-width fields
    std::string name = pet.getName();
    std::string type = pet.getType();
    std::string color = pet.getColor();

    name.resize(16, ' ');   // Fixed width: 16
    type.resize(11, ' ');   // Fixed width: 11
    color.resize(11, ' ');  // Fixed width: 11

    // Write data with proper alignment
    int id = pet.getID();
    shelterFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
    shelterFile.write(name.c_str(), 16);
    shelterFile.write(type.c_str(), 11);
    shelterFile.write(color.c_str(), 11);
    int age = pet.getAge();
    shelterFile.write(reinterpret_cast<const char*>(&age), sizeof(age));

    if (!shelterFile) {
        std::cerr << "Error writing pet to file." << std::endl;
    } else {
        std::cout << "Successfully wrote pet to file." << std::endl;
    }

    shelterFile.flush();
}

void Shelter::listPets() {
    std::cout << "\nPets\n================================================================\n";
    std::cout << std::setw(5) << "ID" 
              << std::setw(15) << "NAME" 
              << std::setw(10) << "TYPE" 
              << std::setw(15) << "COLOR" 
              << std::setw(5) << "AGE" << std::endl;

    for (const auto& [id, pet] : mPets) {
        std::cout << std::setw(5) << id
                  << std::setw(15) << pet.getName()
                  << std::setw(10) << pet.getType()
                  << std::setw(15) << pet.getColor()
                  << std::setw(5) << pet.getAge() << std::endl;
    }
    std::cout << "================================================================\n";
}

void Shelter::addNewPet() {
    int id, age;
    std::string name, type, color;

    std::cout << "Add New Pet\nPet ID: ";
    std::cin >> id;    
    std::cin.ignore();
    std::cout << "Pet Name: ";
    std::getline(std::cin, name);  
    std::cout << "Pet Type: ";
    std::getline(std::cin, type);
    std::cout << "Color: ";
    std::getline(std::cin, color);
    std::cout << "Age: ";
    std::cin >> age;

    // Add new pet to the map
    Pet newPet(id, name, type, color, age);
    mPets[id] = newPet;

    // Calculate new record offset
    int offset = mPets.size() * recordSize - recordSize;
    petFileOffsets[id] = offset;

    // Save pet to file
    savePetToFile(newPet);

    std::cout << "Pet added successfully.\n";
}

void Shelter::removePet(int petID) {
    auto it = mPets.find(petID);
    if (it != mPets.end()) {
        // Remove pet from maps
        mPets.erase(it);
        petFileOffsets.erase(petID);

        // Rewrite the entire shelter data file
        rewriteShelterFile();

        std::cout << "Removed pet with ID " << petID << std::endl;
    } else {
        std::cout << "Pet with ID " << petID << " does not exist." << std::endl;
    }
}

void Shelter::editPetName() {
    int id;
    std::string newName;

    std::cout << "Enter the ID of the Pet whose name you'd like to change: ";
    std::cin >> id;

    auto it = mPets.find(id);
    if (it != mPets.end()) {
        std::cout << "Enter the new name for the pet: ";
        std::cin.ignore();
        std::getline(std::cin, newName);

        it->second.setName(newName);
        savePetToFile(it->second); // Save changes to the file
        std::cout << "Name changed to: " << newName << std::endl;
    } else {
        std::cout << "Pet with ID " << id << " not found.\n";
    }
}

void Shelter::editPetType() {
    int id;
    std::string newType;

    std::cout << "Enter the ID of the Pet whose type you'd like to change: ";
    std::cin >> id;

    auto it = mPets.find(id);
    if (it != mPets.end()) {
        std::cout << "Enter the new type for the pet: ";
        std::cin.ignore();
        std::getline(std::cin, newType);

        it->second.setType(newType);
        savePetToFile(it->second); // Save changes to the file
        std::cout << "Type changed to: " << newType << std::endl;
    } else {
        std::cout << "Pet with ID " << id << " not found.\n";
    }
}

void Shelter::editPetColor() {
    int id;
    std::string newColor;

    std::cout << "Enter the ID of the Pet whose color you'd like to change: ";
    std::cin >> id;

    auto it = mPets.find(id);
    if (it != mPets.end()) {
        std::cout << "Enter the new color for the pet: ";
        std::cin.ignore();
        std::getline(std::cin, newColor);

        it->second.setColor(newColor);
        savePetToFile(it->second); // Save changes to the file
        std::cout << "Color changed to: " << newColor << std::endl;
    } else {
        std::cout << "Pet with ID " << id << " not found.\n";
    }
}

void Shelter::editPetAge() {
    int id, newAge;

    std::cout << "Enter the ID of the Pet whose age you'd like to change: ";
    std::cin >> id;

    auto it = mPets.find(id);
    if (it != mPets.end()) {
        std::cout << "Enter the new age for the pet: ";
        std::cin >> newAge;

        it->second.setAge(newAge);
        savePetToFile(it->second); // Save changes to the file
        std::cout << "Age changed to: " << newAge << std::endl;
    } else {
        std::cout << "Pet with ID " << id << " not found.\n";
    }
}

void Shelter::writeBlankRecord(int offset) {
    // Seek to the specified offset
    shelterFile.seekp(offset, std::ios::beg);

    // Write blank spaces to overwrite the record
    std::string blankRecord(recordSize, ' ');
    shelterFile.write(blankRecord.c_str(), recordSize);
    shelterFile.flush();
}

void Shelter::rewriteShelterFile() {
    // Close the current file
    shelterFile.close();

    // Reopen the file in truncation mode to overwrite it
    shelterFile.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!shelterFile.is_open()) {
        std::cerr << "Error: Unable to open " << filePath << " for rewriting." << std::endl;
        return;
    }

    petFileOffsets.clear();
    int offset = 0;

    // Write all pets to the file and update offsets
    for (const auto& [id, pet] : mPets) {
        petFileOffsets[id] = offset;

        // Prepare data with fixed-width fields
        std::string name = pet.getName();
        std::string type = pet.getType();
        std::string color = pet.getColor();

        name.resize(16, ' ');   // Fixed width: 16
        type.resize(11, ' ');   // Fixed width: 11
        color.resize(11, ' ');  // Fixed width: 11

        // Write data with proper alignment
        int petID = pet.getID();
        shelterFile.write(reinterpret_cast<const char*>(&petID), sizeof(int));
        shelterFile.write(name.c_str(), 16);
        shelterFile.write(type.c_str(), 11);
        shelterFile.write(color.c_str(), 11);
        int age = pet.getAge();
        shelterFile.write(reinterpret_cast<const char*>(&age), sizeof(int));

        if (!shelterFile) {
            std::cerr << "Error writing pet to file." << std::endl;
            break;
        }

        offset += recordSize;
    }

    shelterFile.flush();
    shelterFile.close();

    // Reopen the file in read/write mode
    shelterFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!shelterFile.is_open()) {
        std::cerr << "Error: Unable to reopen " << filePath << " after rewriting." << std::endl;
    }
}
