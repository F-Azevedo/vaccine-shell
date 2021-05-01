# Trabalho 1 - Sistemas Operacionais
###### Universidade Federal do Espirito Santo

---
### Autores:
* Fernando Azevedo Peres
* Igor Mattos dos Santos Varejão
* Luís Eduardo Freire da Câmara

### Data:
Maio de 2021 <br>
4° Período (2020/2)

---
### Descrição:
Vaccine shell implemented with C language.

A VSH deve ser vacinada contra os sinais SIGUSR1 e SIGUSR2, porém não é uma vacina 100% efetiva, contendo efeitos colaterais. Então ao receber esses sinais, a VSH deve mostrar uma mensagem contendo o Zeca.

Os processos de foreground devem ser vacinados, com uma com uma vacina perfeita. Portanto, devem ignorar os sinais recebidos.

Já os processos em background, não são vacinados. Portanto, ao receber os sinais devem contaminar todo o seu grupo, causando a morte do mesmo.

---
### Resolução

##### Exemplo do resultado final:
![Erro](https://github.com/ivarejao/T1-SO/blob/main/imagens/Implementacao.png "Implementação")

##### Exemplo de recebimento de SIGUSR1 ou SIGUSR2 pela VSH:

![Erro](https://github.com/ivarejao/T1-SO/blob/main/imagens/Recebeu_Sinal.png "Exemplo de recebimento de sinal")

##### Foto individual do Zeca.
![Erro](https://github.com/ivarejao/T1-SO/blob/main/imagens/Zeca.png "Zeca")