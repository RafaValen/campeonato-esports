#ifndef TIME_HPP
#define TIME_HPP

#include <string>

class Time {
private:
    std::string nome;
    std::string chave;
    int vitoriasMD3;
    int derrotasMD3;
    int jogosGanhos;
    int jogosPerdidos;

public:
    Time(const std::string& nome, const std::string& chave);

    const std::string& getNome() const;
    const std::string& getChave() const;
    int getVitoriasMD3() const;
    int getDerrotasMD3() const;
    int getJogosGanhos() const;
    int getJogosPerdidos() const;
    int saldoJogos() const;

    // Retorna true quando este time deve vir antes do outro na classificacao.
    bool operator<(const Time& outro) const;

    // Recebe um placar de MD3 ja validado: 2x0, 2x1, 0x2 ou 1x2.
    void registrarResultado(int ganhos, int perdidos);
};

#endif
