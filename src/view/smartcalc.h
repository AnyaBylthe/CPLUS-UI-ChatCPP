#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QMainWindow>
#include <QVector>

#include "../controller/controller.h"
#include "../model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc(s21::Controller &controller);
  ~SmartCalc();

 private:
  s21::Controller *controller_;
  Ui::SmartCalc *ui;

 private slots:
  void DigitsNumbers();
  void Dot();
  void Operations();
  void Clear();
  void Brackets();
  void Equal();
  void Graph();
};
#endif  // SMARTCALC_H
