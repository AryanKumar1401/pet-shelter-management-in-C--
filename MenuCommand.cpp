/**
 * MenuCommand.cpp
 * Implements the MenuCommand class
 */

#include "MenuCommand.h"
#include <iostream>

MenuCommand::MenuCommand(char promptChar, std::string title, std::function<bool()> action)
    : MenuItem(promptChar, title),action(action) {}

MenuCommand::~MenuCommand() {
}

bool MenuCommand::select() {
    return action();
}

void MenuCommand::display() {
    std::cout << mPromptChar << "> " << mTitle << std::endl;
}
