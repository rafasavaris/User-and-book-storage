#include "update_book.h"
#include "ui_update_book.h"
#include "login_window.h"

update_book::update_book(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::update_book), id_usuario(id)
{
    ui->setupUi(this);
    // prepara para verificar se o usuário já tem livros cadastrados
    QSqlQuery query;
    query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE id_usuario = :id");
    query.bindValue(":id", id_usuario);
    if(query.exec())
    {
        if(!query.next())
        {
            // se não tiver, mostra apenas mensagem relatando isso
            ui->txt_resultado->setText("Opa! Você não tem livros cadastrados ainda!");
            ui->insert_titulo->setVisible(false);
            ui->insert_autor->setVisible(false);
            ui->insert_formato->setVisible(false);
            ui->txt_autor->setVisible(false);
            ui->txt_formato->setVisible(false);
            ui->txt_titulo->setVisible(false);
            ui->btn_pesquisar->setVisible(false);
        }
    }
    else
        qDebug() << "Falha ao verificar se existem livros cadastrados";
    // visibilidade desativada de itens que aparecem só se o livro desejado existe
    ui->btn_atualizar->setVisible(false);
    ui->insert_num_paginas->setVisible(false);
    ui->insert_num_paginas_lidas->setVisible(false);
    ui->txt_num_pag->setVisible(false);
    ui->txt_num_pag_lidas->setVisible(false);
}

update_book::~update_book()
{
    delete ui;
}

// volta para a tela inicial. busca o username a partir do id
// e passa como parâmetro.
void update_book::on_btn_voltar_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT USERNAME FROM usuarios WHERE ID = :id");
    query.bindValue(":id", id_usuario);
    QString username;

    if(query.exec())
        if(query.next())
            username = query.value(0).toString();

    this->close();
    mainwindow *main_window = new mainwindow(username);
    main_window->setModal(true);
    main_window->exec();
}

void update_book::on_btn_atualizar_clicked()
{
    // obtém os valores dos campos preenchidos
    QString titulo = ui->insert_titulo->text();
    QString autor = ui->insert_autor->text();
    QString formato = ui->insert_formato->currentText();
    QString num_pag_totais = ui->insert_num_paginas->text();
    QString num_pag_lidas = ui->insert_num_paginas_lidas->text();
    QString id_livro, status;

    // verifica se as informações necessárias estão inseridas corretamente
    if(num_pag_totais.toInt() != 0 && num_pag_lidas.toInt() <= num_pag_totais.toInt())
    {
        // se sim, busca o livro a partir do título, autor e formato
        QSqlQuery query;
        query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE id_usuario = :id and TITULO = :titulo and AUTOR = :autor and FORMATO = :formato");
        query.bindValue(":id", id_usuario);
        query.bindValue(":titulo", titulo);
        query.bindValue(":autor", autor);
        query.bindValue(":formato", formato);

        if(query.exec())
        {
            if(query.next())
            {
                id_livro = query.value(0).toString();
                // se o livro for encontrado, atualiza com as informações inseridas
                // define o novo estado do livro
                if(num_pag_lidas.toInt() == 0)
                    status = "Parado";
                else if(num_pag_lidas.toInt() < num_pag_totais.toInt())
                    status = "Lendo";
                else
                    status = "Finalizado";

                query.prepare("UPDATE banco_livros SET NUM_PAGINAS = :num_pag_totais, NUM_PAGINAS_LIDAS = :num_pag_lidas, STATUS = :status WHERE ID_LIVRO = :id");
                query.bindValue(":id", id_livro);
                query.bindValue(":num_pag_totais", num_pag_totais);
                query.bindValue(":num_pag_lidas", num_pag_lidas);
                query.bindValue(":status", status);

                if(query.exec())
                {
                    // se o comando for executado com sucesso, exibe mensagem e retorna ao começo desta tela
                    ui->txt_resultado->setText("Livro atualizado!");
                    ui->insert_autor->clear();
                    ui->insert_titulo->clear();
                    ui->insert_num_paginas->setValue(0);
                    ui->insert_num_paginas_lidas->setValue(0);
                    ui->btn_atualizar->setVisible(false);
                    ui->insert_num_paginas->setVisible(false);
                    ui->insert_num_paginas_lidas->setVisible(false);
                    ui->txt_num_pag->setVisible(false);
                    ui->txt_num_pag_lidas->setVisible(false);
                }
                else
                    qDebug() << "Falha ao atualizar livro.";
            }
            else
                ui->txt_resultado->setText("Livro não encontrado.");
        }
        else
            qDebug() << "Falha ao buscar livro.";
    }
    else
         ui->txt_resultado->setText("Digite valores válidos.");
}


void update_book::on_btn_pesquisar_clicked()
{
    // realiza a busca do livro a partir dos campos inseridos
    QString titulo = ui->insert_titulo->text();
    QString autor = ui->insert_autor->text();
    QString formato = ui->insert_formato->currentText();
    QString num_paginas, num_paginas_lidas;

    // verifica se as informações necessárias estão inseridas corretamente
    if(!titulo.isEmpty() && !autor.isEmpty())
    {
        // se sim, busca o livro a partir do título, autor e formato
        QSqlQuery query;
        query.prepare("SELECT NUM_PAGINAS, NUM_PAGINAS_LIDAS FROM banco_livros WHERE id_usuario = :id and TITULO = :titulo and AUTOR = :autor and FORMATO = :formato");
        query.bindValue(":id", id_usuario);
        query.bindValue(":titulo", titulo);
        query.bindValue(":autor", autor);
        query.bindValue(":formato", formato);

        if(query.exec())
        {
            if(query.next())
            {
                // se o livro for encontrado, mostra as opções para atualizar
                num_paginas = query.value(0).toString();
                num_paginas_lidas= query.value(1).toString();
                ui->btn_atualizar->setVisible(true);
                ui->insert_num_paginas->setVisible(true);
                ui->insert_num_paginas->setValue(num_paginas.toInt());
                ui->insert_num_paginas_lidas->setVisible(true);
                ui->txt_num_pag->setVisible(true);
                ui->txt_num_pag_lidas->setVisible(true);
                ui->insert_num_paginas_lidas->setValue(num_paginas_lidas.toInt());
            }
            else
                ui->txt_resultado->setText("Livro não encontrado.");
        }
        else
            qDebug() << "Falha ao buscar livro.";
    }
    else
        ui->txt_resultado->setText("Título e Autor não podem estar vazios!");
}

