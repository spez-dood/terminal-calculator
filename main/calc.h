#ifndef calc_h
#define calc_h

enum class CmdType { Operation, Exit, Clear, Help, Invalid };

struct Command {
    CmdType type;
    double x, y;
    char oper;
};

class Calculator {
public:
    Calculator();
    bool is_running();
    void Run_Command();
private:
    bool _running;
    const char* _help_message;
    double Calculate(double x, char oper, double y);
    Command Get_Command();
};

#endif
