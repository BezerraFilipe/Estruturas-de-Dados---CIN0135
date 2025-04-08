[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/rdQPkNim)
# Árvores de Expressões Aritméticas

Neste exercício vamos trabalhar com uma forma particular de expressões aritméticas infixas **EAI** obedecendo as seguintes regras

1. Uma constante inteira não-negativa é uma EAI
2. Se `X` é uma EAI, então `~X` também é uma EAI (menos unário)
3. Se `X` e `Y` são EAIs, então 
	- `(X+Y)` (soma) 
	- `(X-Y)` (subtração)
	- `(X*Y)` (multiplicação) e 
	- `(X/Y)` (divisão) 
	
	também são EAI.

Nada fora dessas formas pode ser considerado uma EAI. 

**ATENÇÃO**: por simplicidade, usamos um símbolo distinto `~` para "menos unário" (inversão de sinal), diferente do operador binário de subtração. Assim, temos que `~X = (0-X)`.

**Exemplos de Expressões Válidas**

- `12`
- `~000`
- `(12*13)`
- `(45/(78-78))` é uma EAI válida, embora represente uma divisão por zero
- `((~4*(1+3))/29)`
~ `(~~~123~~~123)`

**Exemplos de Expressões Inválidas**

- `(12)` : ❌ pela regra 1, uma constante não tem parênteses
- `(~1)` : ❌ pela regra 2, não tem parênteses
- `(20~12)` : ❌ `~` é um operador unário
- `+56` : ❌ o `+` só é usado como operador binário
- `123*45`: ❌ pela regra 3, faltam os parênteses

Essas EAI utilizam parênteses para disbambiguar as operações. Por exemplo, sem os parênteses, a expressão 
```
45/78-78
``` 
poderia ser interpretada como
```
((45/78)-78)
``` 
ou
```
(45/(78-78))
```

### Árvores sintáticas 

Uma EAI pode ser representada por uma árvore binária da seguinte de acordo com as seguintes regras:

1. Se a EAI `X` é uma constante inteira não-negativa, então corresponde à árvore
```
        .-----.
T(X) :  |  X  |
        '/---\'
        =     =
```
ou seja, um nó único com valor `X`  

2. Se a EAI `Y` é da forma `~X`, então corresponde à árvore

```
        .-----.
T(Y) :  |  ~  |
        '/---\'
        =   T(X)  
```
ou seja, uma raiz com o operador "menos unário", sem filho à esquerda, e com a árvore de `X` como sub-árvore à direita.

3. Se `Z` é uma EAI do tipo `(X?Y)`, onde `?` representa um dos operadores binários `-`, `+`, `*` ou `/`, então corresponde à árvore
```
        .-----.
T(Z) :  |  ?  |
        '/---\'
      T(X)   T(Y)  
```
ou seja, uma raiz com o operador binário representado pelo `?` , e com as árvores de `X` e `Y` como sub-árvores à esquerda e à direita respectivamente.

**Exemplo**

Se `X = ((~45/78)-78)`, então a árvore `T(X)` é 
```
      [-]
     /   \
   [/]    [78]
  /   \
[~]   [78]
  \
  [45]
``` 
ao passo que se  `Y = (~45/(78-78)`, então a árvore `T(Y)` é 
```
     [/]
    /   \
 [~]     [-]
  \      /  \
  [45] [78] [78]
``` 

Repare que não é necessário armazenar os parênteses nos nós das árvores pois a própria estrutura impõe uma ordem de interpretação da expressão. A expressão original também pode ser obtida através da árvore por um **percurso em ordem**, tomando-se o cuidado de colocar os parênteses quando necessário.

```
function print_infix_expression(root) {
	if root == NULL
		return 
	else if root has a number
		print root.val
	else if root is a unary '~'
		print root.val // "~" 
		print_infix_expression(root.right)
	else // root is a binary operator
		print "("
		print_infix_expression(root.left)
		print root.val 
		print_infix_expression(root.left)
		print ")"
}
```

### Notação pós-fixa

