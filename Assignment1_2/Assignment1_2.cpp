#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
#include <cmath>

//operator precedence will be stored using this class
//class op_precedence
//{
//public:
//    op_precedence(char name, int prec)
//        :op_name(name), precedence(prec)
//    {
//
//    }
//private:
//    char op_name;
//    int precedence;
//};

class op
{
public:
    op(bool IsOperand, int value)
    {
        _IsOperand = IsOperand;
        _value = value;
    }
private:
    bool _IsOperand;
    int _value;
};
//functions
int CharToIndex(char Operator)
{
    switch (Operator)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '+':
        return 4;
    case '-':
        return 5;
    }
    return -1;
}
float Calc(std::stack<op> postfix_stack)
{
    float result = 0.0; //return value



    return round((result * 100)) * 0.01;
}

int main(int argc, char** argv)
{
    enum OP_index {
        paren_left = 0, paren_right, multi, division, addition, subtract
    };
    int OP_precedence[6] = {0, 0, 2, 2, 1, 1};
    //op_precedence paren_left('(', 0);
    //op_precedence paren_right(')', 0);
    //op_precedence multi('*', 1);
    //op_precedence division('/', 1);
    //op_precedence addition('+', 2);
    //op_precedence subtract('-', 2);
    //stores the operand data and operator data with stack
    std::stack<char> Operator_stk;
    //std::stack<int> postfix_stk;
    std::stack<op> postfix_stk;
    //file read
    FILE* fp_input = fopen("input.txt", "r");
    if (fp_input == nullptr) {
        exit(EXIT_FAILURE);
    }

    //std::string postfix_string = "";
    char scan_char = '\0';
    int scan_int = 0;
    
    while (!feof(fp_input))
    {
        fscanf(fp_input, "%c", &scan_char);
        switch (scan_char)
        {
        case '(':
            Operator_stk.push(scan_char);
            break;
        case ')':
            while (Operator_stk.top() != '(')
            {
                postfix_stk.push(op(false, Operator_stk.top()));
                Operator_stk.pop();
            }
            Operator_stk.pop();
            break;
        case '*':
        case '/':
        case '+':
        case '-':
            if (Operator_stk.size() != 0) {
                if (OP_precedence[CharToIndex(scan_char)] <= OP_precedence[CharToIndex(Operator_stk.top())]) {
                    postfix_stk.push(op(false, Operator_stk.top()));
                    Operator_stk.pop();
                }
            }
            Operator_stk.push(scan_char);
            break;
        default:
            fseek(fp_input, -1, SEEK_CUR);
            fscanf(fp_input, "%d", &scan_int);
            postfix_stk.push(op(true, scan_int));
            //postfix_string.append(std::to_string(scan_int));
        }
    }
    //move all the remaining operators in operator_stk
    while (Operator_stk.size() != 0)
    {
        postfix_stk.push(op(false, Operator_stk.top()));
        Operator_stk.pop();
    }
    fclose(fp_input);
    fp_input = nullptr;
#if 1

#endif
#if 0
    float result = Calc(postfix_stk);
#endif

#if 0
    int example = 0;
    char ex2 = '\0';
    fscanf(fp_input, "%d", &example);
    fscanf(fp_input, "%c", &ex2);
    fscanf(fp_input, "%d", &example);
#endif





    return 0;
}

