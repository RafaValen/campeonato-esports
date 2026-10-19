# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

Na etapa 6, `src/*.cpp` inclui `src/Time.cpp`, `src/Partida.cpp`,
`src/Campeonato.cpp` e `src/main.cpp`.
O executável mantém os testes anteriores com `assert` e acrescenta testes de
cadastro, consulta e listagem de times: campeonato vazio, nomes inválidos,
duplicidade, remoção de espaços nas extremidades e comparação sem diferenciar
maiúsculas e minúsculas de A a Z. Não há tratamento especial de acentos.
Também testa o registro e a listagem de MD3, os quatro placares válidos,
as estatísticas dos dois participantes e a rejeição de confrontos repetidos
(nas duas ordens), times inexistentes, confronto consigo mesmo e placares
inválidos, verificando que as recusas não alteram os dados.
Os testes de histórico verificam a normalização do nome, a filtragem dos dois
participantes, a ordem de registro e a diferença entre time inexistente
(`false`) e time cadastrado sem partidas (`true` com vetor vazio).
Também conferem que o vetor de saída é substituído a cada consulta e que
as consultas e alterações das cópias não modificam os dados do campeonato.
Os testes de classificação usam `std::sort` com `Time::operator<` e verificam
campeonato vazio, times sem partidas e cada critério na ordem: MD3 vencidas,
saldo de jogos, jogos ganhos e nome normalizado. Também comparam o cadastro
antes e depois da classificação e de alterações na cópia retornada.

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| --- | --- | --- |
| | | |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado:
- Um pedido que deu certo, e por que você acha que deu certo:
- Um pedido que deu errado, o que veio errado e como você mudou o pedido:
- Uma coisa que a IA sugeriu e você recusou, e por quê:
