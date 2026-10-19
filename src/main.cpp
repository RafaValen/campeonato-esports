#include <cassert>
#include <iostream>

#include "Time.hpp"
#include "Partida.hpp"

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

    assert(Partida::placarValido(2, 0));
    assert(Partida::placarValido(2, 1));
    assert(Partida::placarValido(0, 2));
    assert(Partida::placarValido(1, 2));
    std::cout << "Placares aceitos: 2x0, 2x1, 0x2 e 1x2.\n";

    assert(!Partida::placarValido(3, 0));
    assert(!Partida::placarValido(0, 3));
    assert(!Partida::placarValido(1, 1));
    assert(!Partida::placarValido(0, 0));
    assert(!Partida::placarValido(2, 2));
    assert(!Partida::placarValido(-1, 2));
    assert(!Partida::placarValido(2, -1));
    assert(!Partida::placarValido(-1, -1));
    std::cout << "Placares rejeitados: 3x0, 0x3, 1x1, 0x0, 2x2, "
              << "-1x2, 2x-1 e -1x-1.\n";

    const Partida partida(alpha.getChave(), beta.getChave(), 2, 1);
    assert(partida.getChaveTimeA() == "alpha");
    assert(partida.getChaveTimeB() == "beta");
    assert(partida.getJogosA() == 2);
    assert(partida.getJogosB() == 1);
    assert(partida.envolveTime("alpha"));
    assert(partida.envolveTime("beta"));
    assert(!partida.envolveTime("gamma"));
    std::cout << "Partida: " << partida.getChaveTimeA() << " x "
              << partida.getChaveTimeB() << ", placar "
              << partida.getJogosA() << 'x' << partida.getJogosB() << '\n';
    std::cout << "envolveTime: alpha e beta participam; gamma nao participa.\n";
    std::cout << "Todos os testes da etapa 2 passaram.\n";
    return 0;
}
