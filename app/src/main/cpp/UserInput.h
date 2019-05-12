//
// Created by Sergey Chernov on 2019-05-12.
//

#ifndef DOITDOUBLEDE_USERINPUT_H
#define DOITDOUBLEDE_USERINPUT_H

/**
 * Represents user input devices and ways to interact with the game.
 * It depends on low level code like reading pressure from touch screen
 * or keys from keyboard or gamepad
 *
 */
class UserInput {


public:
    virtual void onUserInputEvent(void *event) = 0;
};




#endif //DOITDOUBLEDE_USERINPUT_H
