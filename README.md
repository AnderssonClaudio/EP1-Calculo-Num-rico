# EP1-Calculo-Numerico
Exercício programa I - Cadeira de cálculo numérico 2018.1

 == Descricao ==
 
Programa em C com um menu principal que possui 3 opções: ‘C’ – Conversão, ‘S’ – Sistema Linear e ‘F’ – Finalizar.
 
 Ao selecionar a opção ‘C’, o usuario devera digitar um numero decimal, eventualmente com parte fracionaria, e o programa devera exibir esse número no sistema numérico binario, octal e hexadecimal, com ate 20 casas decimais.
 
 Ao selecionar a opção ‘S’, o programa deverá pedir o nome de um arquivo de texto contendo um sistema linear de n equações e n variáveis. O lay-out do arquivo deverá ser:
 
 n
 a1,1 a1,2 ... a1,n b1
 a2,1 a2,2 ... a2,n b2
 ...
 an,1 an,2 ... an,n bn
 
 onde ai,j e o coeficiente da variavel i na equação j e bj e o termo independente da equação j. Por exemplo, o arquivo correspondente ao sistema:
 
 x1 –  x2 + 3x3 =  8
 2x1 – 2x2 +  x3 =  1
 –x1 + 3x2 –  x3 =  2
 
 seria
 
 3
 1 -1  3  8
 2 -2  1  1
 -1  3 -1  2
 
 O programa devera então transformar a matriz de coeficientes numa matriz diagonal usando o Metodo de Jordan. Se o sistema for compativel, exiba a matriz diagonal e uma solução do sistema.
 Se na iteração k do metodo, ak,k for zero, troque a coluna k com uma coluna j tal que k < j = n e ak,j != 0. Lembre-se de que, nesse caso, a coluna k correspondera a variável xj e a coluna j correspondera a variavel xk.
    Se todos os elementos da linha k forem iguais a zero (inclusive o termo independente), a variável xk e livre. Nesse caso, considere seu valor igual a zero e substitua a coluna k da matriz por uma coluna de zeros.
  Se todos os elementos da linha k, menos o termo independente, forem iguais a zero, o sistema será incompatível. Nesse caso, apenas informe que o sistema e incompativel.
