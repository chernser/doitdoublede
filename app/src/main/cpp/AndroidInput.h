//
// Created by Sergey Chernov on 2019-05-12.
//

#ifndef DOITDOUBLEDE_ANDROIDINPUT_H
#define DOITDOUBLEDE_ANDROIDINPUT_H

#include "UserInput.h"

class AndroidInput : UserInput {

public:
    void onUserInputEvent(void *event);
};


#endif //DOITDOUBLEDE_ANDROIDINPUT_H
