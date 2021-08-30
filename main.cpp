#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Token.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

vector<int> call_stack;

int8_t tape[30000];

int pointer = 0;

bool debug_mode = false;

vector<Token::Tokens> command_stack;

int command_pointer = 0;

int interpret(Token::Tokens token) {
    switch(token) {
        case Token::Tokens::Increment:
            tape[pointer]++;
            break;
        case Token::Tokens::Decrement:
            tape[pointer]--;
            break;
        case Token::Tokens::LoopStart:
            if(tape[pointer] == 0) {
                int depth = 0;
                // Two break conditions: EOF or find end of loop
                while(command_stack[command_pointer] != Token::Tokens::End) {
                    if(command_stack[command_pointer] == Token::Tokens::LoopStart) {
                        depth += 1;
                    } else if(command_stack[command_pointer] == Token::Tokens::LoopEnd) {
                        depth -= 1;
                        if(depth == 0) {
                            break;
                        }
                    }
                    command_pointer += 1;
                }
            } else {
                call_stack.push_back(command_pointer);
            }
            break;
        case Token::Tokens::LoopEnd:
            if(tape[pointer] != 0) {
                command_pointer = call_stack.back();
            } else {
                call_stack.pop_back();
            }
            break;
        case Token::Tokens::PointerRight:
            if(pointer == 29999) {
                pointer = 0;
            } else {
                pointer++;
            }
            break;
        case Token::Tokens::PointerLeft:
            if(pointer == 0) {
                pointer = 29999;
            } else {
                pointer--;
            }
            break;
        case Token::Tokens::Input:
            char input;
            cin >> input;
            tape[pointer] = input;
            break;
        case Token::Tokens::Output:
            if(debug_mode) {
                cout << static_cast<int>(tape[pointer]) << " -> ";
            }
            cout << tape[pointer];
            if(debug_mode) {
                cout << endl;
            }
            break;
        case Token::Tokens::End:
            return 0;
        default:
            break;
    }
    command_pointer++;
    return 1;
}

int main(int argc, char *argv[]) {
    string source_file;
    // Check if a source file was provided:
    if(argc < 2) {
        cout << "Please provide a *.bf source file:" << endl;
        cin >> source_file;
    } else {
        if(argv[1] == string("-d")) {
            debug_mode = true;
        } else if(argv[1] == string("--help")) {
            if(argc > 2) {
                if(argv[2] == string("2")) {
                    cout << "The tape is a 30,000 element long array of signed 8 bit ints, with an int pointing to a position. The tape loops infinitely." << endl;
                    cout << "[ and ] work with a vector called the call stack, upon reaching ] it jumps back to the [ by popping the last element." << endl;
                    cout << ", unsurprisingly works with cin." << endl;
                    cout << "Make a guess how . works. I'll wait." << endl;
                }
            } else {
                srand(time(0));
                cout << "Minimal ";
                switch(rand() % 6) {
                case 0:
                    cout << "BF ";
                    break;
                case 1:
                    cout << "BrainFuck ";
                    break;
                case 2:
                    cout << "BrainF*ck ";
                    break;
                case 3:
                    cout << "BrainF**k ";
                    break;
                case 4:
                    cout << "Br**nFuck ";
                    break;
                case 5:
                    cout << "BrainOof ";
                    break;
            }
                cout << "Interpreter " << endl << "Implemented in C++" << endl << endl;
                cout << "Usage: run the program with a *.bf file (or give it a *.bf file when asked) to execute the program" << endl << "Supports all operations." << endl;
                cout << "Run with the -d argument to get a more detailed look at the output." << endl;
                cout << "Run --help 2 for details on implementation" << endl;
            }
            return 0;
        }
        source_file = argv[argc-1];
    }
    // Continue execution:
    string content;
    std::ifstream source(source_file);

    // Output the content of the file.
    while(getline(source, content)) {
        // https://stackoverflow.com/questions/14668326/iterate-through-string-char-by-char
        for(auto c : content) {
            Token::Tokens token = Token::get_token(c);
            if(token != Token::Tokens::Illegal) {
                command_stack.push_back(token);
            }
        }
    }
    command_stack.push_back(Token::Tokens::End);

    source.close();

    while(command_stack[command_pointer] != Token::Tokens::End) {
        interpret(command_stack[command_pointer]);
    }

    return 0;
}
