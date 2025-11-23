#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>

#include "calc.h"

void remove_char(char* str, char c) {
    char* write = str;

    for (char* read = str; *read != '\0'; read++) {
        if (*read == c) { continue; }
        *write = *read;
        write++;
    }
    *write = '\0';
}

Calculator::Calculator() {
    this->_running = true;

    this->_help_message =
        "Please enter the operation to perform.\n"
        "Format (spaces don't matter): a+b, a-b, a*b, a/b\n"
        "Type 'clear' to clear the screen.\n"
        "Type 'exit' to quit.\n"
        "Type 'help' at any time to bring this text up again.\n"
        "=======================================================\n\n";

    std::cout << "\n              ~~<CALCULATOR APP>~~\n"
              << "=================================================\n\n"
              << this->_help_message;
}

bool Calculator::is_running() {
    return this->_running;
}

Command Calculator::Get_Command() {
    if (!std::cin.getline(this->_cmd, 65)) {
        return {CmdType::Invalid};
    }

    remove_char(this->_cmd, ' ');

    std::transform(this->_cmd, this->_cmd+std::strlen(this->_cmd), this->_cmd, ::tolower);

    if (std::strcmp(this->_cmd, "help") == 0) return {CmdType::Help}; 
    if (std::strcmp(this->_cmd, "exit") == 0) return {CmdType::Exit};
    if (std::strcmp(this->_cmd, "clear") == 0) return {CmdType::Clear};

    double x = 0.0;
    double y = 0.0;
    char oper = '+';
    std::istringstream iss(this->_cmd);

    if (iss >> x >> oper >> y) {
        return {CmdType::Operation, x, y, oper};
    }

    return {CmdType::Invalid};
}

double Calculator::Calculate(double x, char oper, double y) {
    switch(oper) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        default:
            return 0.0;
    }
}

void Calculator::Run_Command() {
    double result = 0.0;
    Command cmd = this->Get_Command();

    switch(cmd.type) {
        case CmdType::Exit:
            this->_running = false;
            break;
        case CmdType::Clear:
            #if defined(_WIN32)
                system("cls");
            #else
                system("clear");
            #endif
            break;
        case CmdType::Operation:
            if (cmd.oper == '/' && cmd.y == 0) {
                std::cout << "Inf\n";
                break;
            }
            result = this->Calculate(cmd.x, cmd.oper, cmd.y);
            std::cout << cmd.x << cmd.oper << cmd.y << " = " << result << "\n";
            break;
        case CmdType::Help:
            std::cout << this->_help_message;
            break;
        default:
            std::cout << "Invalid operation!\n";
            break;
    }
}
