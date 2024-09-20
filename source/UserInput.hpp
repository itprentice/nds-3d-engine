/**
 * @file UserInput.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header interface for UserInput class
 * 
 */

#ifndef USERINPUT_H
#define USERINPUT_H
#include <nds.h>
#include <string>
#include <unordered_map>
class UserInput{
    protected:
        /**
         * @brief dictionary of axes and the bitmap that defines their +ve/-ve values
         * 
         */
        std::unordered_map<std::string, int> axes;
    public:
        float getAxis(std::string axisName);
        void configureAxis(std::string axisName, int postiveInput, int negativeInput);
};

#endif