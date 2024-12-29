/**
 * Pet.cpp
 * implements the member functions of the Pet class, which represents a pet with a name, type, and color.
 * The class provides getter and setter functions to access and modify the pet's attributes.
 */
#include "Pet.h"

/**
 * @brief Constructs a Pet object with optional initial values.
 * 
 * @param petName The name of the pet (default: empty string).
 * @param petType The type of the pet (default: empty string).
 * @param petColor The color of the pet (default: empty string).
 */
Pet::Pet(int id, std::string petName, std::string petType, std::string petColor, int petAge)
    : petID(id), name(petName), type(petType), color(petColor), age(petAge) {}

/**
 * @brief Retrieves the pet's name.
 * 
 * @return The name of the pet.
 */
std::string Pet::getName() const {
    return name;
}
int Pet::getID() const {
    return petID;
}

/**
 * @brief Retrieves the pet's type.
 * 
 * @return The type of the pet.
 */
std::string Pet::getType() const {
    return type;
}

/**
 * @brief Retrieves the pet's color.
 * 
 * @return The color of the pet.
 */
std::string Pet::getColor() const {
    return color;
}


int Pet::getAge() const {
    return age;
}

/**
 * @brief Updates the pet's name.
 * 
 * @param petName The new name of the pet.
 */
void Pet::setName(std::string petName) {
    name = petName;
}

void Pet::setID(int id) {
    petID = id;
}

/**
 * @brief Updates the pet's type.
 * 
 * @param petType The new type of the pet.
 */
void Pet::setType( std::string petType) {
    type = petType;
}

void Pet::setAge(int petAge) {
    age = petAge;
}

/**
 * @brief Updates the pet's color.
 * 
 * @param petColor The new color of the pet.
 */
void Pet::setColor( std::string petColor) {
    color = petColor;
}
