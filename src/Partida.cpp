#include "Partida.hpp"

Partida::Partida(const std::string& chaveTimeA, const std::string& chaveTimeB,
                 int jogosA, int jogosB)
    : chaveTimeA(chaveTimeA), chaveTimeB(chaveTimeB),
      jogosA(jogosA), jogosB(jogosB) {
}

const std::string& Partida::getChaveTimeA() const {
    return chaveTimeA;
}

const std::string& Partida::getChaveTimeB() const {
    return chaveTimeB;
}

int Partida::getJogosA() const {
    return jogosA;
}

int Partida::getJogosB() const {
    return jogosB;
}

bool Partida::envolveTime(const std::string& chave) const {
    return chave == chaveTimeA || chave == chaveTimeB;
}

bool Partida::placarValido(int jogosA, int jogosB) {
    return (jogosA == 2 && (jogosB == 0 || jogosB == 1))
        || (jogosB == 2 && (jogosA == 0 || jogosA == 1));
}
