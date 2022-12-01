/**
 * @file solve.cpp
 * @author flexhaufen
 * @brief Solver for Calculator
 * @version 0.1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDES ***
#include "solve.h"
#include "vector.h"

//*** DEFINES ***
const f32 M_PI = 3.1415926f;
const f32 M_E  = 2.7182818f;


c8* reverseString(const c8* string,c8 length){
    auto tmp = (c8*)malloc((length+1)*sizeof(c8));
    if(!tmp)
        return nullptr;

    tmp[length]='\0';
    for (s32 i = 0; i < length; ++i) {
        tmp[i]=string[length-1-i];
    }
    return tmp; //make sure to free the returned pointer
}

f32 CalcSolve(const c8* eq,c8 start,c8 end,const f32* vars) {
    
    // If eq is not valid return NaN
    if(end<=start)
        return std::nanf("");

    // arrays to store numbers and operators
    Vector<f32> numbers;
    Vector<c8> plusIndex;
    Vector<c8> multIndex;
    Vector<c8> powIndex;

    auto tmp = (c8*)malloc(MAX_NUMBER_LENGTH*sizeof(c8));
    if(!tmp)
        return std::nanf("");
    c8 tmpc=0;
    c8* reversed;

    //parse string eq
    //parsing from right to left allows us to
    //e.g. multiply the number to the right of binary operators with -1 for subtraction
    for (c8 i = end-1; i >= start; --i) {
        //check if current c8 is number or decimalpoint '.' using ascii
        if((eq[i]>47 && eq[i]<58) || eq[i]==46) {
            if(tmpc>=MAX_NUMBER_LENGTH)
                return std::nanf("");

            tmp[tmpc++]=eq[i];
        }
        else if(eq[i] == '+') {
            if(tmpc>0) {
                reversed=reverseString(tmp,tmpc);
                if(!reversed)
                    return std::nanf("");
                plusIndex.push(numbers.push(strtof(reversed,nullptr)));
                free(reversed);
                tmpc=0;
            }
            //handling wrong or weird inputs
            else if(i==end-1) {
                return std::nanf("");
            }
            //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
            else if(plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(plusIndex.size() - 1))) {
                plusIndex.push(numbers.size());
            }
        }
        else if(eq[i] == '-') {
            if(tmpc>0) {
                reversed=reverseString(tmp,tmpc);
                if(!reversed)
                    return std::nanf("");
                plusIndex.push(numbers.push(-strtof(reversed,nullptr)));
                free(reversed);
                tmpc=0;
            }
            //handling wrong or weird inputs
            else if(i==end-1) {
                return std::nanf("");
            }
            //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
            else if(plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size()!= *plusIndex.at(plusIndex.size() - 1))) {
                *numbers.at(numbers.size() - 1)*=-1;
                plusIndex.push(numbers.size());
            }
            else {
                *numbers.at(numbers.size() - 1)*=-1;
            }
        }
        //check for multiplication
        else if(eq[i]=='*') {
            if(tmpc>0) {
                reversed=reverseString(tmp,tmpc);
                if(!reversed)
                    return std::nanf("");
                multIndex.push(numbers.push(strtof(reversed,nullptr)));
                free(reversed);
                tmpc=0;
            }
            else if(i==end-1 || i==start) {
                return std::nanf("");
            }
            //this case is for a*-b. because - is pushed into the plusIndex array we need to remove it.
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) {
                plusIndex.pop();
                multIndex.push(numbers.size());
            }
            else {
                multIndex.push(numbers.size());
            }
        }
        else if(eq[i]=='/') {
            if(tmpc>0) {
                reversed=reverseString(tmp,tmpc);
                if(!reversed)
                    return std::nanf("");
                multIndex.push(numbers.push((f32)1/strtof(reversed,nullptr)));
                free(reversed);
                tmpc=0;
            }
            else if(i==end-1 || i==start) {
                return std::nanf("");
            }
            //this case is for a/-b. because - is pushed into the plusIndex array we need to remove it.
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) {
                plusIndex.pop();
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
            else {
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
        }
        else if(eq[i]=='^'){
            if(tmpc>0) {
                reversed=reverseString(tmp,tmpc);
                if(!reversed)
                    return std::nanf("");
                multIndex.push(numbers.push(strtof(reversed,nullptr)));
                powIndex.push(numbers.size());
                free(reversed);
                tmpc=0;
            }
            else if(i==end-1 || i==start) {
                return std::nanf("");
            }//this case is for a/-b. because - is pushed into the plusIndex array we need to remove it.
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) {
                plusIndex.pop();
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }
            else{
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }

        }
        //if we find a closing bracket, try to find a matching opening bracket and call solve recursively
        else if(eq[i]==')'){
            //try to find a matching '(':
            c8 numClosingBrackets=0;
            c8 foundMatching=0;
            for(c8 j=i-1;j>=start;--j){
                if(eq[j]==')')
                    ++numClosingBrackets;
                else if(eq[j]=='(' && numClosingBrackets>0)
                    --numClosingBrackets;
                else if(eq[j]=='(' && numClosingBrackets==0) {
                    //matching '(' found
                    if(!foundMatching) {
                        numbers.push(CalcSolve(eq, j + 1, i,vars));
                        i = j;//skip the part between () in parsing
                        foundMatching = 1;
                    }
                }
            }
            if(!foundMatching)
                return std::nanf("");
        }
        else {
            //unary operators:
            //trig functions work with rad not deg!
            if(i>2 && eq[i]=='n' && eq[i-1]=='i' && eq[i-2]=='s' && eq[i-3]=='a'){
                if(numbers.size())
                    *numbers.at(numbers.size()-1) = asin(*numbers.at(numbers.size()-1));
                i-=3;
                if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) {
                    plusIndex.pop();
                }
            }
            else if(i>1 && eq[i]=='n' && eq[i-1]=='i' && eq[i-2]=='s'){
                if(numbers.size())
                    *numbers.at(numbers.size()-1) = sin(*numbers.at(numbers.size()-1));
                i-=2;
                if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) {
                    plusIndex.pop();
                }
            }


            //constants
            else if(i>0 && eq[i]=='i' && eq[i-1]=='p') {
                numbers.push(M_PI);
                i-=1;
            }
            else if(eq[i]=='e'){
                numbers.push(M_E);
            }
            else if(i>1 && eq[i]=='s' && eq[i-1]=='n' && eq[i-2]=='a'){
                if(vars) {
                    numbers.push(vars[0]);
                }
                else {
                    numbers.push(std::nanf(""));
                }
                i-=2;
            }
            else {
                return std::nanf("");
            }
        }
    }

    //push to numbers array one last time
    if(tmpc>0) {
        reversed=reverseString(tmp,tmpc);
        if(!reversed)
            return std::nanf("");
        numbers.push(strtof(reversed,nullptr));
        free(reversed);
        tmpc=0;
    }

    if(numbers.size()==0)
        return std::nanf("");

    //we start with power a^b
    if(powIndex.size() > 0) {
        for (c8 i = powIndex.size()-1;i>=0; --i){
            //check if '*' is associated with two numbers:
            if(*powIndex.at(i)>= numbers.size())
                return std::nanf("");
            (*numbers.at(*powIndex.at(i)-1)) = pow((*numbers.at(*powIndex.at(i))),(*numbers.at(*powIndex.at(i)-1)));
            (*numbers.at(*powIndex.at(i))) = 1;
        }
    }

    if(multIndex.size() > 0) {
        for (c8 i = multIndex.size()-1;i>=0  ; --i){
            //check if '*' is associated with two numbers:
            if(*multIndex.at(i)>= numbers.size())
                return std::nanf("");
            (*numbers.at(*multIndex.at(i)-1)) *= (*numbers.at(*multIndex.at(i)));
        }
    }

    f32 result=*numbers.at(0);
    for (c8 i=0;i< plusIndex.size(); ++i){
        result+=*numbers.at(*plusIndex.at(i));
    }
    free(tmp);

    return result;
}
