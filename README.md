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

O programa usa C++11 e somente a biblioteca padrão. `src/*.cpp` inclui as
três classes, `src/Interface.cpp` e o ponto de entrada `src/main.cpp`.
Os dados ficam somente na memória e são perdidos ao encerrar.

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Menu: 1 cadastrar time, 2 listar times, 3 registrar MD3, 4 listar partidas,
5 classificação, 6 histórico, 0 sair. Digite cada nome ou número em uma linha.
No registro de MD3, informe os nomes A e B e depois os jogos ganhos por A e B
separadamente (por exemplo, `2` e `1`, não `2x1`). Nomes aceitam espaços;
a comparação ignora maiúsculas/minúsculas de A a Z e espaços nas extremidades,
sem tratamento especial de acentos. Entradas numéricas inválidas permitem
nova tentativa; fim da entrada encerra sem registrar uma MD3 incompleta.

### Testes das classes

Todos os testes das etapas 1 a 6 foram preservados em `tests/testes.cpp`.
Compile separadamente, sem `src/main.cpp`, para não duplicar o ponto de entrada.
Não use `-DNDEBUG`, pois os testes usam `assert`.

```bash
g++ -std=c++11 -Wall -Wextra tests/testes.cpp src/Time.cpp src/Partida.cpp src/Campeonato.cpp -Iinclude -o testes
./testes
```

### Exemplos do menu

- `exemplos/normal.txt`: todas as opções, Alpha 2x1 Beta, classificação,
  histórico e time sem partidas; inclui nomes com espaços.
- `exemplos/erros.txt`: listas vazias, nome inválido, duplicado, time
  inexistente, mesmo time, placares inválidos, confronto invertido repetido,
  opção inexistente, letras, número com sufixo e inteiro fora do alcance.
- `exemplos/fim_entrada.txt`: fim da entrada no meio de uma MD3.

No Bash ou Prompt de Comando, use redirecionamento:

```bash
./sistema < exemplos/normal.txt
./sistema < exemplos/erros.txt
./sistema < exemplos/fim_entrada.txt
```

No PowerShell do Windows:

```powershell
.\sistema.exe
.\testes.exe
cmd /c "sistema.exe < exemplos\normal.txt"
cmd /c "sistema.exe < exemplos\erros.txt"
cmd /c "sistema.exe < exemplos\fim_entrada.txt"
```

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
