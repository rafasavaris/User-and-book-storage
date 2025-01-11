#ifndef RESEARCH_BOOK_H
#define RESEARCH_BOOK_H

#include <QDialog>
#include "login_window.h"

namespace Ui {
class research_book;
}

class research_book : public QDialog
{
    Q_OBJECT

public:
    explicit research_book(int &id, QWidget *parent = nullptr);
    ~research_book();

private slots:
    void on_btn_pesquisar_clicked();

    void on_btn_voltar_clicked();

private:
    Ui::research_book *ui;
    int id_usuario;
};

#endif // RESEARCH_BOOK_H
