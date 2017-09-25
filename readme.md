Atividade da Disciplina de Sistemas Operacionais do 4o Semestre do IFSP - Araraquara <br>
Alunos: Bruno Siqueira, Guilherme Rodrigues e Renan Braga <br>
Professor: Lourenço <br>

exemplos

Documentação:

Índice

 make        ------------------------ 1
 ls          ------------------------ 2
 cat         ------------------------ 3
 cp          ------------------------ 4
 mv          ------------------------ 5
 echo        ------------------------ 6
  |          ------------------------ 7
  >          ------------------------ 8
  "<"        ------------------------ 9
 exit        ------------------------ 10

1) make
O comando make compilará o programa gerando um arquivo de saída chamado minishell
, o qual poderá ser inicializado através da saída padrão, ou seja, ./minishel.

2) ls
O comando listará os arquivos existentes no diretório atual

3) cat
O comando reproduzirá o conteúdo do arquivo na saída padrão, seguindo o modelo cat <arquivo>

4) cp
O comando criará uma copia de um arquivo para outro local cp <enderço_arquivo> <endereço_copia>

5) mv
O comando movimentará o arquivo de um diretŕio para outro, seguindo o modelo mv <endereço_arquivo> <endereço_destino>

6) echo
O comando reproduzirá o que for digitado subsequentemente echo <mensagem_repetida>

7) | 
O comando interligará o resultado de uma saípa para outro contexto. Exemplo ls | echo "teste" > txt

8) >
O comando > passará o conteúdo do que está a esquerda dele para o arquivo da direita, seguindo o modelo <dado_alvo> > <dado_destino>

9) <
O comando < passará o conteúdo do que está a direita dele para o que está à esquera, seguindo o modelo <dado_destino> < <dado_alvo>

10) exit
O comando finaliza a execução do minishell
