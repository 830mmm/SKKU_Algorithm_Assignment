#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
//operator precedence will be stored using this class
class op_precedence
{
public:
    op_precedence(char name, int prec)
        :op_name(name), precedence(prec)
    {

    }
private:
    char op_name;
    int precedence;
};

int main(int argc, char** argv)
{
    op_precedence paren_left('(', 0);
    op_precedence paren_right(')', 0);
    op_precedence multi('*', 1);
    op_precedence division('/', 1);
    op_precedence addition('+', 2);
    op_precedence subtract('-', 2);
    //stores the operand data and operator data with stack
    std::stack<int> infix_stk;
    std::stack<int> postfix_stk;
    //file read
    FILE* fp_input = fopen("input.txt", "r");
    if (fp_input == nullptr) {
        exit(EXIT_FAILURE);
    }

    std::string postfix_string = "";
    char scan_char = '\0';
    int scan_int = 0;
    fscanf(fp_input, "%c", &scan_char);
#if 0
    printf("before: %c", scan_char);
    fseek(fp_input, -1, SEEK_CUR);
    fscanf(fp_input, "%c", &scan_char);
    printf("after: %c", scan_char);
#endif
    switch (scan_char)
    {
    case '(':

    case ')':

    case '*':

    case '/':

    case '+':

    case '-':

    default:
        fseek(fp_input, -1, SEEK_CUR);
        fscanf(fp_input, "%d", &scan_int);
        postfix_string.append(std::to_string(scan_int));
    }
#if 0
    int example = 0;
    char ex2 = '\0';
    fscanf(fp_input, "%d", &example);
    fscanf(fp_input, "%c", &ex2);
    fscanf(fp_input, "%d", &example);
#endif
    fclose(fp_input);
    fp_input = nullptr;




    return 0;
}

