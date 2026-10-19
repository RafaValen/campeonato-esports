#include "Interface.hpp"
#include "Campeonato.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
    bool lerLinha(const std::string& mensagem, std::string& linha) {
        std::cout << mensagem;
        return static_cast<bool>(std::getline(std::cin, linha));
    }

    bool lerInteiro(const std::string& mensagem, int& numero) {
        std::string linha;
        while (lerLinha(mensagem, linha)) {
            std::istringstream entrada(linha);
            char sobra;
            if ((entrada >> numero) && !(entrada >> sobra)) {
                return true;
            }
            std::cout << "Entrada invalida: digite somente um numero inteiro. Tente novamente.\n";
        }
        return false;
    }

    void mostrarMenu() {
        std::cout << "\nGerenciador de Campeonatos de Esports\n"
                  << "1 - Cadastrar time\n"
                  << "2 - Listar times\n"
                  << "3 - Registrar resultado MD3\n"
                  << "4 - Listar partidas\n"
                  << "5 - Exibir classificacao\n"
                  << "6 - Consultar historico\n"
                  << "0 - Sair\n";
    }

    bool cadastrarTime(Campeonato& campeonato) {
        std::string nome;
        if (!lerLinha("Nome do time: ", nome)) {
            return false;
        }
        if (campeonato.cadastrarTime(nome)) {
            std::cout << "Time cadastrado com sucesso.\n";
        } else {
            Time encontrado("", "");
            if (campeonato.consultarTime(nome, encontrado)) {
                std::cout << "Erro: time ja cadastrado.\n";
            } else {
                std::cout << "Erro: nome vazio ou apenas espacos nao e permitido.\n";
            }
        }
        return true;
    }

    void listarTimes(const Campeonato& campeonato) {
        const std::vector<Time> times = campeonato.listarTimes();
        if (times.empty()) {
            std::cout << "Nenhum time cadastrado.\n";
            return;
        }
        std::cout << "Times cadastrados:\n";
        for (std::vector<Time>::size_type i = 0; i < times.size(); ++i) {
            std::cout << "- " << times[i].getNome() << '\n';
        }
    }

    bool registrarPartida(Campeonato& campeonato) {
        std::string nomeA;
        std::string nomeB;
        int jogosA;
        int jogosB;
        if (!lerLinha("Nome do time A: ", nomeA)
            || !lerLinha("Nome do time B: ", nomeB)
            || !lerInteiro("Jogos ganhos pelo time A: ", jogosA)
            || !lerInteiro("Jogos ganhos pelo time B: ", jogosB)) {
            return false;
        }
        switch (campeonato.registrarPartida(nomeA, nomeB, jogosA, jogosB)) {
        case SUCESSO:
            std::cout << "Partida registrada com sucesso.\n";
            break;
        case TIME_NAO_CADASTRADO:
            std::cout << "Erro: um ou ambos os times nao estao cadastrados.\n";
            break;
        case MESMO_TIME:
            std::cout << "Erro: um time nao pode jogar contra ele mesmo.\n";
            break;
        case PLACAR_INVALIDO:
            std::cout << "Erro: placar invalido. Use 2x0, 2x1, 0x2 ou 1x2.\n";
            break;
        case CONFRONTO_REPETIDO:
            std::cout << "Erro: confronto ja realizado, mesmo na ordem invertida.\n";
            break;
        }
        return true;
    }

    void mostrarPartidas(const Campeonato& campeonato,
                         const std::vector<Partida>& partidas) {
        for (std::vector<Partida>::size_type i = 0; i < partidas.size(); ++i) {
            Time timeA("", "");
            Time timeB("", "");
            campeonato.consultarTime(partidas[i].getChaveTimeA(), timeA);
            campeonato.consultarTime(partidas[i].getChaveTimeB(), timeB);
            std::cout << timeA.getNome() << ' ' << partidas[i].getJogosA()
                      << 'x' << partidas[i].getJogosB() << ' '
                      << timeB.getNome() << '\n';
        }
    }

    void listarPartidas(const Campeonato& campeonato) {
        const std::vector<Partida> partidas = campeonato.listarPartidas();
        if (partidas.empty()) {
            std::cout << "Nenhuma partida registrada.\n";
            return;
        }
        std::cout << "Partidas registradas:\n";
        mostrarPartidas(campeonato, partidas);
    }

    void mostrarClassificacao(const Campeonato& campeonato) {
        const std::vector<Time> tabela = campeonato.classificacao();
        if (tabela.empty()) {
            std::cout << "Classificacao vazia: nenhum time cadastrado.\n";
            return;
        }
        std::cout << "Classificacao (MD3 V/D, jogos V/D e saldo):\n";
        for (std::vector<Time>::size_type i = 0; i < tabela.size(); ++i) {
            const Time& time = tabela[i];
            std::cout << i + 1 << ". " << time.getNome()
                      << " | MD3 " << time.getVitoriasMD3() << '/' << time.getDerrotasMD3()
                      << " | jogos " << time.getJogosGanhos() << '/' << time.getJogosPerdidos()
                      << " | saldo " << time.saldoJogos() << '\n';
        }
    }

    bool consultarHistorico(const Campeonato& campeonato) {
        std::string nome;
        if (!lerLinha("Nome do time: ", nome)) {
            return false;
        }
        std::vector<Partida> partidas;
        if (!campeonato.historicoTime(nome, partidas)) {
            std::cout << "Erro: time nao cadastrado.\n";
        } else if (partidas.empty()) {
            std::cout << "Este time ainda nao possui partidas.\n";
        } else {
            Time time("", "");
            campeonato.consultarTime(nome, time);
            std::cout << "Historico de " << time.getNome() << ":\n";
            mostrarPartidas(campeonato, partidas);
        }
        return true;
    }
}

void Interface::executar() {
    Campeonato campeonato;
    while (true) {
        mostrarMenu();
        int opcao;
        if (!lerInteiro("Opcao: ", opcao)) {
            break;
        }
        bool leituraCompleta = true;
        switch (opcao) {
        case 0:
            std::cout << "Programa encerrado.\n";
            return;
        case 1:
            leituraCompleta = cadastrarTime(campeonato);
            break;
        case 2:
            listarTimes(campeonato);
            break;
        case 3:
            leituraCompleta = registrarPartida(campeonato);
            break;
        case 4:
            listarPartidas(campeonato);
            break;
        case 5:
            mostrarClassificacao(campeonato);
            break;
        case 6:
            leituraCompleta = consultarHistorico(campeonato);
            break;
        default:
            std::cout << "Opcao invalida. Escolha de 0 a 6.\n";
            break;
        }
        if (!leituraCompleta) {
            break;
        }
    }
    std::cout << "\nFim da entrada. Programa encerrado.\n";
}
