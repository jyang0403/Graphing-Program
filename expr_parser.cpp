#include <functional>
#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include <sstream>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

using std::string;
using std::deque;
using std::stringstream;

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {

}

double eval(double x) {
  return x;
}

//main parse, calls parse_helper for main functionality
Expr *ExprParser::parse(std::istream &in) {
  deque<string> tokens;
  string str;
  getline(in, str);
  stringstream ss(str); 
  string next;
  while (ss >> next) {
    tokens.push_back(next);
  }
  Expr* head = parse_helper(&tokens);
  return head;
}
//removes the front token and returns it
string get_next_token(deque<string> &tokens) { 
  if (tokens.empty()) {
    throw PlotException("Error: Failed to parse expression\n");
  }
  string result = tokens.front();
  tokens.pop_front();
  return result;
}

//checks if given string is a float/literal
bool is_float(string str) {
  //check first digit
  if (!isdigit(str[0]) && str[0] != '-' && str[0] != '.') {
    return false;
  }
  //check last digit
  if (!isdigit(str[str.length() - 1])) {
    return false;
  }
  //if more than one dot, return false
  //process all indices aside from start and end
  int check_dot = 0;
  for (int i = 0; i < (int) str.length(); i++) {
    if (str[i] == '.') {
      if (check_dot > 0) {
        return false;
      }
      check_dot++;
    }
    else if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}
//implementation of parsing from website
Expr* ExprParser::parse_helper(deque<string> * tokens) {
  if (tokens->size() > 0) {
    string next = get_next_token(*tokens);
    // create nodes that can only be leaves and add them
    if (next == "x" || next == "pi" || is_float(next)) {
      Expr * new_exp;
      if (next == "x") {
        new_exp = new X();
      }
      else if (next == "pi") {
        new_exp = new Pi();
      }
      else {
        new_exp = new Literal(stod(next));
      }
      return new_exp;
    }
    // create other nodes and add them
    else if (next == "(") {
      next = get_next_token(*tokens);
      if (next != "sin" && next != "cos" && next != "+" && next != "-" && next != "*" && next != "/") {
        throw PlotException("Error: Invalid operation type\n");
      }
      Expr * new_exp;
      if (next == "sin") {
        new_exp = new Sin();
      }
      else if (next == "cos") {
        new_exp = new Cos();
      }
      else if (next == "+") {
        new_exp = new Add();
      }
      else if (next == "-") {
        new_exp = new Subtract();
      }
      else if (next == "*") {
        new_exp = new Multiply();
      }
      else if (next == "/") {
        new_exp = new Divide();
      }
      // continue until end parentheses and remove each of them recursively before continuing
      while (tokens->front() != ")") {
        Expr * arg = parse_helper(tokens);
        new_exp->add_child(arg);
      }
      (*tokens).pop_front();
      return new_exp;
    }
    else {
      throw PlotException("Error: Failed to parse expression\n");
    }
  }
  else {
    throw PlotException("Error: Failed to parse expression\n");
  }
}