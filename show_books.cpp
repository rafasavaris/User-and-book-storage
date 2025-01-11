#include "show_books.h"
#include "ui_show_books.h"
#include "livro_finalizado.h"
#include "livro_lendo.h"
#include "livro_parado.h"

QVector<livro*> livros;
static int index = 0;

show_books::show_books(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::show_books), id_usuario(id)
{
    ui->setupUi(this);
    ui->progresso_leitura->setVisible(false);

    // obtém todos os livros cadastrados pelo usuário e salva no vetor
    QSqlQuery query;
    query.prepare("SELECT TITULO, AUTOR, NUM_PAGINAS, NUM_PAGINAS_LIDAS, STATUS, FORMATO, ID_LIVRO "
                  "FROM banco_livros WHERE ID_USUARIO = :id ORDER BY ID_LIVRO");
    query.bindValue(":id", id_usuario);

    if (query.exec()) {
        while (query.next()) {
            QString titulo = query.value(0).toString();
            QString autor = query.value(1).toString();
            int num_pag_totais = query.value(2).toInt();
            int num_pag_lidas = query.value(3).toInt();
            QString status = query.value(4).toString();
            QString formato = query.value(5).toString();
            int id_livro = query.value(6).toInt();

            if (status == "Parado")
                livros.push_back(new livro_parado(id_livro, titulo, autor, formato, num_pag_totais, num_pag_lidas, status));
            else if (status == "Lendo")
                livros.push_back(new livro_lendo(id_livro, titulo, autor, formato, num_pag_totais, num_pag_lidas, status));
            else
                livros.push_back(new livro_finalizado(id_livro, titulo, autor, formato, num_pag_totais, num_pag_lidas, status));
        }

        if (!livros.isEmpty())
        {
            // se há livros, mostra o primeiro
            ui->txt_resultado->setText(livros.at(0)->mostrar_detalhes());
            show_progress_bar(livros.at(0)->get_numPagTotais(), livros.at(0)->get_numPagLidas());
        }
        else
        {
            // se não há livros, mostra mensagem
            ui->btn_proximo->setVisible(false);
            ui->txt_resultado->setText("Opa! Você não tem livros cadastrados ainda!");
        }
    }
    else
        qDebug() << "Falha ao buscar livros.";
}

show_books::~show_books()
{
    delete ui;
}

void show_books::on_btn_proximo_clicked()
{
    if (index + 1 < livros.size())
    {
        index++;
        ui->txt_resultado->setText(livros.at(index)->mostrar_detalhes());
        show_progress_bar(livros.at(index)->get_numPagTotais(), livros.at(index)->get_numPagLidas());
    }
    else
    {
        ui->txt_resultado->setText("Opa! Não existem outros livros cadastrados");
        ui->btn_proximo->setVisible(false);
        ui->progresso_leitura->setVisible(false);
        index++;
    }
}

void show_books::on_btn_voltar_clicked()
{
    if (index > 0)
    {
        index--;
        ui->txt_resultado->setText(livros.at(index)->mostrar_detalhes());
        show_progress_bar(livros.at(index)->get_numPagTotais(),
                          livros.at(index)->get_numPagLidas());
        ui->btn_proximo->setVisible(true);
    }
    else {
        // se está no primeiro livro, volta para a tela principal
        QSqlQuery query;
        query.prepare("SELECT USERNAME FROM usuarios WHERE ID = :id");
        query.bindValue(":id", id_usuario);
        QString username;
        if(query.exec())
            if(query.next())
                username = query.value(0).toString();
            else
                qDebug() << "Falha ao buscar username.";

        this->close();
        for (size_t i = 0; i < livros.size(); i++)
            delete livros.at(i);

        livros.clear();
        mainwindow *main_window = new mainwindow(username);
        main_window->setModal(true);
        main_window->exec();
    }
}

void show_books::show_progress_bar(int num_paginas_totais, int num_paginas_lidas)
{
    int progresso = (num_paginas_lidas * 100) / num_paginas_totais;
    ui->progresso_leitura->setVisible(true);
    ui->progresso_leitura->setValue(progresso);
}
