#include "signup_window.h"
#include "ui_signup_window.h"

singupwindow::singupwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::singupwindow)
{
    ui->setupUi(this);
}

singupwindow::~singupwindow()
{
    delete ui;
}


void singupwindow::on_btn_cadastro_clicked()
{
    // obtém os valores dos campos a serem preenchidos
    QString nome = ui->insert_nome->text();
    QString username = ui->insert_username->text();
    QString senha = ui->insert_senha->text();
    QString senha_conf = ui->insert_senha_2->text();

    // verifica se as senhas são iguais
    if(senha != senha_conf && !senha.isEmpty() && !senha_conf.isEmpty())
    {
        ui->txt_erro->setText("As senhas inseridas são diferentes.");
        ui->insert_senha_2->clear();
    }
    // verifica se todos os campos estão preenchidos
    else if(!username.isEmpty() && !nome.isEmpty() && !senha.isEmpty() && !senha_conf.isEmpty())
    {
        // prepara para verificar se há o username inserido já está cadastrado
        QSqlQuery query;
        query.prepare("SELECT * FROM usuarios WHERE USERNAME = :username");
        query.bindValue(":username", ui->insert_username->text());

        if(query.exec())
        {
            int cont = 0;
            while(query.next())
                cont++;

            if(cont > 0)
            {
                // se já está cadastrado, emite mensagem de erro e limpa os campos
                ui->txt_erro->setText("Username já cadastrado! Insira outro.");
                ui->insert_username->clear();
                ui->insert_senha->clear();
                ui->insert_senha_2->clear();
                ui->insert_username->setFocus();
            }
            else
            {
                // se não, obtém o valor do ID do último usuário cadastrado
                query.prepare("SELECT ID FROM usuarios ORDER BY ID DESC");
                int id;
                if(query.exec())
                {
                    if(query.next())
                        id = query.value(0).toInt();
                    else // se não usuários cadastrados, o id vale 0
                        id = 0;
                }
                else
                    qDebug() << "Falha ao consultar o banco de dados.";

                id++; // incrementa para ser sempre o próximo (se for o primeiro, começar em 1)
                // prepara para inserir os dados do cadastro na tebal de usuários
                query.prepare("INSERT INTO usuarios (ID, USERNAME, NOME, SENHA) VALUES (:id, :username, :nome, :senha)");
                query.bindValue(":id", id);
                query.bindValue(":username", username);
                query.bindValue(":senha", senha);
                query.bindValue(":nome", nome);

                if(!query.exec())
                    qDebug() << "Erro ao inserir dados!";
                else
                {
                    // se o cadastro for feito com sucesso, abre a janela principal
                    qDebug() << "Cadastro feito!";
                    this->close();
                    mainwindow main_window(username);
                    main_window.exec();
                }
            }
        }
        else
            qDebug() << "Falha ao buscar username igual no banco de dados.";
    }
    else
        ui->txt_erro->setText("Os campos não podem estar vazios!");
}

// se o botão de voltar for apertado, retorna para a janela de login
// e fecha a janela atual
void singupwindow::on_btn_voltar_clicked()
{
    this->close();
    loginwindow *login_window = new loginwindow();
    login_window->show();
}

