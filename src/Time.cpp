#include "Time.hpp"

Time::Time(const std::string& nome, const std::string& chave)
    : nome(nome), chave(chave), vitoriasMD3(0), derrotasMD3(0),
      jogosGanhos(0), jogosPerdidos(0) {
}

const std::string& Time::getNome() const {
    return nome;
}

const std::string& Time::getChave() const {
    return chave;
}

int Time::getVitoriasMD3() const {
    return vitoriasMD3;
}

int Time::getDerrotasMD3() const {
    return derrotasMD3;
}

int Time::getJogosGanhos() const {
    return jogosGanhos;
}

int Time::getJogosPerdidos() const {
    return jogosPerdidos;
}

int Time::saldoJogos() const {
    return jogosGanhos - jogosPerdidos;
}

bool Time::operator<(const Time& outro) const {
    if (vitoriasMD3 != outro.vitoriasMD3) {
        return vitoriasMD3 > outro.vitoriasMD3;
    }
    if (saldoJogos() != outro.saldoJogos()) {
        return saldoJogos() > outro.saldoJogos();
    }
    if (jogosGanhos != outro.jogosGanhos) {
        return jogosGanhos > outro.jogosGanhos;
    }
    return chave < outro.chave;
}

void Time::registrarResultado(int ganhos, int perdidos) {
    jogosGanhos += ganhos;
    jogosPerdidos += perdidos;

    if (ganhos > perdidos) {
        ++vitoriasMD3;
    } else {
        ++derrotasMD3;
    }
}
