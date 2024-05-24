#ifndef CPP3_SMARTCALC_V2_SRC_S21_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_S21_CONTROLLER_H_

#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include <vector>

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model& model) : model_(&model){};
  ~Controller() = default;
  void PushExpression(QString expression, QString x) {
    model_->Calculation(expression.toStdString(), x.toStdString());
  }
  double GetAnswer() { return model_->GetResult(); }

  void PushGraph(QString expression, QString x_min, QString x_max,
                 QString y_min, QString y_max) {
    model_->CalculationGraph(expression.toStdString(), x_min.toStdString(),
                             x_max.toStdString(), y_min.toStdString(),
                             y_max.toStdString());
  }

  QVector<double> GetX() { return CopyVector(model_->GetX()); }

  QVector<double> GetY() { return CopyVector(model_->GetY()); }

  QVector<double> CopyVector(std::vector<double> vector) {
    QVector<double> q_vector;
    q_vector.reserve(vector.size());
    for (const auto& item : vector) q_vector.append(item);
    return q_vector;
  }

 private:
  Model* model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_S21_CONTROLLER_H_
