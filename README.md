# Codigo Morse

Trabalho TDE 2 de Estruturas de Dados, em C.

## Feito agora

Menu no terminal, arvore binaria dinamica com as letras A-Z e os numeros 0-9, codificacao e decodificacao de mensagens completas e diagrama da arvore. Leitura de arquivos ainda nao foi implementada.
A versao inicial do menu foi compilada e testada; esta etapa deve ser validada antes do commit.

## Compilar e executar

    gcc -std=c11 -Wall -Wextra -Wpedantic src/main.c -o programa.exe
    .\programa.exe

No terminal MSYS2 UCRT64, executar ./programa.exe. No Linux, usar -o programa e executar ./programa.

## Formato das mensagens

Texto: letras A-Z (maiusculas ou minusculas), numeros e espacos. Acentos e pontuacao sao rejeitados.
Morse: ponto, traco, barra e espaco. Um espaco separa letras; cada barra representa um espaco do texto. Espacos repetidos no texto geram barras repetidas.
Exemplo: OLA MUNDO -> --- .-.. .- / -- ..- -. -.. ---
Entrada pelo menu: ate 1023 caracteres por linha.
