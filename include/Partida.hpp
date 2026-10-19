#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <string>

class Partida {
private:
    std::string chaveTimeA;
    std::string chaveTimeB;
    int jogosA;
    int jogosB;

public:
    // O placar deve ser conferido com placarValido antes da construcao.
    Partida(const std::string& chaveTimeA, const std::string& chaveTimeB,
            int jogosA, int jogosB);

    const std::string& getChaveTimeA() const;
    const std::string& getChaveTimeB() const;
    int getJogosA() const;
    int getJogosB() const;

    bool envolveTime(const std::string& chave) const;
    static bool placarValido(int jogosA, int jogosB);
};

#endif
