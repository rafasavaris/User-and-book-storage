#ifndef STATISTICS_WINDOW_H
#define STATISTICS_WINDOW_H

#include <QDialog>
#include "login_window.h"
#include "livro.h"

namespace Ui {
class statistics_window;
}

class statistics_window : public QDialog
{
    Q_OBJECT

public:
    explicit statistics_window(int &id, QWidget *parent = nullptr);
    ~statistics_window();

private slots:
    void on_btn_voltar_clicked();
    // métodos utilizados
    // retorna a quantidade de livros totais
    QString qntd_livros();
    // retorna quantos livros foram finalizados
    QString qntd_livros_finalizados();
    // retorna o número de páginas lidas
    QString num_paginas_lidas();
    // retorna o maior livro (conta pelo número de páginas
    QString maior_livro();

private:
    Ui::statistics_window *ui;
    int id_usuario;
};

#endif // STATISTICS_WINDOW_H
