//
// Created by Omer on 03/05/2018.
//

#include <exception>

#ifndef DATASTRUCTURES_HW1_EXCEPTIONS_H
#define DATASTRUCTURES_HW1_EXCEPTIONS_H

#define NEW_EXCEPTION(exp, from) \
    class exp : public from{\
    public: \
        virtual const char* what() const throw(){\
            return #exp;\
    }}

NEW_EXCEPTION(AVLTreeException, std::exception);
NEW_EXCEPTION(AVLElementNotFound, AVLElementNotFound);

#endif //DATASTRUCTURES_HW1_EXCEPTIONS_H
