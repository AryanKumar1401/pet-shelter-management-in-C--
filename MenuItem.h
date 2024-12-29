/**
 * MenuItem.h
 * 
 * This header file defines the abstract base class `MenuItem`. 
 * The `MenuItem` class represents a single item that can be displayed in a menu.
 * It has two pure virtual functions that must be implemented by derived classes 
 * for selection (`select()`) and display (`display()`).
 */

#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

class MenuItem {
public:
    /**
     * Constructor for `MenuItem`.
     * @param promptChar The character that will be used to select this menu item.
     * @param title The title or description of this menu item.
     */
    MenuItem(char promptChar, std::string title)
        : mPromptChar(promptChar), mTitle(title) {}

    /**
     * destructor for `MenuItem`.
     */
    virtual ~MenuItem() {
        //std::cout << "MenuItem " << mTitle << " deleted." << std::endl;
    }

    /**
     * Pure virtual function that must be overridden in derived classes.
     * This function is called when the menu item is selected.
     * @return A boolean indicating whether the item was successfully selected.
     */
    virtual bool select() = 0; // Pure virtual function for selecting the item

    /**
     * Pure virtual function that must be overridden in derived classes.
     * This function is used to display the menu item to the user.
     */
    virtual void display() = 0; // Pure virtual function for displaying the item

    /**
     * Getter function to retrieve the prompt character of the menu item.
     * @return The prompt character that corresponds to this menu item.
     */
    char getPromptChar() { return mPromptChar; }

protected:
    char mPromptChar;    ///< The character used to select this menu item.
    std::string mTitle;  ///< The title or label of this menu item.
};

#endif
