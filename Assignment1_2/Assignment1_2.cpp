#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
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
    op(bool IsOperand, float value)
    {
        _IsOperand = IsOperand;
        _value = value;
    }
    float getValue() { return _value; }
    bool getIsOperand() { return _IsOperand; }
    void setValue(float temp_f) { _value = temp_f; }
    void setIsOperand(bool temp_b) { _IsOperand = temp_b; }
private:
    bool _IsOperand;
    float _value;
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
float SimpleCalc(float left, float right, int Op_Char)
{
    if (Op_Char == '+') {
        return (left + right);
    }
    else if (Op_Char == '-') {
        return (left - right);
    }
    else if (Op_Char == '*') {
        return (left * right);
    }
    else if (Op_Char == '/') {
        return (left / right);
    }
    else return -1.0;
}

float Calc(std::vector<op> postfix_stack)
{
    if (postfix_stack.size() == 0) {
        return -1.0;
    }
    int count = 0;
    std::vector<op>::iterator p_count = postfix_stack.begin();
    while (postfix_stack.size() > 1)
    {
#if 0
        if (postfix_stack[count].getIsOperand() == false) { // if this op is operator
            postfix_stack[count - 2].setValue( SimpleCalc( postfix_stack[count-2].getValue(), 
                postfix_stack[count - 1].getValue(), postfix_stack[count].getValue() ) );
            postfix_stack.erase(count);
            postfix_stack.erase(count - 1);
            count--;
        }
#endif
        if (p_count->getIsOperand() == false) { // if this op is operator
            (p_count-2)->setValue( SimpleCalc( (p_count - 2)->getValue(),
                (p_count - 1)->getValue(), (p_count)->getValue() ) );
            p_count -= 2;
            postfix_stack.erase(p_count+1);
            p_count = postfix_stack.erase(p_count+1);
        }
        else {
            p_count++;
        }

    }

    float result = postfix_stack.begin()->getValue(); //return value
    return round((result * 100)) * float(0.01);
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
    std::vector<op> postfix_stk;
    //file read
    FILE* fp_input = fopen(argv[1], "r");
    if (fp_input == nullptr) {
        exit(EXIT_FAILURE);
    }

    //std::string postfix_string = "";
    char scan_char = '\0';
    int scan_int = 0;
    
    while (1)
    {
        fscanf(fp_input, "%c", &scan_char);
        if (feof(fp_input)) break; // end of file (file read failed)
        switch (scan_char)
        {
        case '(':
            Operator_stk.push(scan_char);
            break;
        case ')':
            while (Operator_stk.top() != '(')
            {
                postfix_stk.push_back(op(false, Operator_stk.top()));
                Operator_stk.pop();
            }
            Operator_stk.pop();
            break;
        case '*':
        case '/':
        case '+':
        case '-':
            if (Operator_stk.size() != 0) {
                //if the incoming operator has lower or same precedence as the latest operator
                if (OP_precedence[CharToIndex(scan_char)] <= OP_precedence[CharToIndex(Operator_stk.top())]) {
                    postfix_stk.push_back(op(false, Operator_stk.top()));
                    Operator_stk.pop();
                }
            }
            Operator_stk.push(scan_char);
            break;
        default:
            fseek(fp_input, -1, SEEK_CUR);
            fscanf(fp_input, "%d", &scan_int);
            postfix_stk.push_back(op(true, scan_int));
            //postfix_string.append(std::to_string(scan_int));
        }
    }
    //move all the remaining operators in operator_stk
    while (Operator_stk.size() != 0)
    {
        postfix_stk.push_back(op(false, Operator_stk.top()));
        Operator_stk.pop();
    }
    fclose(fp_input);
    fp_input = nullptr;
#if 1

#endif
#if 1
    float result = Calc(postfix_stk);
    printf("The output is : %.2f\n", result);
#endif
    //writing the result to output text file(argv[2])
    FILE* fp_output = fopen(argv[2], "w");
    if (fp_output == nullptr) {
        exit(EXIT_FAILURE);
    }
    fprintf(fp_output, "%.2f", result);
    fclose(fp_output);
    fp_output = nullptr;
#if 0
    int example = 0;
    char ex2 = '\0';
    fscanf(fp_input, "%d", &example);
    fscanf(fp_input, "%c", &ex2);
    fscanf(fp_input, "%d", &example);
#endif


    return 0;
}

