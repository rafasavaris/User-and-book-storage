#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QDialog>
#include "login_window.h"

namespace Ui {
class add_book;
}

class add_book : public QDialog
{
    Q_OBJECT

public:
    explicit add_book(int &id, QWidget *parent = nullptr);
    ~add_book();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_adicionar_clicked();

private:
    Ui::add_book *ui;
    int id_usuario;
};

#endif // ADD_BOOK_H
