# Codigo Morse

Trabalho TDE 2 de Estruturas de Dados, em C.

## Feito agora

Menu no terminal, arvore binaria dinamica com as letras A-Z e os numeros 0-9, codificacao e decodificacao de mensagens completas e diagrama da arvore. As opcoes 3 e 4 leem arquivos e imprimem o resultado no terminal.
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

## Arquivos

Informe o caminho sem aspas. Caminhos relativos partem da pasta em que o programa foi iniciado.
A opcao 3 aceita texto em varias linhas e converte cada quebra de linha em um espaco (CRLF conta como uma quebra).
A opcao 4 exige somente ponto, traco, barra e espaco: quebras de linha, inclusive no final do arquivo, tabulacoes e outros caracteres sao rejeitados.
Arquivos vazios, bytes nulos, falhas de leitura e memoria insuficiente sao tratados. Os arquivos sao lidos com memoria dinamica.

## Referencias e apoio

Enunciado da atividade TDE 2. Desenvolvimento com apoio de IA (Codex).
