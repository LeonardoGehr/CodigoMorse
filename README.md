# Codigo Morse

Trabalho TDE 2 de Estruturas de Dados, em C.

## Feito agora

Menu no terminal, arvore binaria dinamica com as letras A-Z e os numeros 0-9, codificacao e decodificacao de mensagens completas e diagrama da arvore. As opcoes 3 e 4 leem arquivos e imprimem o resultado no terminal.
Requer GCC com suporte a C11. Nao utiliza bibliotecas externas. As conversoes e os arquivos de exemplo foram testados durante o desenvolvimento.

## Compilar e executar

    gcc -std=c11 -Wall -Wextra -Wpedantic src/main.c -o programa.exe
    .\programa.exe

No terminal MSYS2 UCRT64, executar ./programa.exe. No Linux, usar -o programa e executar ./programa.

## Formato das mensagens

Texto: letras A-Z (maiusculas ou minusculas), numeros e espacos. Acentos e pontuacao sao rejeitados.
Morse: ponto, traco, barra e espaco. Um espaco separa letras; cada barra representa um espaco do texto. Espacos repetidos no texto geram barras repetidas.
Exemplo: OLA MUNDO -> --- .-.. .- / -- ..- -. -.. ---
Entrada pelo menu: ate 1023 caracteres por linha.

## Arquivos


A opcao 3 aceita texto em varias linhas e converte cada quebra de linha em um espaco (CRLF conta como uma quebra).
A opcao 4 exige somente ponto, traco, barra e espaco: quebras de linha, inclusive no final do arquivo, tabulacoes e outros caracteres sao rejeitados.
Arquivos vazios, bytes nulos, falhas de leitura e memoria insuficiente sao tratados. Os arquivos sao lidos com memoria dinamica.


## Testes manuais

1. Opcao 1: SOS deve produzir ... --- ...; ola mundo deve produzir --- .-.. .- / -- ..- -. -.. ---.
2. Opcao 2: as mensagens acima devem produzir SOS e OLA MUNDO.
3. Verificar A-Z e 0-9 e preservar espacos repetidos: A  B deve produzir .- / / -... e voltar a A  B.
4. Opcao 3 com texto_teste.dat: deve produzir --- .-.. .- / -- ..- -. -.. ---.
5. Opcao 4 com morse_teste.dat: deve produzir OLA MUNDO.
6. Opcao 4 com morse_invalido.dat: deve rejeitar a quebra de linha.
7. Arquivo inexistente ou vazio: deve exibir erro e voltar ao menu.
8. Texto com ! ou acentos, Morse com letras ou ......: devem ser rejeitados.
9. Opcao 5: conferir raiz, ponto a esquerda, traco a direita e os numeros nos niveis finais.
10. Opcoes abc, 9 e numeros muito grandes: devem ser rejeitados; 0 encerra.

## Referencias e apoio

- Enunciado da atividade: TDE_2_ED_14h_v1.1.pdf e orientacoes do AVA.
- Video de apoio indicado no enunciado: Morse code and binary trees - Inside code (https://www.youtube.com/watch?v=BqeX-4TshEA).
- Video complementar: How to solve (almost) any binary tree coding problem - Inside code (https://www.youtube.com/watch?v=s2Yyk3qdy3o).
- Desenvolvimento realizado com apoio de IA para planejamento e revisao.

## Diagrama de apoio

Arvore binaria completa do Codigo Morse (docs/arvore_morse.png)

Imagem gerada com IA, para apoio. Representa as letras A-Z e os numeros 0-9: ponto segue a esquerda, traco segue a direita; o simbolo de conjunto vazio indica um no intermediario sem caractere. A imagem e uma ilustracao estatica; a opcao 5 do programa mostra a arvore construida durante a execucao.

## Documentacao complementar consultada na revisao

- malloc - Microsoft Learn (https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc)
- realloc - Microsoft Learn (https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/realloc)
- Referencia da ilustracao: arvore_morse.png (docs/arvore_morse.png), gerada por IA neste projeto.