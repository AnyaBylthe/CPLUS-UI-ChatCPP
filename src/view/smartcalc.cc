#include "smartcalc.h"

#include "ui_smartcalc.h"

double num_first;

SmartCalc::SmartCalc(s21::Controller &controller)
    : controller_(&controller), ui(new Ui::SmartCalc) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(Equal()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(Graph()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(Brackets()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(Brackets()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(Dot()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(Clear()));

  connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(Operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(Operations()));
}

SmartCalc::~SmartCalc() { delete ui; }

void SmartCalc::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "1")
    ui->result_show->setText(ui->result_show->text() + '1');
  else if (button->text() == "2")
    ui->result_show->setText(ui->result_show->text() + '2');
  else if (button->text() == "3")
    ui->result_show->setText(ui->result_show->text() + '3');
  else if (button->text() == "4")
    ui->result_show->setText(ui->result_show->text() + '4');
  else if (button->text() == "5")
    ui->result_show->setText(ui->result_show->text() + '5');
  else if (button->text() == "6")
    ui->result_show->setText(ui->result_show->text() + '6');
  else if (button->text() == "7")
    ui->result_show->setText(ui->result_show->text() + '7');
  else if (button->text() == "8")
    ui->result_show->setText(ui->result_show->text() + '8');
  else if (button->text() == "9")
    ui->result_show->setText(ui->result_show->text() + '9');
  else if (button->text() == "0")
    ui->result_show->setText(ui->result_show->text() + '0');
  else if (button->text() == "x")
    ui->result_show->setText(ui->result_show->text() + 'x');
  else if (button->text() == "e")
    ui->result_show->setText(ui->result_show->text() + 'e');
}

void SmartCalc::Brackets() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "(")
    ui->result_show->setText(ui->result_show->text() + '(');
  else if (button->text() == ")")
    ui->result_show->setText(ui->result_show->text() + ')');
}

void SmartCalc::Dot() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == ".")
    ui->result_show->setText(ui->result_show->text() + '.');
}

void SmartCalc::Operations() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "+")
    ui->result_show->setText(ui->result_show->text() + '+');
  else if (button->text() == "-")
    ui->result_show->setText(ui->result_show->text() + '-');
  else if (button->text() == "*")
    ui->result_show->setText(ui->result_show->text() + '*');
  else if (button->text() == "/")
    ui->result_show->setText(ui->result_show->text() + '/');
  else if (button->text() == "^")
    ui->result_show->setText(ui->result_show->text() + '^');
  else if (button->text() == "mod")
    ui->result_show->setText(ui->result_show->text() + "mod");
  else if (button->text() == "sin")
    ui->result_show->setText(ui->result_show->text() + "sin(");
  else if (button->text() == "cos")
    ui->result_show->setText(ui->result_show->text() + "cos(");
  else if (button->text() == "tan")
    ui->result_show->setText(ui->result_show->text() + "tan(");
  else if (button->text() == "log")
    ui->result_show->setText(ui->result_show->text() + "log(");
  else if (button->text() == "ln")
    ui->result_show->setText(ui->result_show->text() + "ln(");
  else if (button->text() == "asin")
    ui->result_show->setText(ui->result_show->text() + "asin(");
  else if (button->text() == "acos")
    ui->result_show->setText(ui->result_show->text() + "acos(");
  else if (button->text() == "atan")
    ui->result_show->setText(ui->result_show->text() + "atan(");
  else if (button->text() == "sqrt")
    ui->result_show->setText(ui->result_show->text() + "sqrt(");
}

void SmartCalc::Clear() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "AC") ui->result_show->setText("");
}

void SmartCalc::Equal() {
  try {
    controller_->PushExpression(ui->result_show->text(), ui->result_x->text());
    ui->result_show->setText(
        QString::number(controller_->GetAnswer(), 'g', 15));
  } catch (const std::invalid_argument &e) {
    ui->result_show->setText(e.what());
  }
}

void SmartCalc::Graph() {
  try {
    controller_->PushGraph(ui->result_show->text(), ui->res_x_min->text(),
                           ui->res_x_max->text(), ui->res_y_min->text(),
                           ui->res_y_max->text());
    ui->widget->clearGraphs();
    ui->widget->xAxis->setRange(ui->res_x_min->text().toDouble(),
                                ui->res_x_max->text().toDouble());
    ui->widget->yAxis->setRange(ui->res_y_min->text().toDouble(),
                                ui->res_y_max->text().toDouble());
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(controller_->GetX(), controller_->GetY());
    ui->widget->graph(0)->setPen(QPen(QColor(0, 77, 255)));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 0.8));
    ui->widget->replot();
  } catch (const std::invalid_argument &e) {
    ui->result_show->setText(e.what());
  }
}
