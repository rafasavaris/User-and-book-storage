#include "research_book.h"
#include "ui_research_book.h"

research_book::research_book(int &id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::research_book), id_usuario(id)
{
    ui->setupUi(this);
    ui->progresso_leitura->setVisible(false);

    // prepara para verificar se o usuário já tem livros cadastrados
    QSqlQuery query;
    query.prepare("SELECT ID_LIVRO FROM banco_livros WHERE id_usuario = :id");
    query.bindValue(":id", id_usuario);
    if(query.exec())
    {
        if(!query.next())
        {
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
        qDebug() << "Falha ao procurar livros cadastrados.";
}

research_book::~research_book()
{
    delete ui;
}

void research_book::on_btn_pesquisar_clicked()
{
    QString titulo = ui->insert_titulo->text();
    QString autor = ui->insert_autor->text();
    QString formato = ui->insert_formato->currentText();
    QString num_pag_totais, num_pag_lidas, id_livro, status;

    // testa se o usuário digitou nome e autor
    if(!titulo.isEmpty() && !autor.isEmpty())
    {
        // se sim, pesquisa baseado no titulo, autor e formato
        QSqlQuery query;
        query.prepare("SELECT ID_LIVRO, NUM_PAGINAS, NUM_PAGINAS_LIDAS, STATUS FROM banco_livros WHERE id_usuario = :id and TITULO = :titulo and AUTOR = :autor AND FORMATO = :formato");
        query.bindValue(":id", id_usuario);
        query.bindValue(":titulo", titulo);
        query.bindValue(":autor", autor);
        query.bindValue(":formato", formato);

        if(query.exec())
        {
            if(query.next())
            {
                id_livro = query.value(0).toString();
                num_pag_totais = query.value(1).toString();
                num_pag_lidas = query.value(2).toString();
                status = query.value(3).toString();
                ui->txt_resultado->setText("Livro encontrado!\nTítulo: " +titulo+ "\nAutor: " +autor+
                                           "\nFormato: " +formato+ "\nNúmero de páginas: " +num_pag_totais+
                                           "\nNúmero de páginas lidas: " +num_pag_lidas+ "\nStatus: " +status+ "\nProgresso: ");
                int qntd_progresso;
                qntd_progresso = (num_pag_lidas.toInt() * 100)/num_pag_totais.toInt();
                ui->progresso_leitura->setVisible(true);
                ui->progresso_leitura->setValue(qntd_progresso);
                ui->insert_autor->clear();
                ui->insert_titulo->clear();
                ui->insert_titulo->setFocus();

            }
            else
            {
                ui->progresso_leitura->setVisible(false);
                ui->txt_resultado->setText("Livro não encontrado.");
            }
        }
        else
            qDebug() << "Falha ao buscar livro.";
    }
    else
    {
        ui->txt_resultado->setText("Digite valores válidos!");
        ui->progresso_leitura->setVisible(false);
    }
}


void research_book::on_btn_voltar_clicked()
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

