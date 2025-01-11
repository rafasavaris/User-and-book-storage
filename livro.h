#ifndef LIVRO_H
#define LIVRO_H
#include <QString>
#include <string>

class livro
{
private:
    int m_id_livro;
    QString m_titulo;
    QString m_autor;
    QString m_formato;
    int m_num_pag_totais;
    int m_num_pag_lidas;
    QString m_status;
public:
    livro(int id, QString titulo, QString autor, QString formato, int num_pag_totais, int num_pag_lidas, QString status) : m_id_livro(id), m_titulo(titulo), m_autor(autor), m_formato(formato), m_num_pag_totais(num_pag_totais), m_num_pag_lidas(num_pag_lidas), m_status(status) {}

    // getters
    int get_idLivro() { return m_id_livro; }
    QString get_titulo() { return m_titulo; }
    QString get_autor() { return m_autor; }
    QString get_formato() { return m_formato; }
    int get_numPagTotais() { return m_num_pag_totais; }
    int get_numPagLidas() { return m_num_pag_lidas; }
    QString get_status() { return m_status; }

    virtual QString mostrar_detalhes() = 0;
    ~livro() {}
};

#endif // LIVRO_H
