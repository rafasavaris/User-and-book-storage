#ifndef SIGNUP_WINDOW_H
#define SIGNUP_WINDOW_H

#include <QDialog>
#include "login_window.h"
#include "main_window.h"

namespace Ui {
class singupwindow;
}

class singupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit singupwindow(QWidget *parent = nullptr);
    ~singupwindow();

private slots:
    void on_btn_cadastro_clicked();

    void on_btn_voltar_clicked();

private:
    Ui::singupwindow *ui;
};

#endif // SIGNUP_WINDOW_H
