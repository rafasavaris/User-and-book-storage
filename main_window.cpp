#include "main_window.h"
#include "ui_main_window.h"

mainwindow::mainwindow( QString &user_username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow) , username(user_username)
{
    ui->setupUi(this);

    // busca o nome do usuário para exibir mensagem na tela
    QSqlQuery query;
    query.prepare("SELECT NOME FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if (query.exec())
        if (query.next()) {
            QString nome = query.value(0).toString();
            ui->txt_bem_vindo->setText("Bem-vindo, "+nome+".");
        }
    else
        qDebug() << "Erro ao executar a consulta";
}

mainwindow::~mainwindow()
{
    delete ui;
}

// se o botão de voltar for apertado, retorna para a janela de login
// e fecha a janela atual
void mainwindow::on_btn_sair_clicked()
{
    this->close();
    loginwindow *login_window = new loginwindow();
    login_window->show();
}

// os métodos abaixo são chamados quando o respectivo botão é apertado,
// e em todos, o ID do usuário é procurado no banco de dados a partir
// do username e passado como parâmetro para a próxima tela, além de
// fechar a tela atual.

void mainwindow::on_btn_adicionar_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();

    else
        qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    add_book *add_window = new add_book(id);
    add_window->exec();
}


void mainwindow::on_btn_pesquisar_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();
    else
        qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    research_book *research_window = new research_book(id);
    research_window->exec();
}


void mainwindow::on_btn_atualizar_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();
    else
        qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    update_book *update_window = new update_book(id);
    update_window->exec();
}


void mainwindow::on_btn_remover_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();
    else
        qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    remove_book *remove_window = new remove_book(id);
    remove_window->exec();
}


void mainwindow::on_btn_ver_estante_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();
    else
         qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    show_books *show_window = new show_books(id);
    show_window->exec();
}

void mainwindow::on_btn_estatisticas_clicked()
{
    QSqlQuery query;
    int id;
    this->close();
    query.prepare("SELECT ID FROM usuarios WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if(query.exec())
        if(query.next())
            id = query.value(0).toInt();
        else
            qDebug() << "Erro ao buscar username para acessar a próxima janela!";

    statistics_window *statisticswindow = new statistics_window(id);
    statisticswindow->exec();
}

