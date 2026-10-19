Plano — Gerenciador de Campeonatos de Esports
1. Organização
Usar C++11 e somente a biblioteca padrão, sem new, delete, lambdas ou unordered_map.

Arquivos previstos	Responsabilidade
include/Time.hpp, src/Time.cpp	Nome e estatísticas de um time
include/Partida.hpp, src/Partida.cpp	Participantes e placar de uma MD3
include/Campeonato.hpp, src/Campeonato.cpp	Cadastro, resultados, consultas e classificação
include/Interface.hpp, src/Interface.cpp	Funções do menu, leitura e apresentação
src/main.cpp	Iniciar a interface
exemplos/*.txt	Entradas para testar o menu
Interface será um conjunto de funções, não uma classe adicional. Somente a interface usará cin e cout.

Não haverá persistência em arquivos, edição ou exclusão de resultados: essas funcionalidades não foram pedidas.

2. Classes, atributos e métodos
Time
Atributos privados:

std::string nome: nome de apresentação.
std::string chave: nome padronizado para identificar o time.
int vitoriasMD3, derrotasMD3.
int jogosGanhos, jogosPerdidos.
As estatísticas começam em zero.

Métodos previstos:

Construtor recebendo nome e chave.
Métodos de consulta dos atributos.
saldoJogos() const: jogos ganhos menos jogos perdidos.
registrarResultado(int ganhos, int perdidos): atualizar as estatísticas de uma MD3 já validada.
operator<(const Time& outro) const: definir a ordem de classificação.
O operator< colocará primeiro quem tiver:

Mais vitórias em MD3.
Maior saldo de jogos.
Mais jogos ganhos.
Menor nome padronizado em ordem alfabética.
Assim, std::sort poderá ordenar diretamente objetos Time, como exige o enunciado.

Partida
Atributos privados:

std::string chaveTimeA, chaveTimeB.
int jogosA, jogosB.
Guardar as chaves evita duplicar objetos Time e suas estatísticas dentro das partidas.

Métodos previstos:

Construtor recebendo participantes e placar.
Métodos de consulta dos atributos.
envolveTime(const std::string& chave) const: informar se o time participou.
static placarValido(int jogosA, int jogosB): aceitar somente 2x0, 2x1, 0x2 e 1x2.
Os nomes de apresentação serão consultados no campeonato pelas chaves.

Campeonato
Atributos privados:

Container	Conteúdo	Motivo
std::map<std::string, Time>	Chave padronizada → objeto Time	Buscar times e impedir nomes duplicados
std::vector<Partida>	Partidas registradas	Preservar a ordem de registro e facilitar listagem
std::set<std::pair<std::string, std::string>>	Confrontos realizados	Impedir que dois times se enfrentem novamente
No set, as duas chaves serão guardadas sempre em ordem crescente. Exemplo: Alpha x Beta e Beta x Alpha produzem o mesmo par.

Métodos públicos previstos:

cadastrarTime(nome): cadastrar ou indicar duplicidade.
consultarTime(nome, timeEncontrado) const: devolver sucesso ou falha e preencher uma cópia do time.
listarTimes() const: devolver std::vector<Time>.
registrarPartida(nomeA, nomeB, jogosA, jogosB): validar e registrar.
listarPartidas() const: devolver std::vector<Partida>.
historicoTime(nome, partidasEncontradas) const: distinguir time inexistente de histórico vazio.
classificacao() const: copiar os times para um vector e aplicar std::sort.
Métodos auxiliares privados:

Padronizar nomes.
Montar a chave do confronto, independentemente da ordem dos participantes.
O registro de partida devolverá um resultado enumerado, declarado em Campeonato.hpp, distinguindo:

Sucesso.
Time não cadastrado.
Mesmo time nos dois lados.
Placar inválido.
Confronto já realizado.
A interface transformará esses resultados em mensagens. Uma tentativa inválida não alterará estatísticas nem containers.

3. Detalhes que precisam de confirmação
**UPDATE :** Decisões adotadas para os nomes dos times :

- Os espaços no início e no final dos nomes são removidos.
- Nomes vazios ou compostos apenas por espaços são rejeitados.
- Letras maiúsculas e minúsculas de A a Z são consideradas equivalentes na identificação dos times.
- Espaços internos são preservados.
- Não foi implementada normalização específica de caracteres acentuados.

4. Etapas pequenas
Cada etapa deverá terminar compilando com o comando do README.md:

g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema

Nas etapas anteriores ao menu completo, src/main.cpp terá verificações pequenas e determinísticas. Quando o menu estiver disponível, os testes de entrada ficarão em exemplos/.

Etapa 1 — Time e estatísticas
Arquivos: Time.hpp, Time.cpp e main.cpp.

Implementar construção, consultas, saldo e atualização de estatísticas.

Teste: Alpha começa com tudo zerado. Após receber um resultado 2x1, deve ter uma vitória em MD3, dois jogos ganhos, um perdido e saldo 1.

Etapa 2 — Representação de partida
Arquivos: Partida.hpp, Partida.cpp e testes em main.cpp.

Implementar participantes, placar e consultas.

Testes: aceitar os quatro placares permitidos; rejeitar 3x0, 1x1 e valores negativos; verificar se uma partida envolve determinado time.

Etapa 3 — Cadastro e consulta de times
Arquivos: Campeonato.hpp, Campeonato.cpp e testes em main.cpp.

Implementar o map, a padronização acordada, o cadastro e as consultas.

Testes: cadastrar Alpha e Beta; recusar ALPHA após Alpha; consultar time inexistente; listar campeonato vazio.

Etapa 4 — Registro e listagem de partidas
Arquivos: Campeonato.hpp, Campeonato.cpp e testes em main.cpp.

Adicionar o vector, o set e todas as validações antes de atualizar os dados.

Testes:

Alpha vence Beta por 2x1: uma partida registrada e estatísticas corretas.
Recusar Beta x Alpha depois disso.
Recusar confronto consigo mesmo, time inexistente e placar inválido.
Confirmar que as recusas não mudam os dados.
Etapa 5 — Histórico por time
Arquivos: Campeonato.hpp, Campeonato.cpp e testes em main.cpp.

Filtrar as partidas usando Partida::envolveTime.

Testes: histórico com partidas, time cadastrado sem partidas e time inexistente.

Etapa 6 — Classificação
Arquivos: Time.hpp, Time.cpp, Campeonato.cpp e testes em main.cpp.

Implementar operator< e ordenar uma cópia dos times com std::sort.

Testes: verificar separadamente cada critério de desempate e a classificação vazia. Confirmar que ordenar não altera os cadastros.

Etapa 7 — Interface e testes completos
Arquivos: Interface.hpp, Interface.cpp, main.cpp e exemplos/*.txt.

Criar menu para cadastrar, listar times, registrar e listar partidas, mostrar classificação, consultar histórico e sair.

A leitura deverá aceitar nomes com espaços e permitir nova tentativa após entrada numérica inválida. O fim da entrada deverá encerrar o programa sem repetição infinita.

Cenários de teste:

Exemplo Alpha x Beta da descrição.
Listas vazias.
Duplicidade de nome com diferença de maiúsculas.
Todos os erros de registro.
Histórico de time inexistente.
Letra no lugar de número e opção inválida.
Após cada etapa de implementação: compilar, executar os testes disponíveis e informar os resultados reais. As seções autorais do README.md e DESCRICAO.md permanecerão intactas.