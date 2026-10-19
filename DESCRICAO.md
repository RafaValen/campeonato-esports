## Descrição do sistema

O Gerenciador de Campeonatos de Esports é um sistema desenvolvido em C++11 que permite cadastrar times, registrar resultados de partidas MD3 (melhor de três), consultar o histórico dos confrontos e visualizar a classificação das equipes com base em suas vitórias e critérios de desempate.

**Uma frase dizendo o que o sistema faz:**

O sistema organiza campeonatos de esports, registrando partidas e resultados para gerar a classificação dos times.

## Nome e ideia

O sistema vai se chamar Gerenciador de Campeonatos de Esports. A ideia é ajudar a organizar campeonatos de jogos competitivos, tipo Honor of Kings, cadastrando times, resultados das partidas e mostrando a classificação. É mais voltado pra quem organiza esses campeonatos

## O que o sistema guarda

O sistema vai guardar os nomes dos times, quantas MD3 cada um ganhou ou perdeu e a quantidade de jogos ganhos e perdidos.

Também vai guardar as partidas que aconteceram, quais times jogaram e o placar de cada uma.

## O que dá para fazer

Cadastrar os times que vão participar.

Ver todos os times cadastrados.

Registrar o resultado de uma MD3 entre dois times.

Ver as partidas que já aconteceram e seus placares.

Ver a classificação geral dos times.

Consultar o histórico de partidas de um time específico.

Sair do programa.


## Regras

As partidas vão ser MD3, ou seja, quem ganhar 2 jogos vence.

Os placares possíveis são 2x0, 2x1, 0x2 e 1x2.

A classificação vai ser pela quantidade de MD3 vencidas.

Se tiver empate, vai contar o saldo de jogos (vitórias menos derrotas nos jogos).

Se continuar empatado, fica na frente quem tiver mais jogos vencidos.

Se ainda empatar, vai pela ordem alfabética.

Não pode ter dois times com o mesmo nome, mesmo usando letras maiúsculas ou minúsculas.

Um time não pode jogar contra ele mesmo.

Só pode registrar partidas de times cadastrados.

Cada time só pode enfrentar outro uma vez. Ex: Alpha x Beta é a mesma coisa que Beta x Alpha.

## Quando algo dá errado

Se tentar cadastrar um time que já existe, o programa vai avisar.

Se tentar colocar um time que não foi cadastrado em uma partida, vai dar erro e não vai registrar.

Se tentar registrar uma partida repetida ou um time contra ele mesmo, o programa não vai deixar.

Se colocar um placar errado, tipo 3x0 ou 1x1, vai avisar que não é válido.

Se procurar um time que não existe, vai mostrar uma mensagem avisando.

Se não tiver nenhum time ou partida cadastrada, vai informar que a lista tá vazia.

Se digitar letra onde deveria ser número ou escolher uma opção que não existe, vai avisar do erro e deixar tentar de novo.

## Classes que eu imagino

Time: vai guardar o nome do time e as estatísticas dele, tipo vitórias e derrotas.

Partida: vai guardar os dois times que jogaram e o resultado da MD3.

Campeonato: vai controlar os times, as partidas e a classificação, além de verificar se um confronto já aconteceu.

## Exemplo de uso

Quando abrir o programa, vai aparecer um menu com as opções.

Primeiro eu cadastro o time Alpha e depois o Beta.

Depois vou na opção de registrar partida, escolho Alpha e Beta e coloco o resultado 2x1.

O programa registra que Alpha ganhou a MD3.

Quando eu abrir a classificação, Alpha vai estar em primeiro com 1 vitória e Beta em segundo com 1 derrota.

Se eu tentar registrar Beta x Alpha de novo, o programa vai avisar que essa partida já aconteceu.

Também vou poder consultar o histórico do Alpha e ver que ele ganhou do Beta por 2x1.