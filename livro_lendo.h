#ifndef LIVRO_LENDO_H
#define LIVRO_LENDO_H
#include "livro.h"

class livro_lendo : public livro
{
public:
    livro_lendo(int id, QString titulo, QString autor, QString formato, int num_pag_totais, int num_pag_lidas, QString status)
        : livro(id, titulo, autor, formato, num_pag_totais, num_pag_lidas, status) {}

    QString mostrar_detalhes()
    {
        QString sst;
        sst = "Título: " + get_titulo() + "\nAutor: " + get_autor() + "\nFormato: " + get_formato() +
                   "\nNúmero de páginas totais: " + QString::number(get_numPagTotais()) + "\nNúmero de páginas lidas: " + QString::number(get_numPagLidas()) +
                   "\nStatus: o livro está sendo lido. Não esqueça de\natualizar seu progresso.";
        return sst;
    }
};

#endif // LIVRO_LENDO_H
