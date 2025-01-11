#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <string>
#include <QFile>
#include <QStandardPaths>
#include <Qvector>

#include "main_window.h"
#include "signup_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class loginwindow;
}
QT_END_NAMESPACE

class loginwindow : public QMainWindow
{
    Q_OBJECT

public:
    loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

private slots:
    void on_btn_login_clicked();

    void on_btn_sign_up_clicked();

    void on_btn_sair_clicked();

private:
    Ui::loginwindow *ui;
};
#endif // LOGIN_WINDOW_H
