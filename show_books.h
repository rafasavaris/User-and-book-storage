#ifndef SHOW_BOOKS_H
#define SHOW_BOOKS_H

#include <QDialog>
#include "login_window.h"

namespace Ui {
class show_books;
}

class show_books : public QDialog
{
    Q_OBJECT

public:
    explicit show_books(int &id, QWidget *parent = nullptr);
    ~show_books();

private slots:
    void on_btn_proximo_clicked();

    void on_btn_voltar_clicked();

private:
    Ui::show_books *ui;
    int id_usuario;
    void show_progress_bar(int num_paginas_totais, int num_paginas_lidas);
};

#endif // SHOW_BOOKS_H
