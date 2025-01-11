#include "statistics_window.h"
#include "ui_statistics_window.h"

statistics_window::statistics_window(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::statistics_window), id_usuario(id)
{
    ui->setupUi(this);

    // busca se há livros cdastrados
    QSqlQuery query;
    query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE ID_USUARIO = :id ORDER BY ID_LIVRO DESC");
    query.bindValue(":id", id_usuario);
    if(query.exec())
    {
        if(query.next())
        {
            // se sim, exibe as estistícas
            ui->txt_resultado->setText("Você tem "+ qntd_livros() + " livros na sua estante!\n" +
                               "E " + qntd_livros_finalizados() + " livro(s) finalizado(s).\n"+
                               "Você leu " + num_paginas_lidas() + " páginas!\n" +
                               "O maior livro que você tem é " + maior_livro());
        }
        else
            ui->txt_resultado->setText("Opa! Você não tem livros cadastrados ainda!");
    }
    else
        qDebug() << "Falha ao buscar livros cadastrados.";
}

statistics_window::~statistics_window()
{
    delete ui;
}

void statistics_window::on_btn_voltar_clicked()
{
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
    mainwindow *main_window = new mainwindow(username);
    main_window->setModal(true);
    main_window->exec();
}

QString statistics_window::qntd_livros()
{
    QSqlQuery query;
    query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE ID_USUARIO = :id ORDER BY ID_LIVRO DESC");
    query.bindValue(":id", id_usuario);

    QString id_livro_max;

    if(query.exec())
        if(query.next())
            id_livro_max = query.value(0).toString();
    else
        qDebug() << "Falha ao buscar maior id dos livros.";

    return id_livro_max;
}

QString statistics_window::qntd_livros_finalizados()
{
    QSqlQuery query;
    query.prepare("SELECT STATUS FROM banco_livros WHERE ID_USUARIO = :id");
    query.bindValue(":id", id_usuario);
    QString status;
    int qntd = 0;

    if(query.exec())
        while(query.next())
        {
            status = query.value(0).toString();
            if(status == "Finalizado")
                qntd++;
        }

    else
        qDebug() << "Falha ao buscar STATUS dos livros.";

    return QString::number(qntd);
}

QString statistics_window::num_paginas_lidas()
{
    QSqlQuery query;
    query.prepare("SELECT NUM_PAGINAS_LIDAS FROM banco_livros WHERE ID_USUARIO = :id");
    query.bindValue(":id", id_usuario);
    int pag_totais_lidas = 0;

    if(query.exec())
        while(query.next())
            pag_totais_lidas += query.value(0).toInt();
    else
        qDebug() << "Falha ao buscar NÚMERO DE PÁGINAS LIDAS dos livros.";

    return QString::number(pag_totais_lidas);
}

QString statistics_window::maior_livro()
{
    QSqlQuery query;
    query.prepare("SELECT TITULO, AUTOR FROM banco_livros WHERE ID_USUARIO = :id ORDER BY NUM_PAGINAS DESC");
    query.bindValue(":id", id_usuario);
    QString titulo, autor;

    if(query.exec() && query.next())
    {
        titulo = query.value(0).toString();
        autor = query.value(1).toString();
    }
    else
        qDebug() << "Falha ao buscar livro.";
    return (titulo + " de\n" + autor);
}
