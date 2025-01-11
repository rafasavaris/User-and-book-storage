#ifndef REMOVE_BOOK_H
#define REMOVE_BOOK_H

#include <QDialog>
#include "login_window.h"

namespace Ui {
class remove_book;
}

class remove_book : public QDialog
{
    Q_OBJECT

public:
    explicit remove_book(int &id, QWidget *parent = nullptr);
    ~remove_book();

private slots:
    void on_btn_remover_clicked();

    void on_btn_voltar_clicked();

private:
    Ui::remove_book *ui;
    int id_usuario;
};

#endif // REMOVE_BOOK_H
