#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>

#include "calc.h"

Calculator::Calculator() {
    this->_running = true;

    this->_help_message = "Please enter the operation to perform.\n";
    this->_help_message += "Format (spaces don't matter): a+b, a-b, a*b, a/b\n";
    this->_help_message += "Type 'clear' to clear the screen.\n";
    this->_help_message += "Type 'exit' to quit.\n";
    this->_help_message += "Type 'help' at any time to bring this text up again.\n";
    this->_help_message += "=======================================================\n\n";

    std::cout << "\n              ~~<CALCULATOR APP>~~\n"
              << "=================================================\n\n"
              << this->_help_message;
}

bool Calculator::is_running() {
    return this->_running;
}

char to_lower(char c) {
    return std::tolower(static_cast<unsigned char>(c));
};

Command Calculator::Get_Command() {
    std::string cmd;
    std::getline(std::cin, cmd);

    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());

    std::transform(cmd.begin(), cmd.end(), cmd.begin(), to_lower);

    if (cmd == "help") return {CmdType::Help}; 
    if (cmd == "exit") return {CmdType::Exit};
    if (cmd == "clear") return {CmdType::Clear};

    double x = 0.0;
    double y = 0.0;
    char oper = '+';
    std::istringstream iss(cmd);

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
