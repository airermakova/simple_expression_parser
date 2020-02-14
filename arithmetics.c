
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <algorithm> 
#include <iostream>
#include <string>
using namespace std;  

// Global Variables
char symbols[7]={ '(',')','*','+','/','-', ' '};


// Function Declarations


//function to execute primitive math operand, 
//such as /,*,+,-
std::string count(std::string& str, char op)
{
    std::size_t pos = str.find(op);
    int f = atoi(str.substr(0, (int)pos).c_str());
    int s = atoi(str.substr(pos+1, str.length()-(pos+1)).c_str());
    int res = 0;
    switch(str[pos])
    {
        case '*' : res = f*s; 
             break;
        case '/' : res = f/s;
             break;   
        case '+' : res = f+s; 
             break;
        case '-' : res = f-s;
             break;  
    }
    std::string resS = std::to_string(res);
    return resS;
}

//Function to calculate single mathematical operand 
//such as *, /, +, - and to print the result into 
//the input string
std::string countSingleOp(const std::string& input, char op)
{
    std::string str = input;  
    std::string ss;
    std::string val;  
    std::size_t pos = str.find(op);
    int stPos=1;
    int len = 3;  
    while(pos!=std::string::npos)
    {
        stPos=1;
        len = 3;
        if(((int)pos-2)>=0 && isdigit(str.at((int)pos-2)))
        {
           stPos = 2;
           len = len+1;
        }
        if(str.length()>pos+2 && isdigit(str.at((int)pos+2)))
           len = len+1;
        ss = str.substr((int)pos-stPos, len);
        val = count(ss, op);    
        str.replace((int)pos-stPos, len, val);
        pos = str.find(op);
    }
    return str;
}

//Following function will calculate expression in case there is no brackets 
std::string countBracket(const std::string& input)
{
    std::string str = countSingleOp(input, '/');  

    std::string str1 = countSingleOp(str, '*');  

    std::string str2 = countSingleOp(str1, '+');   

    std::string str3 = countSingleOp(str2, '-');   
   
    return str3;
}

//Following function will calculate expression inside the brackets
std::string openBracket(std::string& input)
{
    std::string str = input;    
    std::size_t stPos = str.find_last_of("(");
    std::size_t endPos;
    std::string brackets;
    std::string resbrackets;
    while(stPos!=std::string::npos)
    {
        endPos = str.find_first_of(")");
        if(endPos==std::string::npos)
           break;
        brackets = str.substr((int)stPos+1, ((int)endPos) - ((int)stPos+1));
        resbrackets = countBracket(brackets);
        str.replace((int)stPos, ((int)endPos) - ((int)stPos) +1, resbrackets); 
        stPos = str.find_last_of("(");       
    }
    return str;
}

//following parser operates with positive numbers from 0 to 9
//allowed only following symbols ( ) / * + -

bool checkFormula(const std::string& formula)
{
  //brief check of formula
  if(std::count(formula.begin(), formula.end(), '(')!=std::count(formula.begin(), formula.end(), ')'))
  {   
        fprintf(stdout, "Opening and closing bracket number is not equal\n");
        return false;
  }

  for(int i=0; i<formula.length(); i++)
  {
        if(!isdigit(formula[i]))      
            if(std::find(std::begin(symbols), std::end(symbols), formula[i])==std::end(symbols))
            {   
                fprintf(stdout, "Character: %c at place %d is not accepted \n", (char*)formula[i], i+1);
                return false;
            }
        if((i!=formula.length()-1) && isdigit(formula[i])&&isdigit(formula[i+1]))
        {   
            fprintf(stdout, "Value: %c%c is too long, numbers accepted are 0-9\n", (char*)formula[i], (char*)formula[i+1]);
            return false;
        }
   };
   return true;  
}

int main(int argc, char* argv[])
{
  
  fprintf(stdout, "Following parser operates with positive numbers from 0 to 9. \nAllowed only following symbols ( ) / * + - \n");
  fprintf(stdout, "Insert formula:");
  std::string formula;
  std::getline (std::cin,formula);

  // remove all spaces
  std::size_t pos = formula.find(' ');
  while(pos!=std::string::npos)
  {
      formula.erase((int)pos, 1);
      pos = formula.find(' ');
  }
  if(!checkFormula(formula))
  {
      fprintf(stdout, "inserted formula is not correct %s \n", formula.c_str());
      return 1;
  }  
  
  //Count expression inside the brackets
  std::string res = openBracket(formula);
  //Count expression after all brackets have been opened 
  std::string resF = countBracket(res);
  fprintf(stdout, "Counted %s \n", resF.c_str());
  return 0;
}

 
    


