/**
 * main.cpp
 * Handles primary functionality of the menu application, such as displaying menu items and handling user input
 */

#include "Shelter.h"
#include "Menu.h"
#include "MenuCommand.h"
#include <iostream>
#include <functional>
#include <memory>

int main(int argc, char *argv[]) {
    int newlineSize;
    std::string directory;

    std::cout << "Enter the number of bytes in a newline: ";
    std::cin >> newlineSize;
    std::cin.ignore();
    std::cout << "What directory to write to: ";
    std::getline(std::cin, directory);
    Shelter shelter(directory, newlineSize);

    auto mainMenu = std::make_shared<Menu>('0', "Main");
    auto editPetMenu = std::make_shared<Menu>('2', "Edit Pet");

    editPetMenu->addMenuItem(std::make_shared<MenuCommand>('1', "Edit Pet Name", [&shelter]() {
        shelter.editPetName();
        return true;
    }));
    editPetMenu->addMenuItem(std::make_shared<MenuCommand>('2', "Edit Pet Type", [&shelter]() {
        shelter.editPetType();
        return true;
    }));
    editPetMenu->addMenuItem(std::make_shared<MenuCommand>('3', "Edit Pet Color", [&shelter]() {
        shelter.editPetColor();
        return true;
    }));
    editPetMenu->addMenuItem(std::make_shared<MenuCommand>('4', "Edit Pet Age", [&shelter]() {
        shelter.editPetAge();
        return true;
    }));
    editPetMenu->addMenuItem(std::make_shared<MenuCommand>('b', "Back", []() { return false; }));

    mainMenu->addMenuItem(std::make_shared<MenuCommand>('1', "List Pets", [&shelter]() {
        shelter.listPets();
        return true;
    }));
    mainMenu->addMenuItem(editPetMenu);
    mainMenu->addMenuItem(std::make_shared<MenuCommand>('3', "Add New Pet", [&shelter]() {
        shelter.addNewPet();
        return true;
    }));
    mainMenu->addMenuItem(std::make_shared<MenuCommand>('4', "Remove Pet", [&shelter]() {
        int id;
        std::cout << "Enter the id of the pet to remove: ";
        std::cin >> id;
        shelter.removePet(id);
        return true;
    }));
    mainMenu->addMenuItem(std::make_shared<MenuCommand>('Q', "Quit", []() { std::cout << "Done.\n";return false; }));

    mainMenu->select();

    return 0;
}
