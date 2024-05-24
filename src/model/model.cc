#include "model.h"

namespace s21 {
void Model::Calculation(std::string expression, std::string x) {
  Operation last_buffer = {"", 0};
  std::regex regex(R"((\d+(\.\d+)?)([eE][+-]?\d+)?|[+\-*/\^\(\)]|(mod)|(\w+))");
  std::smatch match;
  ClearStack();
  CheckX(x);
  CheckBrackets(expression);
  LastSymbol(expression);
  for (size_t index = 0; index < expression.size();) {
    buffer_.name = Tracker(expression, regex, match, index);
    buffer_.priority = Priority(buffer_.name);
    Control(last_buffer);
    Parser(x, last_buffer);
    last_buffer = buffer_;
    if (index == expression.size()) {
      while (!stack_sign_.empty()) CalculationStack();
      result_ = stack_numbers_.top();
    }
  }
}

std::string Model::Tracker(std::string expression, std::regex regex,
                           std::smatch match, size_t &index) {
  std::sregex_iterator iter(expression.begin() + index, expression.end(),
                            regex);
  match = *iter;
  index += match.length();
  return match.str();
}

double Model::GetResult() { return result_; }

int Model::Priority(std::string buffer) {
  int priority = 0;
  try {
    std::stod(buffer);
    priority = 7;
  } catch (const std::invalid_argument &e) {
    if (buffer == "(") {
      priority = 1;
    } else if (buffer == "+" || buffer == "-") {
      priority = 2;
    } else if (buffer == "*" || buffer == "/") {
      priority = 3;
    } else if (buffer == "^") {
      priority = 4;
    } else if (buffer == "sin" || buffer == "cos" || buffer == "tan" ||
               buffer == "asin" || buffer == "acos" || buffer == "atan" ||
               buffer == "sqrt" || buffer == "ln" || buffer == "log" ||
               buffer == "mod") {
      priority = 5;
    } else if (buffer == ")") {
      priority = 6;
    } else if (buffer == "x") {
      priority = 8;
    } else {
      priority = 0;
    }
  } catch (const std::out_of_range &e) {
    priority = 0;
  }
  return priority;
}

void Model::Parser(std::string x, Operation last_buffer) {
  Operation tmp = {"", 0};
  if (!stack_sign_.empty()) {
    tmp = stack_sign_.top();
  }
  if (buffer_.priority == 7) {
    stack_numbers_.push(std::stod(buffer_.name));
  } else if (buffer_.priority == 8) {
    stack_numbers_.push(std::stod(x));
  } else if (buffer_.priority == 1) {
    stack_sign_.push(buffer_);
  } else if (buffer_.priority < 6) {
    if (((buffer_.name == "-" || buffer_.name == "+") &&
         stack_numbers_.empty()) ||
        ((buffer_.name == "-" || buffer_.name == "+") && tmp.name == "(" &&
         last_buffer.priority != 7 && last_buffer.priority != 8))
      stack_numbers_.push(0);
    if (buffer_.priority <= tmp.priority &&
        (buffer_.priority != 4 || tmp.priority != 4)) {
      while (!stack_sign_.empty()) {
        if (buffer_.priority > tmp.priority) break;
        CalculationStack();
        if (!stack_sign_.empty()) tmp = stack_sign_.top();
      }
    }
    stack_sign_.push(buffer_);
  } else if (buffer_.priority == 6) {
    while (tmp.priority != 1) {
      CalculationStack();
      if (!stack_sign_.empty()) tmp = stack_sign_.top();
    }
    stack_sign_.pop();
  }
}

void Model::CalculationStack() {
  Operation tmp = stack_sign_.top();

  double a = 0, b = 0, c = 0;
  if (tmp.name == "+" || tmp.name == "-" || tmp.name == "*" ||
      tmp.name == "/" || tmp.name == "^" || tmp.name == "mod") {
    b = stack_numbers_.top();
    stack_numbers_.pop();
  }
  a = stack_numbers_.top();
  stack_numbers_.pop();
  if (tmp.name == "+")
    c = a + b;
  else if (tmp.name == "-")
    c = a - b;
  else if (tmp.name == "*")
    c = a * b;
  else if (tmp.name == "/")
    c = a / b;
  else if (tmp.name == "^")
    c = pow(a, b);
  else if (tmp.name == "sin")
    c = sin(a);
  else if (tmp.name == "cos")
    c = cos(a);
  else if (tmp.name == "tan")
    c = tan(a);
  else if (tmp.name == "log")
    c = log10(a);
  else if (tmp.name == "ln")
    c = log(a);
  else if (tmp.name == "asin")
    c = asin(a);
  else if (tmp.name == "acos")
    c = acos(a);
  else if (tmp.name == "atan")
    c = atan(a);
  else if (tmp.name == "sqrt")
    c = sqrt(a);
  else if (tmp.name == "mod")
    c = fmodl(a, b);
  stack_numbers_.push(c);
  stack_sign_.pop();
}

void Model::ClearStack() {
  while (!stack_numbers_.empty()) stack_numbers_.pop();
  while (!stack_sign_.empty()) stack_sign_.pop();
  result_ = 0;
  buffer_.name = "";
  buffer_.priority = 0;
}

void Model::CheckBrackets(std::string expression) {
  int bracket = 0;
  for (size_t index = 0; index < expression.size(); ++index) {
    if (expression[index] == '(')
      ++bracket;
    else if (expression[index] == ')')
      --bracket;
  }
  if (bracket != 0) throw std::invalid_argument("ERROR: Input Error");
}

void Model::CheckX(std::string &x) {
  x = (x == "") ? "1" : x;
  try {
    std::stod(x);
  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument("ERROR: X is Invalid Argument");
  } catch (const std::out_of_range &e) {
    throw std::invalid_argument("ERROR: X is Out Of Range");
  }
}

void Model::Control(Operation last_buffer) {
  if (buffer_.priority == 0) {
    throw std::invalid_argument("ERROR: Input Error");
  } else if (buffer_.priority == 1) {
    if (last_buffer.priority >= 6 && last_buffer.priority <= 8) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  } else if (buffer_.priority == 2) {
    if (last_buffer.priority != 0 && last_buffer.priority != 1 &&
        last_buffer.priority != 6 && last_buffer.priority != 7 &&
        last_buffer.priority != 8) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  } else if (buffer_.name == "mod" || buffer_.priority == 3 ||
             buffer_.priority == 4) {
    if (last_buffer.priority < 6) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  } else if (buffer_.priority == 5) {
    if (last_buffer.priority >= 5) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  } else if (buffer_.priority == 6) {
    if (last_buffer.priority < 6) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  } else if (buffer_.priority == 7 || buffer_.priority == 8) {
    if (last_buffer.priority == 6 || last_buffer.priority == 7 ||
        last_buffer.priority == 8 ||
        (last_buffer.priority == 5 && last_buffer.name != "mod")) {
      throw std::invalid_argument("ERROR: Input Error");
    }
  }
}

void Model::LastSymbol(std::string expression) {
  char last_symbol = expression.back();
  try {
    std::stoi(std::string(1, last_symbol));
  } catch (const std::invalid_argument &e) {
    if (last_symbol != 'x' && last_symbol != ')')
      throw std::invalid_argument("ERROR: Input Error");
  }
}

void Model::CalculationGraph(std::string expression, std::string x_min,
                             std::string x_max, std::string y_min,
                             std::string y_max) {
  CheckGraph(x_min, x_max, y_min, y_max);
  ClearGraph();
  double x_minimum = std::stod(x_min);
  double x_maximum = std::stod(x_max);
  double step = (x_maximum - x_minimum) / 1000;
  for (double index = x_minimum; index <= x_maximum; index += step) {
    Calculation(expression, std::to_string(index));
    x_.push_back(index);
    y_.push_back(result_);
  }
}

std::vector<double> Model::GetX() { return x_; }

std::vector<double> Model::GetY() { return y_; }

void Model::CheckGraph(std::string x_min, std::string x_max, std::string y_min,
                       std::string y_max) {
  try {
    double x_minimum = std::stod(x_min);
    double x_maximum = std::stod(x_max);
    double y_minimum = std::stod(y_min);
    double y_maximum = std::stod(y_max);
    if (x_minimum < -1000000 || x_maximum > 1000000 || y_minimum < -1000000 ||
        y_maximum > 1000000 || x_minimum > x_maximum || y_minimum > y_maximum) {
      throw std::invalid_argument("ERROR: Input Graph Error");
    }
  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument("ERROR: Input Graph Error");
  } catch (const std::out_of_range &e) {
    throw std::invalid_argument("ERROR: Input Graph Error");
  }
}

void Model::ClearGraph() {
  if (!x_.empty() && !y_.empty()) {
    x_.clear();
    y_.clear();
  }
}
}  // namespace s21
