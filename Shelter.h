/**
 * Shelter.h
 * This file is the interface for the Shelter class. 
 * The Shelter class is responsible for managing a collection of Pet objects.
 * It provides functionality to add, list, remove, and update pets.
 */

#ifndef SHELTER_H
#define SHELTER_H

#include "Pet.h"
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>

class Shelter {
public:
    Shelter(const std::string& directory, int newlineSize);
    ~Shelter();
    /**
     * Lists all the pets currently in the shelter.
     * This function iterates through the vector of pets and prints their details (name, type, and color).
     * If no pets are present, it does nothing.
     */
    void listPets();

    /**
     * Adds a new pet to the shelter.
     * This function prompts the user for the pet's name, type, and color, 
     * creates a new Pet object, and adds it to the shelter's vector of pets.
     */
    void addNewPet();

    /**
     * Removes a pet from the shelter.
     * this function will allow the user to remove a pet from the shelter's list.
     */
    void removePet(int petID);

    /**
     * Edits the name of the pet
     */
    void editPetName();

    /**
     * Edits the type of the pet
     */
    void editPetType();

    /**
     * Edits the color of the pet
     */
    void editPetColor();

    /*
    * Edits the age of the pet
    */
    void editPetAge();

private:
    /**
     * A vector to store the list of Pet objects in the shelter.
     * Each Pet object represents an individual pet with attributes like name, type, and color.
     */
    std::map<int, Pet> mPets;

    /** 
     * Maps pet IDs to their corresponding file offsets in shelter.dat.
     * Key: Pet ID
     * Value: Byte offset in the file where the pet's record begins
     * Used to quickly locate and update pet records without scanning the entire file.
     */
    std::map<int, int> petFileOffsets;     

    /**
     * File stream handle for shelter.dat.
     * Opened in binary mode for random access read/write operations.
     * Remains open for the lifetime of the Shelter object.
     */
    std::fstream shelterFile; 

    /**
     * The total size in bytes of each pet record in the file.
     */
    int recordSize;     

    /**
     * Number of bytes used for newline characters on the current system.
     * 1 byte for Unix/Mac OS (\n)
     * 2 bytes for Windows (\r\n)
     * Used to correctly calculate record sizes and file positions.
     */                
    int newlineSize;                    

    std::string filePath;

    /**
     * Rewrites the entire shelter data file based on the current pets in mPets.
     * Called when a pet is removed to update the data file.
     */
    void rewriteShelterFile();

    /**
     * Loads all pet records from shelter.dat into memory.
     * Called during Shelter construction.
     * Populates both mPets and petFileOffsets maps.
     * Handles fixed-width field parsing and whitespace trimming.
     * @throws std::runtime_error if file read operations fail
     */
    void loadPetsFromFile();

    /**
     * Writes a pet's record to shelter.dat at its designated offset.
     * Uses fixed-width fields with space padding to maintain consistent record sizes.
     * @param pet The Pet object to save to the file
     * @throws std::runtime_error if file write operations fail
     */
    void savePetToFile(const Pet& pet);

    /**
     * Writes an empty record at the specified file offset.
     * Used when removing pets to maintain file structure integrity.
     * Fills the record space with spaces/null bytes.
     * @param offset The byte position in the file to write the blank record
     * @throws std::runtime_error if file write operations fail
     */
    void writeBlankRecord(int offset);
};

#endif
