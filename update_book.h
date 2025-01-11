#ifndef UPDATE_BOOK_H
#define UPDATE_BOOK_H

#include <QDialog>

namespace Ui {
class update_book;
}

class update_book : public QDialog
{
    Q_OBJECT

public:
    explicit update_book(int &id, QWidget *parent = nullptr);
    ~update_book();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_atualizar_clicked();

    void on_btn_pesquisar_clicked();

private:
    Ui::update_book *ui;
    int id_usuario;
};

#endif // UPDATE_BOOK_H
