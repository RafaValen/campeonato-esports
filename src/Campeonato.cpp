#include "Campeonato.hpp"

#include <utility>

std::pair<std::string, std::string> Campeonato::montarChaveConfronto(
    const std::string& chaveA, const std::string& chaveB) {
    if (chaveA < chaveB) {
        return std::make_pair(chaveA, chaveB);
    }
    return std::make_pair(chaveB, chaveA);
}

std::string Campeonato::removerEspacosExtremos(const std::string& nome) {
    const std::string::size_type inicio = nome.find_first_not_of(' ');
    if (inicio == std::string::npos) {
        return "";
    }

    const std::string::size_type fim = nome.find_last_not_of(' ');
    return nome.substr(inicio, fim - inicio + 1);
}

std::string Campeonato::padronizarNome(const std::string& nome) {
    std::string chave = removerEspacosExtremos(nome);
    for (std::string::size_type i = 0; i < chave.size(); ++i) {
        if (chave[i] >= 'A' && chave[i] <= 'Z') {
            chave[i] = static_cast<char>(chave[i] - 'A' + 'a');
        }
    }
    return chave;
}

bool Campeonato::cadastrarTime(const std::string& nome) {
    const std::string nomeLimpo = removerEspacosExtremos(nome);
    const std::string chave = padronizarNome(nomeLimpo);
    if (chave.empty()) {
        return false;
    }

    // insert nao substitui um time que ja tenha a mesma chave.
    return times.insert(std::make_pair(chave, Time(nomeLimpo, chave))).second;
}

bool Campeonato::consultarTime(const std::string& nome, Time& timeEncontrado) const {
    const std::string chave = padronizarNome(nome);
    const std::map<std::string, Time>::const_iterator it = times.find(chave);
    if (it == times.end()) {
        return false;
    }

    timeEncontrado = it->second;
    return true;
}

std::vector<Time> Campeonato::listarTimes() const {
    std::vector<Time> lista;
    for (std::map<std::string, Time>::const_iterator it = times.begin();
         it != times.end(); ++it) {
        lista.push_back(it->second);
    }
    return lista;
}

ResultadoRegistro Campeonato::registrarPartida(const std::string& nomeA,
                                              const std::string& nomeB,
                                              int jogosA, int jogosB) {
    const std::string chaveA = padronizarNome(nomeA);
    const std::string chaveB = padronizarNome(nomeB);
    std::map<std::string, Time>::iterator timeA = times.find(chaveA);
    std::map<std::string, Time>::iterator timeB = times.find(chaveB);

    if (timeA == times.end() || timeB == times.end()) {
        return TIME_NAO_CADASTRADO;
    }
    if (chaveA == chaveB) {
        return MESMO_TIME;
    }
    if (!Partida::placarValido(jogosA, jogosB)) {
        return PLACAR_INVALIDO;
    }

    const std::pair<std::string, std::string> confronto =
        montarChaveConfronto(chaveA, chaveB);
    if (confrontos.find(confronto) != confrontos.end()) {
        return CONFRONTO_REPETIDO;
    }

    // Nenhum dado e alterado antes de todas as validacoes acima.
    partidas.push_back(Partida(chaveA, chaveB, jogosA, jogosB));
    confrontos.insert(confronto);
    timeA->second.registrarResultado(jogosA, jogosB);
    timeB->second.registrarResultado(jogosB, jogosA);
    return SUCESSO;
}

std::vector<Partida> Campeonato::listarPartidas() const {
    return partidas;
}
