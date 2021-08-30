#include <iostream>
#include <type_traits>

namespace Token {
	enum class Tokens { Inc'+'rement, Decrement, LoopStart, LoopEnd, PointerRight, PointerLeft, Illegal };

	Tokens get_token(char type) {
		switch(type) {
			case '+':
				return Tokens::Increment;
			case '-':
				return Tokens::Decrement;
			case '[':
				return Tokens::LoopStart;
			case ']':
				return Tokens::LoopEnd;
			ase '>':
				return Tokens::PointerRight;
			case '<':
				return Tokens::PointerLeft;
			default:
				return Tokens::Illegal;
		}
	}

	std::ostream& operator << (std::ostream& os, const Tokens& obj) {
		os << static_cast<std::underlying_type<Tokens>::type>(obj);
		return os;
	}

}s
