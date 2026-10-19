#ifndef CAMPEONATO_HPP
#define CAMPEONATO_HPP

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "Time.hpp"
#include "Partida.hpp"

enum ResultadoRegistro {
    SUCESSO,
    TIME_NAO_CADASTRADO,
    MESMO_TIME,
    PLACAR_INVALIDO,
    CONFRONTO_REPETIDO
};

class Campeonato {
private:
    std::map<std::string, Time> times;
    std::vector<Partida> partidas;
    std::set<std::pair<std::string, std::string> > confrontos;

    static std::string removerEspacosExtremos(const std::string& nome);
    static std::string padronizarNome(const std::string& nome);
    static std::pair<std::string, std::string> montarChaveConfronto(
        const std::string& chaveA, const std::string& chaveB);

public:
    // Retorna false se o nome estiver vazio ou ja estiver cadastrado.
    bool cadastrarTime(const std::string& nome);
    // Em caso de falha, nao altera timeEncontrado.
    bool consultarTime(const std::string& nome, Time& timeEncontrado) const;
    // Retorna copias em ordem de chave, nao em ordem de classificacao.
    std::vector<Time> listarTimes() const;
    // Ordena apenas copias dos times pelos criterios de Time::operator<.
    std::vector<Time> classificacao() const;

    // Valida times, confronto consigo mesmo, placar e repeticao, nessa ordem.
    ResultadoRegistro registrarPartida(const std::string& nomeA,
                                       const std::string& nomeB,
                                       int jogosA, int jogosB);
    // Retorna copias na ordem de registro.
    std::vector<Partida> listarPartidas() const;

    // Substitui a saida por copias em ordem de registro.
    // Retorna false para time inexistente e deixa a saida vazia.
    // Retorna true para time cadastrado, mesmo que nao tenha partidas.
    bool historicoTime(const std::string& nome,
                       std::vector<Partida>& partidasEncontradas) const;
};

#endif
