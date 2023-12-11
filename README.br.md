# PatternExtractor - Laboratório de Programação 2023-2

_Leia isso em outros idiomas: [English](README.en.md), [Português](README.md)._

Bem-vindo ao projeto **PatternExtractor**, organizado pelo **Professor Daniel Ferreira no IFCE**.

## Visão Geral
O projeto **PatternExtractor** é parte do Laboratório de Programação do segundo semestre de 2023. O objetivo deste projeto é desenvolver uma solução baseada em IA para extrair e analisar padrões de conjuntos de dados.

## Propósito
O objetivo principal do **PatternExtractor** é criar uma ferramenta que possa identificar e extrair automaticamente padrões significativos de conjuntos de dados médicos.

## Tecnologias
> **Nota:** Embora seja incentivada uma grande precisão, não seremos avaliados na "parte de IA do código".
Usaremos principalmente C e Weka.

Weka é uma suíte de software de código aberto projetada para tarefas de mineração de dados e aprendizado de máquina desenvolvida na Universidade de Waikato, Nova Zelândia.

Saiba mais aqui: [WEKA](https://www.cs.waikato.ac.nz/ml/weka/index.html)

## Execução do Código

### Pré-requisitos

Certifique-se de ter os seguintes pré-requisitos instalados no seu sistema:

- Linux é recomendado.

### Executando o Código

Siga estas etapas para executar o código:

- **Passo 1:** Clone o repositório para sua máquina local.

    ```bash
    git clone https://github.com/maripasa/PatternExtractor.git
    ```

- **Passo 2:** Navegue até o diretório do projeto.

    ```bash
    cd PatternExtractor
    ```
   
- **Passo 3:** Execute o programa.

    ```bash
    # Exemplo de comando para executar o SCM_Extractor
    ./bin/SCM_Extractor.exe <RaioCursor> <nivelQuantização> <DiretórioInput> <DiretórioOutput>
    ```

### Solução de Problemas

Se encontrar algum problema durante a execução, considere o seguinte:

- Recompilar usando o Makefile para máxima compatibilidade.

    Para Unix:
    ```bash
    make clean-unix
    make
    ```
    Para Windows:
    ```bash
    make clean-windows
    make
    ```

## Organização de Arquivos

### PatternExtractor
- **`/bin`**: Arquivos de código-fonte

- **`/data`**: Arquivos de conjunto de dados e arquivos de saída
  - `/features_output`: Saída de características
  - `/oncotex_pgm`: Conjunto de dados de imagens PGM

- **`/demos`**: Arquivos não relacionados ao código principal
  - `/snippets`: Códigos originais do professor
  - `/tests`: Testes antigos

- **`/docs`**: Arquivos de teste e conjuntos
  - `FinalProject.pdf`: Instruções do projeto
  - `RelatorioFinal.docx`: Relatório final docx
  - `RelatorioFinal.pdf`: Relatório final pdf 

- **`/include`**: Arquivos de cabeçalho

- **`/obj`**: Arquivos de objeto compilados

- **`/src`**: Código fonte

- **`README.en.md`**: README em inglês

- **`README.md`**: README em português

## Contribuidores

O projeto **PatternExtractor** tem como principais contribuidores:

- [@maripasa](https://github.com/maripasa)
- [@Kaiserg3](https://github.com/Kaiserg3)
- [@Lucasholanda5](https://github.com/Lucasholanda5)
- [@rafri41200](https://github.com/rafri41200)

![266834128-c75a6f3b-ce18-48c7-908e-8efe5aa9c254](https://github.com/maripasa/PatternExtractor/assets/123270648/be891264-39b2-4ff1-9551-bb95f52ce82c)
