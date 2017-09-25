<b>Atividade da Disciplina de Sistemas Operacionais do 4o Semestre do IFSP - Araraquara</b><br>
Alunos: Bruno Siqueira, Guilherme Rodrigues e Renan Braga <br>
Professor: Lourenço <br>


Documentação:<br><br>

Índice<br>

 make        ------------------------ 1<br>
 ls          ------------------------ 2<br>
 cat         ------------------------ 3<br>
 cp          ------------------------ 4<br>
 mv          ------------------------ 5<br>
 echo        ------------------------ 6<br>
  |          ------------------------ 7<br>
  ">"        ------------------------ 8<br>
  "<"        ------------------------ 9<br>
 exit        ------------------------ 10<br>

1) make<br>
O comando make compilará o programa gerando um arquivo de saída chamado minishell
, o qual poderá ser inicializado através da saída padrão, ou seja, ./minishel.<br><br>

2) ls<br>
O comando listará os arquivos existentes no diretório atual<br><br>

3) cat<br>
O comando reproduzirá o conteúdo do arquivo na saída padrão, seguindo o modelo cat <arquivo><br><br>

4) cp<br>
O comando criará uma copia de um arquivo para outro local cp <enderço_arquivo> <endereço_copia><br><br>

5) mv<br>
O comando movimentará o arquivo de um diretŕio para outro, seguindo o modelo mv <endereço_arquivo> <endereço_destino><br><br>

6) echo<br>
O comando reproduzirá o que for digitado subsequentemente echo <mensagem_repetida><br><br>

7) | <br>
O comando interligará o resultado de uma saípa para outro contexto. Exemplo ls | echo "teste" > txt<br><br>

8) ><br>
O comando > passará o conteúdo do que está a esquerda dele para o arquivo da direita, seguindo o modelo <dado_alvo> > <dado_destino><br><br>

9) <<br>
O comando < passará o conteúdo do que está a direita dele para o que está à esquera, seguindo o modelo <dado_destino> < <dado_alvo><br><br>

10) exit<br>
O comando finaliza a execução do minishell<br><br>
