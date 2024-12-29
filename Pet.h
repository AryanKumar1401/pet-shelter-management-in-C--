/**
 * Pet.h
 *
 * This header file defines the Pet class, which represents a pet with attributes such as name, type, and color.
 * The class provides getter and setter methods to access and modify these attributes.
 * It is designed to encapsulate the details of a pet and offers functionality to manipulate pet data.
 */

#ifndef PET_H
#define PET_H

#include <string>

/**
 * @brief The Pet class stores and manages information about a pet.
 * 
 * This class encapsulates the details of a pet, including its name, type, and color.
 * It provides getter and setter methods to retrieve and update these attributes.
 */
class Pet {
private:
    int petID;
    std::string name;  ///< The name of the pet
    std::string type;  ///< The type of the pet
    std::string color; ///< The color of the pet
    int age; ///< The age of the pet 

public:
    /**
     * @brief Constructs a Pet object with optional initial values.
     * 
     * @param petName The name of the pet (default: empty string).
     * @param petType The type of the pet (default: empty string).
     * @param petColor The color of the pet (default: empty string).
     */
    Pet(int id = 0, std::string petName = "", std::string petType = "", std::string petColor = "",int petAge=0);

    /**
     * @brief Retrieves the pet's ID
     * 
     * @return the id of the pet.
     */
    int getID() const;
    /**
     * @brief Retrieves the pet's name.
     * 
     * @return The name of the pet.
     */
    std::string getName() const;

    /**
     * @brief Retrieves the pet's type.
     * 
     * @return The type of the pet.
     */
    std::string getType() const;

    /**
     * @brief Retrieves the pet's color.
     * 
     * @return The color of the pet.
     */
    std::string getColor() const;
    /**
     * @brief Retrieves the pet's age.
     * 
     * @return The age of the pet.
     */
    int getAge() const;

    /**
     * @brief Updates the pet's name.
     * 
     * @param petName The new name of the pet.
     */
    void setName(std::string name);

    /**
     * @brief Updates the pet's type.
     * 
     * @param petType The new type of the pet.
     */
    void setType(std::string petType);

    /**
     * @brief Updates the pet's ID
     */
    void setID(int id);

    /**
     * @brief Updates the pet's color.
     * 
     * @param petColor The new color of the pet.
     */
    void setColor(std::string petColor);

    /**
     * @brief Updates the pet's age.
     * 
     * @param petColor The new age of the pet.
     */
    void setAge(int petAge);

};

#endif // PET_H