As EAI descritas acima adotam a forma **infixa** na qual os operadores são escritos **entre** os operandos. O operador `~` unário pode ser visto como um caso particular em que o operando de esquerda é um `0` que é omitido (isto é `~X` seria equivalente a `(0~X)`). Uma outra possibilidade é escrever expressões na forma **pós-fixa** em que o operador vem depois dos operandos. As regras para as Expressões Aritméticas Pós-fixas **EAP** são as seguintes:

1. Uma constante inteira não-negativa é uma EAP
2. Se `X` é uma EAP, então `X ~` também é uma EAP (menos unário)
3. Se `X` e `Y` são EAPs, então 
	- `X Y +` (soma) 
	- `X Y -` (subtração)
	- `X Y *` (multiplicação) e 
	- `X Y /` (divisão) 
	
	também são EAPs.

**Exemplos de Expressões Válidas**

- `12`
- `000 ~`
- `12 13 *`
- `45 78 78 - /` é uma EAP válida, embora represente uma divisão por zero
- `4 ~ 1 3 + * 29 /`
~ `123 ~ ~ ~ 123 ~ ~ ~`

Essas EAPs são equivalentes às EAIs válidas acima, porém, diferentemente das EAIs, as EAPs não necessitam parênteses para desambibuação. Por exemplo, a quarta EAP `45 78 78 - /` corresponde à EAI `(45/(78-78))` sem risco de ambiguidade, uma vez que a EAI `((45/78)-78)` corresponderia a uma outra EAP `45 78 / 78 -`.

Tanto a EAI como sua equivalente EAP correspondem à mesma árvore, conforme descrito acima. A EAP pode ser obtida por um percurso em **pós-ordem** da árvore.

A árvore pode ser obtida diretamente a partir da EAP com o auxílio de uma **pilha**, inicialmente vazia. Para cada item `tok` da EAP:
- Se `tok` corresponde a uma constante numérica `X` (não negativa), empilha um nó com valor `X` sem filhos
- Se `tok` é um `~` (operador menos unário):
	- Desempilha o nó `R` do topo da pilha
	- Empilha um novo nó raiz com rótulo `tok` (`~`) e com filhos à direita `R` apenas
- Se `tok` é um `+`, `*`, ou `/` (operador binário):
	- Desempilha o nó `R` do topo da pilha
	- Desempilha o nó `L` do topo da pilha
	- Empilha um novo nó raiz com rótulo `tok` (o operador binário) e com filhos à esquerda e direita `L` e `R` respectivamente

Ao final, a raiz da árvore representando a expressão será o nó no topo da pilha.

## Entrada

A entrada é constituída de várias expressões aritméticas e inicia com um inteiro
```
N
```
correspondente ao número de expressões.
Seguem-se `N` expressões na seguinte forma
```
M
X
```
onde `M` é um caractere designando o "modo" da expressão
- `I` = infixa
- `P` = pós-fixa

e `X` é a expressão **válida** propriamente dita.

## Saída

Para cada expressão `X` da entrada, o programa deve imprimir

```
X'
H V
```
onde 

- `X'` é a expressão equivalente no formato alternativo, isto é, se `X` é infixa, então `X'` é pós-fixa, e vice versa
- `H` é a **altura** da árvore sintática de `X`
- `V` é o valor numérico da expressão.

**IMPORTANTE**: 
1. Considere as divisões como aritmética inteira com truncagem, e.g. `(10/-4) = -2` e `(-4/10) = 0`
2. Caso a expressão contenha alguma divisão por `0` imprimir `?` no lugar de `V`


## Instruções de Implementação

- Completar o arquivo [exprtree.hpp](./exprtree.hpp) que contém as definições dos tipos usados na solução:
- Completar o arquivo [solver.cpp](./solver.cpp) que é usado para gerar o executável da solução.
- Não alterar o arquivo [sanity.cpp](./sanity.cpp)
- Não alterar os arquivos de entradas/saidas de teste (*.in, *.out)
- **FAZER COMMIT APENAS DAS MODIFICAÇÕES DOS ARQUIVOS [exprtree.hpp](./exprtree.hpp) e [solver.cpp](./solver.cpp)**. **NÃO ADICIONAR NOVOS ARQUIVOS AO REPOSITÓRIO**.