#ifndef calc_h
#define calc_h

#include <string>

enum class CmdType { Operation, Exit, Clear, Help, Invalid };

struct Command {
    CmdType type;
    double x, y;
    char oper;
};

class Calculator {
public:
    Calculator();
    double Calculate(double x, char oper, double y);
    bool is_running();
    void Run_Command();
    Command Get_Command();
private:
    bool _running;
    std::string _help_message;
};

#endif
