#include <QApplication>

#include "smartcalc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(model);
  SmartCalc w(controller);
  w.show();
  return a.exec();
}
