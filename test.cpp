#include <iostream>
#include <string>
#include "expr.h"
#include "expr_parser.h"
using std::iostream;
using std::string;
using std::cout;

int main() {
  int a = 7, b = 5;int &c = a;int &d = b;c = d;d = 8;
  cout << a;
  return 0;
}
