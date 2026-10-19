#include <cassert>
#include <iostream>

#include "Time.hpp"
#include "Partida.hpp"
#include "Campeonato.hpp"

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

    Campeonato campeonato;
    Time encontrado("Sem consulta", "sem consulta");
    assert(campeonato.listarTimes().empty());
    assert(!campeonato.consultarTime("Alpha", encontrado));
    assert(encontrado.getNome() == "Sem consulta");
    assert(!campeonato.cadastrarTime(""));
    assert(!campeonato.cadastrarTime("   "));
    assert(campeonato.listarTimes().empty());
    std::cout << "Campeonato vazio: lista vazia e consulta sem resultado.\n";
    std::cout << "Nomes vazios ou apenas espacos foram rejeitados.\n";

    assert(campeonato.cadastrarTime("  Alpha  "));
    assert(campeonato.cadastrarTime("Beta"));
    assert(!campeonato.cadastrarTime("ALPHA"));
    assert(!campeonato.cadastrarTime("  aLpHa "));
    assert(!campeonato.cadastrarTime(""));
    assert(!campeonato.cadastrarTime("   "));
    assert(campeonato.listarTimes().size() == 2);
    std::cout << "Alpha e Beta cadastrados; ALPHA e aLpHa duplicados rejeitados.\n";

    const Campeonato& consulta = campeonato;
    assert(consulta.consultarTime("  ALPHA  ", encontrado));
    assert(encontrado.getNome() == "Alpha");
    assert(encontrado.getChave() == "alpha");
    assert(encontrado.getVitoriasMD3() == 0);
    assert(encontrado.getDerrotasMD3() == 0);
    assert(encontrado.getJogosGanhos() == 0);
    assert(encontrado.getJogosPerdidos() == 0);
    assert(encontrado.saldoJogos() == 0);
    assert(!consulta.consultarTime("Gamma", encontrado));
    assert(!consulta.consultarTime("", encontrado));
    assert(!consulta.consultarTime("   ", encontrado));
    assert(encontrado.getNome() == "Alpha");
    assert(consulta.listarTimes().size() == 2);
    std::cout << "Consulta de ALPHA com espacos encontrou Alpha, com estatisticas zeradas.\n";
    std::cout << "Time inexistente e consultas vazias nao alteraram o campeonato.\n";

    std::vector<Time> lista = consulta.listarTimes();
    assert(lista.size() == 2);
    assert(lista[0].getNome() == "Alpha");
    assert(lista[0].getChave() == "alpha");
    assert(lista[1].getNome() == "Beta");
    assert(lista[1].getChave() == "beta");
    assert(consulta.consultarTime("bEtA", encontrado));
    assert(encontrado.getNome() == "Beta");
    std::cout << "Listagem: " << lista[0].getNome() << ", "
              << lista[1].getNome() << '\n';

    // As consultas devolvem copias: modifica-las nao muda o cadastro.
    lista[0].registrarResultado(2, 0);
    encontrado.registrarResultado(2, 1);
    assert(consulta.consultarTime("Alpha", encontrado));
    assert(encontrado.getVitoriasMD3() == 0);
    assert(consulta.consultarTime("Beta", encontrado));
    assert(encontrado.getVitoriasMD3() == 0);

    Campeonato nomesComEspacos;
    assert(nomesComEspacos.cadastrarTime("  Team Alpha  "));
    assert(nomesComEspacos.consultarTime(" TEAM ALPHA ", encontrado));
    assert(encontrado.getNome() == "Team Alpha");
    assert(encontrado.getChave() == "team alpha");
    assert(!nomesComEspacos.cadastrarTime("team alpha"));
    std::cout << "Espacos internos preservados; consultas e listagens devolvem copias.\n";
    std::cout << "Todos os testes da etapa 3 passaram.\n";

    Campeonato md3;
    assert(md3.listarPartidas().empty());
    assert(md3.registrarPartida("Alpha", "Beta", 2, 1) == TIME_NAO_CADASTRADO);
    assert(md3.listarTimes().empty());
    assert(md3.listarPartidas().empty());
    assert(md3.cadastrarTime("Alpha"));
    assert(md3.cadastrarTime("Beta"));
    assert(md3.cadastrarTime("Gamma"));
    assert(md3.cadastrarTime("Delta"));

    assert(md3.registrarPartida("  ALPHA ", " bEtA  ", 2, 1) == SUCESSO);
    assert(md3.consultarTime("Alpha", encontrado));
    assert(encontrado.getVitoriasMD3() == 1);
    assert(encontrado.getDerrotasMD3() == 0);
    assert(encontrado.getJogosGanhos() == 2);
    assert(encontrado.getJogosPerdidos() == 1);
    assert(encontrado.saldoJogos() == 1);
    assert(md3.consultarTime("Beta", encontrado));
    assert(encontrado.getVitoriasMD3() == 0);
    assert(encontrado.getDerrotasMD3() == 1);
    assert(encontrado.getJogosGanhos() == 1);
    assert(encontrado.getJogosPerdidos() == 2);
    assert(encontrado.saldoJogos() == -1);
    std::cout << "Alpha 2x1 Beta aceito com nomes normalizados.\n";
    std::cout << "Alpha: MD3 1V/0D, jogos 2V/1D, saldo +1; "
              << "Beta: MD3 0V/1D, jogos 1V/2D, saldo -1.\n";

    const std::vector<Time> antesDasRecusas = md3.listarTimes();
    assert(md3.registrarPartida(" BETA ", "alpha", 2, 0) == CONFRONTO_REPETIDO);
    assert(md3.registrarPartida("Alpha", "Beta", 2, 1) == CONFRONTO_REPETIDO);
    assert(md3.registrarPartida("Alpha", " ALPHA ", 2, 0) == MESMO_TIME);
    assert(md3.registrarPartida("Inexistente", "Beta", 2, 0) == TIME_NAO_CADASTRADO);
    assert(md3.registrarPartida("Alpha", "Inexistente", 2, 0) == TIME_NAO_CADASTRADO);
    assert(md3.registrarPartida("", "Beta", 2, 0) == TIME_NAO_CADASTRADO);
    assert(md3.registrarPartida("Alpha", "   ", 2, 0) == TIME_NAO_CADASTRADO);

    // Alpha x Gamma ainda nao aconteceu: o erro deve ser o placar.
    const int placaresInvalidos[][2] = {
        {3, 0}, {0, 3}, {1, 1}, {0, 0}, {2, 2}, {-1, 2}, {2, -1}, {-1, -1}
    };
    for (int i = 0; i < 8; ++i) {
        assert(md3.registrarPartida("Alpha", "Gamma",
                                   placaresInvalidos[i][0], placaresInvalidos[i][1])
               == PLACAR_INVALIDO);
    }

    const std::vector<Time> depoisDasRecusas = md3.listarTimes();
    assert(depoisDasRecusas.size() == antesDasRecusas.size());
    for (std::vector<Time>::size_type i = 0; i < antesDasRecusas.size(); ++i) {
        assert(depoisDasRecusas[i].getNome() == antesDasRecusas[i].getNome());
        assert(depoisDasRecusas[i].getChave() == antesDasRecusas[i].getChave());
        assert(depoisDasRecusas[i].getVitoriasMD3() == antesDasRecusas[i].getVitoriasMD3());
        assert(depoisDasRecusas[i].getDerrotasMD3() == antesDasRecusas[i].getDerrotasMD3());
        assert(depoisDasRecusas[i].getJogosGanhos() == antesDasRecusas[i].getJogosGanhos());
        assert(depoisDasRecusas[i].getJogosPerdidos() == antesDasRecusas[i].getJogosPerdidos());
        assert(depoisDasRecusas[i].saldoJogos() == antesDasRecusas[i].saldoJogos());
    }
    std::vector<Partida> aceitas = md3.listarPartidas();
    assert(aceitas.size() == 1);
    assert(aceitas[0].getChaveTimeA() == "alpha");
    assert(aceitas[0].getChaveTimeB() == "beta");
    assert(aceitas[0].getJogosA() == 2);
    assert(aceitas[0].getJogosB() == 1);
    std::cout << "Repeticoes nas duas ordens, mesmo time, times inexistentes "
              << "e oito placares invalidos rejeitados sem alterar os dados.\n";

    // Os erros anteriores nao podem reservar o confronto Alpha x Gamma.
    assert(md3.registrarPartida("Alpha", "Gamma", 0, 2) == SUCESSO);
    assert(md3.registrarPartida("Beta", "Gamma", 1, 2) == SUCESSO);
    assert(md3.registrarPartida("Alpha", "Delta", 2, 0) == SUCESSO);

    // Confere acumulacao para os quatro times, inclusive quando B vence.
    const char* nomesEsperados[] = {"Alpha", "Beta", "Gamma", "Delta"};
    const int estatisticasEsperadas[][4] = {
        {2, 1, 4, 3}, {0, 2, 2, 4}, {2, 0, 4, 1}, {0, 1, 0, 2}
    };
    for (int i = 0; i < 4; ++i) {
        assert(md3.consultarTime(nomesEsperados[i], encontrado));
        assert(encontrado.getVitoriasMD3() == estatisticasEsperadas[i][0]);
        assert(encontrado.getDerrotasMD3() == estatisticasEsperadas[i][1]);
        assert(encontrado.getJogosGanhos() == estatisticasEsperadas[i][2]);
        assert(encontrado.getJogosPerdidos() == estatisticasEsperadas[i][3]);
        assert(encontrado.saldoJogos()
               == estatisticasEsperadas[i][2] - estatisticasEsperadas[i][3]);
    }

    const Campeonato& consultaMD3 = md3;
    aceitas = consultaMD3.listarPartidas();
    assert(aceitas.size() == 4);
    const char* adversariosEsperados[] = {"beta", "gamma", "gamma", "delta"};
    const int placaresEsperados[][2] = {{2, 1}, {0, 2}, {1, 2}, {2, 0}};
    std::cout << "Listagem de partidas aceitas, em ordem de registro:\n";
    for (int i = 0; i < 4; ++i) {
        assert(aceitas[i].getChaveTimeA() == (i == 2 ? "beta" : "alpha"));
        assert(aceitas[i].getChaveTimeB() == adversariosEsperados[i]);
        assert(aceitas[i].getJogosA() == placaresEsperados[i][0]);
        assert(aceitas[i].getJogosB() == placaresEsperados[i][1]);
        std::cout << aceitas[i].getChaveTimeA() << ' ' << aceitas[i].getJogosA()
                  << 'x' << aceitas[i].getJogosB() << ' '
                  << aceitas[i].getChaveTimeB() << '\n';
    }
    aceitas.clear();
    assert(consultaMD3.listarPartidas().size() == 4);
    assert(md3.registrarPartida(" gamma ", " ALPHA ", 2, 0) == CONFRONTO_REPETIDO);
    std::cout << "Os quatro placares validos foram aceitos; estatisticas acumuladas corretas.\n";
    std::cout << "Todos os testes da etapa 4 passaram.\n";

    const std::vector<Time> timesAntesDoHistorico = consultaMD3.listarTimes();
    const std::vector<Partida> partidasAntesDoHistorico = consultaMD3.listarPartidas();
    std::vector<Partida> historico;
    assert(consultaMD3.historicoTime("  aLpHa  ", historico));
    assert(historico.size() == 3);
    const int indicesAlpha[] = {0, 1, 3};
    std::cout << "Historico de Alpha (consulta com espacos e letras mistas):\n";
    for (int i = 0; i < 3; ++i) {
        const Partida& esperada = partidasAntesDoHistorico[indicesAlpha[i]];
        assert(historico[i].getChaveTimeA() == esperada.getChaveTimeA());
        assert(historico[i].getChaveTimeB() == esperada.getChaveTimeB());
        assert(historico[i].getJogosA() == esperada.getJogosA());
        assert(historico[i].getJogosB() == esperada.getJogosB());
        assert(historico[i].envolveTime("alpha"));
        std::cout << historico[i].getChaveTimeA() << ' ' << historico[i].getJogosA()
                  << 'x' << historico[i].getJogosB() << ' '
                  << historico[i].getChaveTimeB() << '\n';
    }

    // Reutiliza a saida: nao deve acumular resultados da consulta anterior.
    assert(consultaMD3.historicoTime(" GAMMA ", historico));
    assert(historico.size() == 2);
    for (int i = 0; i < 2; ++i) {
        const Partida& esperada = partidasAntesDoHistorico[i + 1];
        assert(historico[i].getChaveTimeA() == esperada.getChaveTimeA());
        assert(historico[i].getChaveTimeB() == "gamma");
        assert(historico[i].getJogosA() == esperada.getJogosA());
        assert(historico[i].getJogosB() == esperada.getJogosB());
    }
    std::cout << "Gamma: duas partidas encontradas como segundo participante.\n";

    assert(consulta.historicoTime(" ALPHA ", historico));
    assert(historico.empty());
    std::cout << "Time cadastrado sem partidas: retorno true e historico vazio.\n";

    historico = partidasAntesDoHistorico;
    assert(!consultaMD3.historicoTime(" Inexistente ", historico));
    assert(historico.empty());
    assert(!consultaMD3.historicoTime("", historico));
    assert(historico.empty());
    assert(!consultaMD3.historicoTime("   ", historico));
    assert(historico.empty());
    Campeonato campeonatoSemTimes;
    assert(!campeonatoSemTimes.historicoTime("Alpha", historico));
    assert(historico.empty());
    assert(campeonatoSemTimes.listarTimes().empty());
    std::cout << "Time inexistente: retorno false e historico vazio.\n";

    // Alterar as copias retornadas nao pode afetar o campeonato.
    assert(consultaMD3.historicoTime("Alpha", historico));
    historico[0] = Partida("outro", "time", 2, 0);
    historico.clear();
    assert(consultaMD3.historicoTime("Alpha", historico));
    assert(historico.size() == 3);
    assert(historico[0].getChaveTimeA() == "alpha");
    assert(historico[0].getChaveTimeB() == "beta");
    assert(historico[0].getJogosA() == 2);
    assert(historico[0].getJogosB() == 1);

    const std::vector<Time> timesDepoisDoHistorico = consultaMD3.listarTimes();
    assert(timesDepoisDoHistorico.size() == timesAntesDoHistorico.size());
    for (std::vector<Time>::size_type i = 0; i < timesAntesDoHistorico.size(); ++i) {
        assert(timesDepoisDoHistorico[i].getNome() == timesAntesDoHistorico[i].getNome());
        assert(timesDepoisDoHistorico[i].getChave() == timesAntesDoHistorico[i].getChave());
        assert(timesDepoisDoHistorico[i].getVitoriasMD3() == timesAntesDoHistorico[i].getVitoriasMD3());
        assert(timesDepoisDoHistorico[i].getDerrotasMD3() == timesAntesDoHistorico[i].getDerrotasMD3());
        assert(timesDepoisDoHistorico[i].getJogosGanhos() == timesAntesDoHistorico[i].getJogosGanhos());
        assert(timesDepoisDoHistorico[i].getJogosPerdidos() == timesAntesDoHistorico[i].getJogosPerdidos());
    }
    const std::vector<Partida> partidasDepoisDoHistorico = consultaMD3.listarPartidas();
    assert(partidasDepoisDoHistorico.size() == partidasAntesDoHistorico.size());
    for (std::vector<Partida>::size_type i = 0; i < partidasAntesDoHistorico.size(); ++i) {
        assert(partidasDepoisDoHistorico[i].getChaveTimeA() == partidasAntesDoHistorico[i].getChaveTimeA());
        assert(partidasDepoisDoHistorico[i].getChaveTimeB() == partidasAntesDoHistorico[i].getChaveTimeB());
        assert(partidasDepoisDoHistorico[i].getJogosA() == partidasAntesDoHistorico[i].getJogosA());
        assert(partidasDepoisDoHistorico[i].getJogosB() == partidasAntesDoHistorico[i].getJogosB());
    }
    std::cout << "Historicos preservam a ordem; consultas e alteracoes das copias nao mudam os dados.\n";
    std::cout << "Todos os testes da etapa 5 passaram.\n";
    return 0;
}
