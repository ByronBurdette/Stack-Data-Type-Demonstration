
// Byron Burdette
// COP2535.0M1



/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
                                                CLASS SPECIFICATION FILE FOR THE CLASS rpnCalculator
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/





/**********************************************                     PREPROCESSOR DIRECTIVES                **************************************************/
#pragma once                                                    //  include guard ensures this file is included, but only once

#include<iostream>                                              //  includes the library for standard I/O stream objects
#include<fstream>                                               //  includes the library for file stream objects
#include<stack>                                                 //  includes the library for the stack container
#include<vector>                                                //  includes the library for vectors
#include<string>                                                //  includes the library for string types
#include<sstream>                                               //  includes the library for string stream objects
#include<iomanip>                                               //  includes the library for I/O manipulation
/*********************************************************************************************************************************************************/



using namespace std;                                            //  lifts all entities in the standard namespace into the current global namespace






class rpnCalculator                                             //  begin class declaration
{
private:
    stack< int > expression;                                    //  declares a stack of integers "expression". We use this to keep track of the order of operations for our expresssions
    ifstream inFile;                                            //  declare an input file stream object. This is what we'll use to read from the file containing the expressions
    vector<int> answers;                                        //  declare a vector if integers "answers" to store all the answers to the different expressions
    int length = 0;                                             //  declare and integer "length" to store the length of the longest expression encountered. We'll be using this to assist in formatting the output

public:
    rpnCalculator();                                            //  prototype for the constructor. We'll use this to open the file, and make sure it was opened correctly
    void welcomeMessage();                                      //  prototype for function that simply displays the purpose of the program for the user
    void evaluateExpressions();                                 //  prototype for function that reads each expression and uses the stack to keep track of the order of operations in the expression
    void calculateExpression(char);                             //  prototype for function that performs the operation represented by the char parameter on the top two values in the stack
    void displayResults();                                      //  prototype for function that displays the results of each expression
};

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
                                                THIS MARKS THE END OF THE CLASS SPECIFICATION FILE
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/