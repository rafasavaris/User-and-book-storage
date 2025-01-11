#include "livro.h"

void livro::calcular_progresso()
{
    m_progresso = m_num_pag_lidas * 100 / m_num_pag_totais;
}
