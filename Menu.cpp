/**
 * Menu.cpp
 * This file contains the implementation for the Menu class functions
 */

#include "Menu.h"
#include <iostream>

Menu::Menu(char promptChar, std::string title)
    : MenuItem(promptChar, title) {}

Menu::~Menu() {
}
void Menu::addMenuItem(std::shared_ptr<MenuItem> item) {
    mItems[item->getPromptChar()] = item;
}

bool Menu::select() {
    while (true) {
        // Display the menu title and items
        std::cout << "\n==== " << mTitle << " MENU ====" << std::endl;
        for (const auto& pair : mItems) {
            pair.second->display();
        }

        // Prompt user for a choice
        std::cout << "Enter choice> ";
        char choice;
        std::cin >> choice;

        // Validate the user's choice using std::map::find
        auto it = mItems.find(choice);
        if (it != mItems.end()) {
            // Execute the selected command
            bool shouldContinue = it->second->select();
            if (!shouldContinue) {
                // If 'Back' or 'Quit' was selected, determine action based on choice
                return choice == 'b'; // Return true for 'Back' to continue the previous menu, false to quit
            }
        } else {
            std::cout << "Unknown Menu Selection" << std::endl;
        }
    }
}

void Menu::display() {
    std::cout << mPromptChar << "> " << mTitle << std::endl;
}
