#include "remove_book.h"
#include "ui_remove_book.h"

remove_book::remove_book(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::remove_book), id_usuario(id)
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
            ui->txt_aviso->setText("Opa! Você não tem livros cadastrados ainda!");
            ui->insert_titulo->setVisible(false);
            ui->insert_autor->setVisible(false);
            ui->insert_formato->setVisible(false);
            ui->txt_autor->setVisible(false);
            ui->txt_formato->setVisible(false);
            ui->txt_titulo->setVisible(false);
            ui->btn_remover->setVisible(false);
        }
    }
    else
        qDebug() << "Falha ao atualizar livro.";
}

remove_book::~remove_book()
{
    delete ui;
}

void remove_book::on_btn_remover_clicked()
{
    // obtém as informações inseridas
    QString titulo = ui->insert_titulo->text();
    QString autor = ui->insert_autor->text();
    QString formato = ui->insert_formato->currentText();
    QSqlQuery query;

    // testa se as informações não estão vazias
    if(!titulo.isEmpty() && !autor.isEmpty())
    {
        // busca o livro a partir das informações inseridas
        query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE id_usuario = :id and TITULO = :titulo and AUTOR = :autor and FORMATO = :formato");
        query.bindValue(":id", id_usuario);
        query.bindValue(":titulo", titulo);
        query.bindValue(":autor", autor);
        query.bindValue(":formato", formato);

        if(query.exec())
        {
            if(query.next())
            {
                // excluí o dado desejado a partir do id do usuário, título, autor e formato do livro
                query.prepare("DELETE FROM banco_livros WHERE id_usuario = :id and TITULO = :titulo and AUTOR = :autor and FORMATO = :formato");
                query.bindValue(":id", id_usuario);
                query.bindValue(":titulo", titulo);
                query.bindValue(":autor", autor);
                query.bindValue(":formato", formato);

                if(query.exec())
                {
                    ui->txt_aviso->setText("Livro deletado com sucesso!.");
                    ui->insert_titulo->clear();
                    ui->insert_autor->clear();
                    // atualização dos IDs dos livros restantes, a partir de um loop, começando do menor ID até o maior (todos os IDs são atualizados
                    // começando pelo menor, que irá valer 1
                    query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE id_usuario = :id ORDER BY ID_LIVRO");
                    query.bindValue(":id", id_usuario);

                    if (query.exec())
                    {
                        int novo_id = 1;
                        while (query.next())
                        {
                            int id_livro_atual = query.value(0).toInt();
                            QSqlQuery updateQuery;
                            updateQuery.prepare("UPDATE banco_livros SET ID_LIVRO = :novo_id WHERE ID_LIVRO = :id_livro_atual AND id_usuario = :id");
                            updateQuery.bindValue(":novo_id", novo_id);
                            updateQuery.bindValue(":id_livro_atual", id_livro_atual);
                            updateQuery.bindValue(":id", id_usuario);
                            novo_id++;

                            if (!updateQuery.exec())
                                qDebug() << "Erro ao atualizar ID_LIVRO.";
                        }
                    }
                    else
                        qDebug() << "Falha ao buscar ID dos livros.";
                }
                else
                    qDebug() << "Falha ao deletar livro.";
            }
            else
                ui->txt_aviso->setText("Livro não encontrado.");
        }
        else
            qDebug() << "Falha ao buscar livro.";
    }
    else
        ui->txt_aviso->setText("Os campos não podem estar vazios!");
}


void remove_book::on_btn_voltar_clicked()
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

