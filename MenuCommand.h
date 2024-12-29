/**
 * MenuCommand.h
 * 
 * This header file defines the `MenuCommand` class, which inherits from the `MenuItem` class.
 * A `MenuCommand` represents an executable command in the menu system. 
 * It provides implementations for the `select()` and `display()` functions.
 */

#ifndef MENUCOMMAND_H
#define MENUCOMMAND_H

#include "MenuItem.h"

class MenuCommand : public MenuItem {
public:
    /**
     * Constructor for `MenuCommand`.
     * @param promptChar The character that will be used to select this command.
     * @param title The title or description of this command.
     */
    MenuCommand(char promptChar, std::string title, std::function<bool()> action);
    
    /**
     * Destructor for `MenuCommand`.
     */
    ~MenuCommand();
    
    /**
     * Implements the selection behavior for the command.
     * @return A boolean indicating whether the command was successfully executed.
     */
    bool select(); // Overriding select function

    /**
     * Displays the title of the command to the user.
     */
    void display(); // Overriding display function
private:
    std::function<bool()> action;
};

#endif
