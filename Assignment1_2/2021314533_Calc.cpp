//Student Profile : 2021314533 최민준
//Algorithm Assignment#1
#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <cmath>
//this class stores distinct operand/operator from given input
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
    bool _IsOperand; // true if it is operand
    float _value; // integer value(ASCII value converted to float if operator)
};
//functions
//This function returns the index of certain operator 
//designated with enum OP_index in main function
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
//Simple calculation with two float values and an operator
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
//This function performs calculation of postfix notation
float Calc(std::vector<op> postfix_vector)
{
    if (postfix_vector.size() == 0) { // if there is no operation expression
        return -1.0; //returns -1
    }
    int count = 0;
    std::vector<op>::iterator p_count = postfix_vector.begin(); // iterator of vector(used like pointer)
    //this while loop performs the calculation sequentially
    //until there remains only one value(=result, return value)
    while (postfix_vector.size() > 1) 
    {
        if (p_count->getIsOperand() == false) { // if this op is operator
            (p_count-2)->setValue( SimpleCalc( (p_count - 2)->getValue(),
                (p_count - 1)->getValue(), (p_count)->getValue() ) );
            p_count -= 2;
            postfix_vector.erase(p_count+1);
            p_count = postfix_vector.erase(p_count+1);
        }
        else {
            p_count++; // moves to next op class if previous one was a operand
        }
    }

    float result = postfix_vector.begin()->getValue(); // value to be returned
    return round((result * 100)) * float(0.01);
}

int main(int argc, char** argv)
{
    enum OP_index {
        paren_left = 0, paren_right, multi, division, addition, subtract
    };
    int OP_precedence[6] = {0, 0, 2, 2, 1, 1};
    std::stack<char> Operator_stk; //stores operator data with stack
    std::vector<op> postfix_vtr;   //stores postfix notation converted from input file through lower codes
    //file read
    FILE* fp_input = fopen(argv[1], "r");
    if (fp_input == nullptr) {
        exit(EXIT_FAILURE);
    }

    char scan_char = '\0';
    int scan_int = 0;
    
    while (1)
    {
        fscanf(fp_input, "%c", &scan_char); // reads repetitively and receive at scan_char
        if ( feof(fp_input) ) break; // end of file (file read failed)
        if (scan_char == '\n') continue; // prevents errors resulting from automatic newline addition(vim / echo cmd)

        switch (scan_char)
        {
        case '(':
            Operator_stk.push(scan_char); // '(' should be pushed without any examination
            break;
        case ')':
            while (Operator_stk.top() != '(') // pushes every operator to postfix_vtr
            {
                postfix_vtr.push_back(op(false, Operator_stk.top()));
                Operator_stk.pop();
            }
            Operator_stk.pop(); // delete '(' for convenience
            break;
        case '*':
        case '/':
        case '+':
        case '-':
            if (Operator_stk.size() != 0) {
                //if the incoming operator has lower or same precedence as the latest operator
                if (OP_precedence[CharToIndex(scan_char)] <= OP_precedence[CharToIndex(Operator_stk.top())]) {
                    postfix_vtr.push_back(op(false, Operator_stk.top())); // push the previous operator to postfix first
                    Operator_stk.pop();
                }
            }
            Operator_stk.push(scan_char); // push the operator to Operator_stk
            break;
        default: // this is performed when the input is integer
            fseek(fp_input, -1, SEEK_CUR);
            fscanf(fp_input, "%d", &scan_int);
            postfix_vtr.push_back(op(true, scan_int)); // push directly to postfix
        }
    }
    //move all the remaining operators in operator_stk to postfix
    while (Operator_stk.size() != 0)
    {
        postfix_vtr.push_back(op(false, Operator_stk.top()));
        Operator_stk.pop();
    }
    fclose(fp_input);
    fp_input = nullptr;

    //calculates the postfix notation
    float result = Calc(postfix_vtr);

    //writing the result to output text file(argv[2])
    FILE* fp_output = fopen(argv[2], "w");
    if (fp_output == nullptr) {
        exit(EXIT_FAILURE);
    }
    fprintf(fp_output, "%.2f", result);
    fclose(fp_output);
    fp_output = nullptr;

    return 0;
}

