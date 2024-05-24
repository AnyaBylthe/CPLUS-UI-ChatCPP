#ifndef CPP3_SMARTCALC_V2_SRC_S21_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_S21_MODEL_H_

#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

using Operation = struct OperationSigns {
  std::string name;
  int priority;
};

namespace s21 {
class Model {
 public:
  Model() = default;
  ~Model() = default;
  void Calculation(std::string expression, std::string x);
  double GetResult();

  void CalculationGraph(std::string expression, std::string x_min,
                        std::string x_max, std::string y_min,
                        std::string y_max);
  std::vector<double> GetX();
  std::vector<double> GetY();

 private:
  std::string Tracker(std::string expression, std::regex regex,
                      std::smatch match, size_t &index);
  int Priority(std::string buffer);
  void Parser(std::string x, Operation last_buffer);
  void CalculationStack();
  void ClearStack();
  void CheckBrackets(std::string expression);
  void CheckX(std::string &x);
  void Control(Operation last_buffer);
  void LastSymbol(std::string expression);
  void CheckGraph(std::string x_min, std::string x_max, std::string y_min,
                  std::string y_max);
  void ClearGraph();
  double result_;
  std::stack<Operation> stack_sign_;
  std::stack<double> stack_numbers_;
  Operation buffer_;
  std::vector<double> x_;
  std::vector<double> y_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_S21_MODEL_H_
