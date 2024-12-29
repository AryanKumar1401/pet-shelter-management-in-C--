/**
 * Menu.h
 * 
 * This header file defines the `Menu` class, which inherits from the `MenuItem` class.
 * A `Menu` represents a collection of other `MenuItem` objects (including other menus or commands).
 * It implements the functionality to add items, display the menu, and select an item.
 */

#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include <map>
#include <memory>

class Menu : public MenuItem {
public:
    /**
     * Constructor for `Menu`.
     * @param promptChar The character that will be used to select this menu.
     * @param title The title or description of the menu.
     */
    Menu(char promptChar, std::string title); // Constructor

    /**
     * Destructor for `Menu`.
     */
    ~Menu();

    /**
     * Adds a new `MenuItem` to this menu.
     * @param item A pointer to the `MenuItem` to be added.
     */
    void addMenuItem(std::shared_ptr<MenuItem> item); // Add an item to the menu

    /**
     * Overrides the selection behavior for the menu.
     * The user selects one of the items in the menu.
     * @return A boolean indicating whether the selection was successful.
     */
    bool select(); // Overriding select function

    /**
     * Displays the menu and its items to the user.
     */
    void display(); // Overriding display function

private:
   std::map<char, std::shared_ptr<MenuItem>> mItems; 
};
#endif