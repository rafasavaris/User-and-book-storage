#include "add_book.h"
#include "ui_add_book.h"

add_book::add_book(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_book) , id_usuario(id)
{
    ui->setupUi(this);
}

add_book::~add_book()
{
    delete ui;
}

// volta para a janela principal. busca o username a partir do id
// e passa como argumento.
void add_book::on_btn_voltar_clicked()
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

void add_book::on_btn_adicionar_clicked()
{
    // obtém todos os valores inseridos
    QString titulo = ui->insert_titulo->text();
    QString autor = ui->insert_autor->text();
    QString formato = ui->insert_formato->currentText();
    QString num_pag_totais = ui->insert_num_paginas->text();
    QString num_pag_lidas = ui->insert_num_paginas_lidas->text();
    QString status;

    // testa se os valores são válidos
    if(num_pag_lidas.toInt() > num_pag_totais.toInt())
        ui->txt_erro->setText("O número de páginas lidas não pode ser maior que o número de\npáginas totais!");
    // apenas insere se os campos de autor e título não estão vazios e o número de páginas totais for válido
    else if(!titulo.isEmpty() && !autor.isEmpty() && num_pag_totais != '0')
    {
        // prepara para buscas se o usuário já cadastrou este livro a partir do id do usuário,
        // título, autor e formato do livro
        int id_livro;
        QSqlQuery query;
        query.prepare("SELECT * FROM banco_livros WHERE ID_USUARIO = :id AND TITULO = :titulo AND AUTOR = :autor and FORMATO = :formato");
        query.bindValue(":id", id_usuario);
        query.bindValue(":titulo", titulo);
        query.bindValue(":autor", autor);
        query.bindValue(":formato", formato);

        if(query.exec())
        {
            // dá mesma forma que antes, conta se há cadastros com as informações inseridas
            int cont = 0;
            while(query.next())
                cont++;

            if(cont > 0)
            {
                // se já existe este cadastro, limpa os campos e exibe mensagem de erro
                ui->txt_erro->setText("Já existe um livro com esse titulo!");
                ui->insert_titulo->clear();
                ui->insert_autor->clear();
                ui->insert_num_paginas_lidas->setValue(0);
                ui->insert_num_paginas->setValue(0);
            }

            else
            {
                // senão, prepara para buscar o ID atual dos livros, selecionando o último
                query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE ID_USUARIO = :id ORDER BY ID_LIVRO DESC");
                query.bindValue(":id", id_usuario);
                if(query.exec())
                {
                    // se existe um ID, ele é atribuído a variável respectiva. senão, a variável vale 0 (primeira inserção)
                    if(query.next())
                        id_livro = query.value(0).toInt();

                    else
                        id_livro = 0;
                }
                else
                    qDebug() << "Falha ao procurar ID do último livro!";

                // define o status do livro
                if(num_pag_lidas == '0')
                    status = "Parado";
                else if(num_pag_lidas < num_pag_totais)
                    status = "Lendo";
                else
                    status = "Finalizado";

                // insere o livro no banco de dados, respectivo ao usuário atual
                query.prepare("INSERT INTO banco_livros (ID_USUARIO, ID_LIVRO, TITULO, AUTOR, NUM_PAGINAS, NUM_PAGINAS_LIDAS, FORMATO, STATUS) "
                              "VALUES(:id, :id_livros, :titulo, :autor, :num_pag_totais, :num_pag_lidas, :formato, :status)");
                query.bindValue(":id", id_usuario);
                query.bindValue(":id_livros", id_livro + 1); // id do livro é o id do último livro inserido + 1 (próximo livro)
                query.bindValue(":titulo", titulo);
                query.bindValue(":autor", autor);
                query.bindValue(":num_pag_totais", num_pag_totais);
                query.bindValue(":num_pag_lidas", num_pag_lidas);
                query.bindValue(":formato", formato);
                query.bindValue(":status", status);

                if(!query.exec()) // se o cadastro não for feito, exibe mensagem de erro
                    ui->txt_erro->setText("Erro ao inserir dados!");

                else // se for feito, limpa os campos
                {
                    ui->txt_erro->setText("Livro adicionado!");
                    ui->insert_titulo->clear();
                    ui->insert_autor->clear();
                    ui->insert_num_paginas_lidas->setValue(0);
                    ui->insert_num_paginas->setValue(0);
                }
            }
        }
        else
            qDebug() << "Falha ao verificar se o livro já existe nso cadastros.";
    }
    else
        ui->txt_erro->setText("Os dados devem ser preenchidos corretamente!");
}

