#include "login_window.h"
#include "./ui_login_window.h"

static QSqlDatabase banco_de_dados = QSqlDatabase::addDatabase("QSQLITE");

loginwindow::loginwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginwindow)
{
    // cria um QFile com url do banco de dados compactado no arquivo resources.qrc
    QFile resourceFile(":/banco_de_dados/banco_de_usuarios.db");
    // veriffica se este arquivo existe
    if (!resourceFile.exists()) {
        qDebug() << "Erro: O arquivo do .qrc não existe!";
        return;
    }
    else
        qDebug() << "Arquivo do .qrc encontrado!";

    // QString com o endereço do banco de dados compactado
    QString resourcePath = ":/banco_de_dados/banco_de_usuarios.db";

    // obtém o endereço da pasta Home do usuário
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    // cria um caminho (em formato de string) com o endereço do Home + nome do banco de dados
    QString tempPath = homePath + "/banco_de_usuarios.db";

    // verifica se o banco de dados (arquivo .db) já foi copiado anteriormente
    if (!QFile::exists(tempPath)) {
        // se não existe, copia ele do arquivo resources.qrc para o caminho declarado anteriormente
        qDebug() << "Banco de dados não encontrado em" << tempPath << ". Copiando arquivo.";

        if (QFile::copy(resourcePath, tempPath)) {
            qDebug() << "Banco de dados copiado com sucesso para:" << tempPath;
            QFile file(tempPath); // cria uma variável QFile para ser possível setar
                                  // as permissões necessárias para manipular o arquivo
            if (!file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner))
                qDebug() << "Erro ao definir permissões:" << file.errorString();
        }
        else
        {
            qDebug() << "Erro ao copiar banco de dados do .qrc:" << QFile(resourcePath).errorString();
            return;
        }
    }
    else
        qDebug() << "Banco de dados já existe em:" << tempPath;

    ui->setupUi(this);
    //associa a variável ao caminho do banco de dados criado
    banco_de_dados.setDatabaseName(tempPath);

    if(banco_de_dados.open())
        qDebug() << "Banco de dados aberto com sucesso!";
    else
    {
        qDebug() << "Erro ao abrir banco de dados!!";
        return;
    }
    ui->insert_username->setFocus();
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_btn_login_clicked()
{
    // valores dos campos preenchidos na tela
    QString username = ui->insert_username->text();
    QString senha = ui->insert_senha->text();
    // busca destes campos no banco de dados dos usuários
    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE USERNAME = :username AND SENHA = :senha");
    query.bindValue(":username", username);
    query.bindValue(":senha", senha);

    // verifica se os campos não estão vazios
    if(!username.isEmpty() && !senha.isEmpty())
    {
        if(query.exec())
        {
            // a sequência abaixo conta quantos registros existem com base na busca feita
            // se existir registros, a variável é incrementada
            int cont = 0;
            while(query.next())
                cont++;
            if(cont > 0)
            {
                // se o usuário existe, fecha a janela de login e abre a janela principal,
                // passando o username do usuário que fez login como argumento
                this->close();
                mainwindow *main_window = new mainwindow(username);
                main_window->setModal(true);
                main_window->exec();
            }
            else
            {
                // exibe mensagem de erro e limpa os campos a serem preenchidos
                ui->texto_erro->setText("Usuário não encontrado!");
                ui->insert_username->clear();
                ui->insert_senha->clear();
                ui->insert_username->setFocus();
            }
        }
        else
            qDebug() << "Erro ao realizar consulta de dados.";
    }
    else
        ui->texto_erro->setText("Preencha todos os campos!");
}

// se o botão de cadastro for apertado, fecha a janela de login
// e abre a janela de cadastro
void loginwindow::on_btn_sign_up_clicked()
{
    this->close();
    singupwindow singup_window;
    singup_window.exec();
}

// se o botão de sair for apertado, fecha o banco de dados e
// a janela de login (encerra o programa)
void loginwindow::on_btn_sair_clicked()
{
    banco_de_dados.close();
    this->close();
}

