
# Semi-aberto

## Descrição

Num planeta de uma galáxia distante, os cemitérios são verticais, organizados em `M` andares numerados `0,...,M-1`. A tradição local manda que qualquer edifício público, como os cemitérios, tenha uma quantidade ímpar de andares, no mínimo 13 (número da sorte local). Cada andar `F=0,..,M-1` dispõe de uma quantidade limitada `L` de jazigos, rotulados `F.0, F.1,..., F.(L-1)`. 

Quando um indivíduo desse planeta morre, ele é levado para o cemitério da sua área de residência e colocado num jazigo com base numa chave numérica única `K` correspondente ao seu número de seguro social, de acordo com a seguinte política:

1. Primeiro, um andar `H(K)` escolhido de acordo com a regra 
`H(K) = K mod M`;
2. Se houver ainda algum jazigo disponível neste andar, o corpo é inserido de forma que os jazigos estejam ocupados em ordem crescente pelo no. de seguro social, isto é, para qualquer andar `F`, temos 
`F.0.K < F.1.K < ... < F.(B-1).K`, onde `B` é o número de jazigos ocupados no andar e `F.J.K` indica o número do seguro social do ocupante do jazigo `F.J`
3. Se não houver mais nenhum jazigo disponível no andar , a lei local manda que um novo prédio de `2M+1` andares, e com `2*L` túmulos por andar, seja imediatamente construído no local (a tecnologia é avançadíssima e a construção é imediatamente feita por robôs) e todos os corpos de todos os jazigos,  do primeiro ao último andar, e por ordem em cada andar, são recolocados novo prédio de acordo com esta mesma política. 
**IMPORTANTE**: durante a redistribuição, os túmulos vazios são ignorados. Depois que todos os corpos forem realocados, o novo corpo recém-chegado é acomodado. O antigo cemitério é então demolido e substituído pelo novo.

É também muito comum pelos costumes locais que, após algum tempo, as famílias retirem os restos mortais dos seus entes queridos para cremá-los e jogarem as cinzas ao mar. Entretanto, a religião local proíbe que um mesmo jazigo seja utilizado por mais de uma pessoa e, portanto, uma vez removidos os despojos, o túmulo é lacrado e fica inutilizado. Após a retirada, o jazigo já não está de fato ocupado mas, para efeito de ordenação, esse túmulo mantém o no. do seguro social do seu ex-ocupante e continua indisponível.

A administração precisa então desenvolver um sistema informático que, entre outras coisas, permita descobrir rapidamente em qual jazigo repousa o corpo de um indivíduo dado seu número de seguro social, ou indicar que essa pessoa não está no cemitério.

## Formato de entrada

A primeira linha  da entrada é constituída por dois inteiros
```
M L
```
correspondentes ao número inicial de andares e ao número de jazigos por andar do cemitério, respectivamente. Supõe-se que o cemitério esteja inicialmente vazio.

Seguem-se  `N` linhas, cada linha correspondente a uma operação numa das formas a seguir

* `ADD K` = adiciona o indivíduo com chave `K` ao cemitério
* `REM K` = remove o corpo com chave `K` do cemitério, se ele estiver no cemitério
* `QRY K` = retorna o jazigo do corpo com chave `K`, se houver

A entrada termina com uma linha 

```
END
```

## Formato de saída

Para cada operação na entrada, deve ser impressa uma linha dois inteiros na forma

```
F.J
```

onde `F` corresponde ao andar e `J` o no. do jazigo correspondente à operação:

- `ADD K` --> jazigo no qual o indivíduo com chave `K` foi colocado
- `REM K` --> jazigo do qual os despojos com chave `K` foram removidos
- `QRY K` --> jazigo no qual encontra-se o corpo com chave `K`

No caso das operações `REM` ou `QRY`, caso o indivíduo com seguro social `K` não esteja no cemitério (incluindo o caso em que foi retirado para cremação), deve ser impressa uma linha

```
?.?
```

## Instruções de Implementação

- Completar o arquivo [cemetery.hpp](./cemetery.hpp) que contém as definições dos tipos usados na solução:
- Completar o arquivo [solver.cpp](./solver.cpp) que é usado para gerar o executável da solução.
- Não alterar o arquivo [sanity.cpp](./sanity.cpp)
- Não alterar os arquivos de entradas/saidas de teste (*.in, *.out)
- **FAZER COMMIT APENAS DAS MODIFICAÇÕES DOS ARQUIVOS [cemetery.hpp](./cemetery.hpp) e [solver.cpp](./solver.cpp)**. **NÃO ADICIONAR NOVOS ARQUIVOS AO REPOSITÓRIO**.
