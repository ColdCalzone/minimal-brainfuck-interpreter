#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

namespace Token
{
    enum struct Tokens { Increment, Decrement, LoopStart, LoopEnd, PointerRight, PointerLeft, Input, Output, End, Illegal };

    Tokens get_token(char type);

    std::ostream& operator<<(std::ostream& os, const Tokens& obj);
};


#endif // TOKEN_H
