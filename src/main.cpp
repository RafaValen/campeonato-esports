#include <cassert>
#include <iostream>

#include "Time.hpp"

int main() {
    Time alpha("Alpha", "alpha");

    assert(alpha.getNome() == "Alpha");
    assert(alpha.getChave() == "alpha");
    assert(alpha.getVitoriasMD3() == 0);
    assert(alpha.getDerrotasMD3() == 0);
    assert(alpha.getJogosGanhos() == 0);
    assert(alpha.getJogosPerdidos() == 0);
    assert(alpha.saldoJogos() == 0);

    std::cout << "Time: " << alpha.getNome() << '\n';
    std::cout << "Antes: MD3 vencidas=" << alpha.getVitoriasMD3()
              << ", MD3 perdidas=" << alpha.getDerrotasMD3()
              << ", jogos ganhos=" << alpha.getJogosGanhos()
              << ", jogos perdidos=" << alpha.getJogosPerdidos()
              << ", saldo=" << alpha.saldoJogos() << '\n';

    alpha.registrarResultado(2, 1);

    assert(alpha.getVitoriasMD3() == 1);
    assert(alpha.getDerrotasMD3() == 0);
    assert(alpha.getJogosGanhos() == 2);
    assert(alpha.getJogosPerdidos() == 1);
    assert(alpha.saldoJogos() == 1);

    std::cout << "Apos vencer por 2x1: MD3 vencidas=" << alpha.getVitoriasMD3()
              << ", MD3 perdidas=" << alpha.getDerrotasMD3()
              << ", jogos ganhos=" << alpha.getJogosGanhos()
              << ", jogos perdidos=" << alpha.getJogosPerdidos()
              << ", saldo=+" << alpha.saldoJogos() << '\n';

    // Confere tambem derrotas e acumulacao sem mudar o exemplo de Alpha.
    Time beta("Beta", "beta");
    beta.registrarResultado(0, 2);
    beta.registrarResultado(2, 0);
    assert(beta.getVitoriasMD3() == 1);
    assert(beta.getDerrotasMD3() == 1);
    assert(beta.getJogosGanhos() == 2);
    assert(beta.getJogosPerdidos() == 2);
    assert(beta.saldoJogos() == 0);

    std::cout << "Todos os testes da etapa 1 passaram.\n";
    return 0;
}
