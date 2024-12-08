#include <iostream>
#include <string>
#include "Stack.hpp"

struct Stack_data {
  size_t index;
  char parentheses_type;
}; 

std::string verify_expression(const std::string& expression) {

  Stack<Stack_data> stack;
  std::string result = "";

  for(size_t i = 0; i < expression.length(); i++) {
    if(expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
      stack.push({i, expression[i]});
    } else if(expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
      if(stack.isEmpty()) {
        result += "Parentesi chiusa " + std::string(1, expression[i]) + " mai aperta in posizione " + std::to_string(i) + "\n";
        continue;
      } 

      if((expression[i] == ')' && stack.top().parentheses_type != '(') ||
         (expression[i] == ']' && stack.top().parentheses_type != '[') ||
         (expression[i] == '}' && stack.top().parentheses_type != '{')) {
            result += "Parentesi " + std::string(1, expression[i]) + " non corrispondente alla parentesi aperta in posizione " + std::to_string(stack.top().index) + "\n";
            stack.pop();
      } else 
          stack.pop();
    }
  }

  while(!stack.isEmpty()) {
    result += "Parentesi aperta " + std::string(1, stack.top().parentheses_type) + " mai chiusa in posizione " + std::to_string(stack.top().index) + "\n";
    stack.pop();
  }

  return result.empty() ? "Espressione corretta\n" : result;
}

int main(void) {
    //array of some expression example for trying the code
    std::string expressions[] = {
        "{[()]} + 3 * (5 - 2)",
        "{[(()]})",      
        "(3 + 2) * {5 - (2 + 3)}", 
        "(3 + 2 * {5 - (2 + 3)}",
        "(3 + 2) * 5 + {3 * [4 + 2]}", 
        "{[}]"          
    };

    for (const auto& expression : expressions) {
        std::cout << "Verifica per l'espressione: " << expression << std::endl;
        std::cout << verify_expression(expression) << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    return 0;
}
