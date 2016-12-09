
// Byron Burdette
// COP2535.0M1



/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
                                            MEMBER FUNCTION DEFINITIONS FOR THE CLASS rpnCalculator
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/





#include"rpnCalculator.h"                                                       //  include class specification file




/*********************************************************************************************************************************************************
                                                    THIS MARKS THE BEGINNING OF THE CONSTRUCTOR

                the purpose of this function is to open the input file and the terminate the program if the file could not be opened
**********************************************************************************************************************************************************/
rpnCalculator::rpnCalculator()                                                  //  begin function definition
{
    inFile.open("postfix.txt");                                                 //  open our input file
    if (!inFile)                                                                //  if the file couldn't be opened...
    {
        cout << "Error. Cannot open file. Terminating program . . .";           //  display an error message
        cout << endl << endl;                                                   //  whitespace formatting
        system("pause");                                                        //  pause the system before terminating so the user can read the error
        exit(555);                                                              //  terminate the system with an error
    }
}
/*********************************************************************************************************************************************************
                                                    THIS MARKS THE END OF THE CONSTRUCTOR
**********************************************************************************************************************************************************/










/*********************************************************************************************************************************************************
                                                THIS MARKS THE BEGINNING OF THE "welcomeMessage" FUNCTION

                                    the purpose of this function is to display the purpose of the program for the user
**********************************************************************************************************************************************************/
void rpnCalculator::welcomeMessage()                                                                         //  begin function definition
{
    cout << setfill('*') << setw(79) << '*' << endl;                                                         //  introductory message
    cout << "*    The purpose of this program is to demonstrate an appropriate use of a    *" << endl        //  more message
        << "*    stack. I was provided with a file containing mathematical expressions    *" << endl         //  some more message
        << "*    written in postfix notation. This program evaluates the expressions      *" << endl         //  even more message
        << "*    with the aid of a stack.                                                 *" << endl;        //  a little more message
    cout << setfill('*') << setw(79) << '*' << endl << endl;                                                 //  some formatting, and we're done
}                                                                                                            //  end function definition
/*********************************************************************************************************************************************************
                                                THIS MARKS THE END OF THE "welcomeMessage" FUNCTION
**********************************************************************************************************************************************************/








/*********************************************************************************************************************************************************
                                            THIS MARKS THE BEGINNING OF THE "evaluateExpressions" FUNCTION

the purpose of this function is to go through the file lin-by-line, evaluating each expression. It accomplishes this by turning an expression into an
input stream and then reading each part of the expression. When it finds a number, it puts it on the stack. When it finds an operator, it sends the
operator over to the function "calculateExpression" which can then pop the top two values off the stack and use the operator to perform a calculation.
Then it sticks the result onto the stack. By the time we reach the end of the input stream, we will have evaluated the expression, so we store whatever's
left on the stack inside our vector "answers" and pop the stack to clean it off for the next expression.
**********************************************************************************************************************************************************/
void rpnCalculator::evaluateExpressions()                       //  begin function definition
{
    string expr;                                                //  declare a string "expr" to store the entire expression

    while (getline(inFile, expr))                               //  while there are still expressions to evaluate, store the next expression in "expr"
    {
        if (expr.length() > length)                             //  if the current expression is the longest expression encountered...
            length = expr.length();                             //  then store the length of the expression

        stringstream ss(expr);                                  //  create an input stream "ss" out of the current expression so we can evaluate each individual part
        string str;                                             //  create a string "str" that we'll use to store one individual part of the expression for evaluation

        while (ss >> str)                                       //  for each piece of the expression...
        {
            try                                                 //  first, we check if it's a number
            { expression.push(stoi(str)); }                     //  try to convert it to a number an put it on the stack
            catch (exception e)                                 //  if an exception occured, then we must have an operator
            {
                char ch = str[0];                               //  store the operator as a char so we can use it in a switch statement in our calcuating function
                calculateExpression(ch);                        //  perform the calculation using this operator and the top two values in the stack. Remove the top to values on the stack, and store the resulting calculation on the stack
            }
        }                                                       //  end of the loop.

        answers.push_back(expression.top());                    //  there's nothing else in this expression, so we store the result left on the stack inside our vector "answers"
        expression.pop();                                       //  and we pop the result off the stack to prime the stack for the next expression
    }                                                           //  end loop
}                                                               //  end function definition
/*********************************************************************************************************************************************************
                                                    THIS MARKS THE END OF THE "evaluateExpressions" FUNCTION
**********************************************************************************************************************************************************/










/*********************************************************************************************************************************************************
                                    THIS MARKS THE BEGINNING OF THE "calculateExpression" FUNCTION

the purpose of this function is to use the operator recently identified in the expression for a calculation using the top two values on the stack. Once
an operator is identified in the function "evaluateExpressions", the operator is passed to this function. This function stores the top two values on the stack
and removes them both from the stack. This function then performs the calculation and stores the result on the stack
**********************************************************************************************************************************************************/
void rpnCalculator::calculateExpression(char sign)              //  begin function definition
{
    int ans;                                                    //  create a variable to store the result of the calculation
    int operand2 = expression.top();                            //  store the second operand for calculation
    expression.pop();                                           //  remove the second operand from the stack
    int operand1 = expression.top();                            //  store the first operand for calculation
    expression.pop();                                           //  remove the first operand from the stack

    switch (sign)                                               //  begin switch statement for the different operators
    {
    case '+':                                                   //  if we're performing addition...
        ans = operand1 + operand2;                              //  sum the two operands
        break;
    case '-':                                                   //  if we're performing subtraction...
        ans = operand1 - operand2;                              //  subtract the second operand from the first
        break;
    case '*':                                                   //  if we performing multiplication...
        ans = operand1 * operand2;                              //  multiply the two operands
        break;
    case '/':                                                   //  if we're performing division
        ans = operand1 / operand2;                              //  divide the first operand by the second
        break;
    }                                                           //  end switch statement

    expression.push(ans);                                       //  store the result on the stack
}                                                               //  end function definition
/*********************************************************************************************************************************************************
                                            THIS MARKS THE END OF THE "calculateExpression" FUNCTION
**********************************************************************************************************************************************************/







/*********************************************************************************************************************************************************
                                                THIS MARKS THE BEGINNING OF THE "displayResults" FUNCTION

                            the purpose of this function is to neatly display each expression followed by its result
**********************************************************************************************************************************************************/
void rpnCalculator::displayResults()                            //  begin function definition
{
    inFile.clear();                                             //  clear the EOF flag on the input file so we can display the file
    inFile.seekg(0);                                            //  set the position of the next character to be extracted from the input file back the the beginning of the file
    string str;                                                 //  create a string to hold each expression
    int count = 0;                                              //  a counter for accessing the vector filled with answers to the expressions

    cout << setw(length+1) << setfill(' ') << "Expression";     //  formatting and displaying headers
    cout << "     " << "Result" << endl << endl;                //  more headers

    while (getline(inFile, str))                                //  for each expression...
    {
        cout << ' ' << setw(length) << setfill(' ') << str << "       " << answers[count] << endl;      //  display the expression followed by its result
        count++;                                                                                        //  increment the counter to keep track of which answer to display
    }

    cout << endl << endl << endl;                                                                       //  newline formatting
}                                                                                                       //  end function definition
/*********************************************************************************************************************************************************
                                                    THIS MARKS THE END OF THE "displayResults" FUNCTION
**********************************************************************************************************************************************************/



/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
                                                THIS MARKS THE END OF THE MEMBER FUNCTION DEFINITIONS
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/