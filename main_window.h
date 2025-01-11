#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include "login_window.h"
#include "signup_window.h"
#include "add_book.h"
#include "research_book.h"
#include "update_book.h"
#include "remove_book.h"
#include "show_books.h"
#include "statistics_window.h"

namespace Ui {
class mainwindow;
}

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow(QString &user_username, QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void on_btn_adicionar_clicked();

    void on_btn_pesquisar_clicked();

    void on_btn_atualizar_clicked();

    void on_btn_remover_clicked();

    void on_btn_ver_estante_clicked();

    void on_btn_sair_clicked();

    void on_btn_estatisticas_clicked();

private:
    Ui::mainwindow *ui;
    QString username;
};

#endif // MAIN_WINDOW_H
