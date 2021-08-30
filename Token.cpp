#include <iostream>
#include <string>
#include <type_traits>
#include "Token.h"

// Tokens for each instruction in BrainFuck
namespace Token
{
    Tokens get_token(char type)
    {
        switch(type) {
            case '+':
                return Tokens::Increment;
            case '-':
                return Tokens::Decrement;
            case '[':
                return Tokens::LoopStart;
            case ']':
                return Tokens::LoopEnd;
            case '>':
                return Tokens::PointerRight;
            case '<':
                return Tokens::PointerLeft;
            case ',':
                return Tokens::Input;
            case '.':
                return Tokens::Output;
            default:
                // Remember to handle this!
                return Tokens::Illegal;
        }
    }

    // https://stackoverflow.com/questions/11421432/how-can-i-output-the-value-of-an-enum-class-in-c11#11421471
    std::ostream& operator<<(std::ostream& os, const Tokens& obj)
    {
        switch(obj) {
            case Tokens::Increment:
                os << "+";
                break;
            case Tokens::Decrement:
                os << "-";
                break;
            case Tokens::LoopStart:
                os << "[";
                break;
            case Tokens::LoopEnd:
                os << "]";
                break;
            case Tokens::PointerRight:
                os << ">";
                break;
            case Tokens::PointerLeft:
                os << "<";
                break;
            case Tokens::Input:
                os << ",";
                break;
            case Token::Tokens::Output:
                os << ".";
                break;
            default:
                os << "?";
        }
        return os;
    }
}
