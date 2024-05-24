#include <gtest/gtest.h>

#include "../model/model.h"

TEST(ModelCalcTest, Calculation1) {
  std::string str = "5+7*2/(2-6)^3";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 4.78125);
}

TEST(ModelCalcTest, Calculation2) {
  std::string str = "2+5+7+9*3*2^5";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 878);
}

TEST(ModelCalcTest, Calculation3) {
  std::string str = "123.456+5*4^3";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 443.456);
}

TEST(ModelCalcTest, Calculation4) {
  std::string str = "(8+2*5)/(1+3*2-4)";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 6);
}
TEST(ModelCalcTest, Calculation5) {
  std::string str =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 10);
}
TEST(ModelCalcTest, Calculation6) {
  std::string str = "cos(1*2)-1";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), -1.4161468365471424);
}

TEST(ModelCalcTest, Calculation7) {
  std::string str =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), -1.8390715290764525);
}

TEST(ModelCalcTest, Calculation8) {
  std::string str = "sin(cos(5))";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_NEAR(result.GetResult(), 0.27987335076, 1e-06);
}

TEST(ModelCalcTest, Calculation9) {
  std::string str = "2.33mod1";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 0.33);
}

TEST(ModelCalcTest, Calculation10) {
  std::string str = "3+4*2/1-5+2^2";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 10);
}

TEST(ModelCalcTest, Calculation11) {
  std::string x = "0.0003";
  std::string str = "asin(2*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 0.0006, 1e-06);
}

TEST(ModelCalcTest, Calculation12) {
  std::string x = "0.0019";
  std::string str = "acos(2*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 1.567, 1e-05);
}

TEST(ModelCalcTest, Calculation13) {
  std::string x = "0.0019";
  std::string str = "atan(2*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 0.00379998, 1e-06);
}

TEST(ModelCalcTest, Calculation14) {
  std::string x = "0.004";
  std::string str = "tan(2*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 0.00800017, 1e-06);
}

TEST(ModelCalcTest, Calculation15) {
  std::string x = "25";
  std::string str = "sqrt(2*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 7.07107, 1e-05);
}

TEST(ModelCalcTest, Calculation16) {
  std::string x = "2";
  std::string str = "ln(10*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 2.99573, 1e-05);
}

TEST(ModelCalcTest, Calculation17) {
  std::string x = "2";
  std::string str = "log(10*x)";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_NEAR(result.GetResult(), 1.30103, 1e-06);
}

TEST(ModelCalcTest, Calculation18) {
  std::string str = "-5-(-3)";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), -2);
}

TEST(ModelCalcTest, Calculation19) {
  std::string str = "-3/(-3)";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 1);
}

TEST(ModelCalcTest, Calculation20) {
  std::string str = "5.23e12+4.26e13";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 47830000000000);
}

TEST(ModelCalcTest, Calculation21) {
  std::string str = "25e-21*2";
  s21::Model result;
  result.Calculation(str, "0");
  EXPECT_DOUBLE_EQ(result.GetResult(), 5e-20);
}

TEST(ModelCalcTest, Calculation22) {
  std::string str = "x";
  std::string x = "13.6";
  s21::Model result;
  result.Calculation(str, x);
  EXPECT_DOUBLE_EQ(result.GetResult(), 13.6);
}

TEST(CalculationError, Test_1) {
  std::string number_x = "qew";
  std::string expression = "tan(x)";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_2) {
  std::string number_x = "2e2222";
  std::string expression = "tan(x)";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_3) {
  std::string number_x = "";
  std::string expression = "2e22222";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_4) {
  std::string number_x = "323";
  std::string expression = ")(";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_5) {
  std::string number_x = "323";
  std::string expression = "qwe";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_6) {
  std::string number_x = "323";
  std::string expression = "cos()";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_7) {
  std::string number_x = "323";
  std::string expression = "6^cos5";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_8) {
  std::string number_x = "323";
  std::string expression = "(9x";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_9) {
  std::string number_x = "323";
  std::string expression = "+-5-6";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_10) {
  std::string number_x = "323";
  std::string expression = "5^";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_11) {
  std::string number_x = "323";
  std::string expression = "mod5";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_12) {
  std::string number_x = "323";
  std::string expression = "5(sin(5))";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_13) {
  std::string number_x = "323";
  std::string expression = "6sin(q)";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationError, Test_14) {
  std::string number_x = "323";
  std::string expression = "6+(7)233-2334";
  s21::Model result;
  EXPECT_ANY_THROW(result.Calculation(expression, number_x));
}

TEST(CalculationGraph, Test_1) {
  std::string number_x = "";
  std::string expression = "sin(x)";
  s21::Model result;
  std::string x_min = "-5", x_max = "5";
  std::string y_min = "-5", y_max = "5";
  result.CalculationGraph(expression, x_min, x_max, y_min, y_max);
  std::vector x_axis = result.GetX();
  std::vector y_axis = result.GetY();
  EXPECT_EQ(expression, "sin(x)");
}

TEST(CalculationGraphError, Test_1) {
  std::string number_x = "";
  std::string expression = "sin(x)";
  s21::Model result;
  std::string x_min = "-50000000", x_max = "5";
  std::string y_min = "-5", y_max = "5";
  EXPECT_ANY_THROW(
      result.CalculationGraph(expression, x_min, x_max, y_min, y_max));
}

TEST(CalculationGraphError, Test_2) {
  std::string number_x = "";
  std::string expression = "sin(x)";
  s21::Model result;
  std::string x_min = "2e2222", x_max = "5";
  std::string y_min = "-5", y_max = "5";
  EXPECT_ANY_THROW(
      result.CalculationGraph(expression, x_min, x_max, y_min, y_max));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
