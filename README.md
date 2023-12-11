# PatternExtractor - Programming Lab 2023-2

_Read this in other languages: [English](README.en.md), [Português](README.md)._

Welcome to the **PatternExtractor** project, organized by **Professor Daniel Ferreira at IFCE**.

## Overview
The **PatternExtractor** project is a part of the Programming Lab for the second semester of 2023. The goal of this project is to develop an AI-based solution for extracting and analyzing patterns from datasets.

## Purpose
The primary objective of **PatternExtractor** is to create a tool that can automatically identify and extract meaningful patterns from medical datasets.

## Technologies
> **Note:** Although great accuracy is encouraged, we won't be avaliated in the "AI part of the code".
We will be using mainly C and Weka.

Weka is an open-source software suite designed for data mining and machine learning tasks developed at the University of Waikato, New Zealand.

More about it in here: [WEKA](https://www.cs.waikato.ac.nz/ml/weka/index.html)

## Code Execution

### Prerequisites

Ensure you have the following prerequisites installed on your system:

- Linux is recommended.

### Running the Code

Follow these steps to execute the code:

- **Step 1:** Clone the repository to your local machine.

    ```bash
    git clone https://github.com/maripasa/PatternExtractor.git
    ```

- **Step 2:** Navigate to the project directory.

    ```bash
    cd PatternExtractor
    ```
   
- **Step 3:** Run the program.

    ```bash
    # Example command to run SCM_Extractor
    ./bin/SCM_Extractor.exe <CursorFilterSize> <QuantizationLevels> <InputDirectory> <OutputDirectory>
    ```

### Troubleshooting

If you encounter any issues during execution, consider the following:

- Recompile using Makefile for maximum compatibility.

    For Unix:
    ```bash
    make clean-unix
    make
    ```
    For Windows:
    ```bash
    make clean-windows
    make
    ```

## File Organization

### PatternExtractor
- **`/bin`**: Source code files

- **`/data`**: Dataset files and output files
  - `/features_output`: Features output
  - `/oncotex_pgm`: PGM images dataset

- **`/demos`**: Not main code related files files
  - `/snippets`: Teacher's original codes
  - `/tests`: Old small tests

- **`/docs`**: Test files and suites
  - `FinalProject.pdf`: Project instructions
  - `RelatorioFinal.docx`: Final report docx
  - `RelatorioFinal.pdf`: Final report pdf 

- **`/include`**: Header files

- **`/obj`**: Compiled object files

- **`/src`**: Source code

- **`README.en.md`**: English README

- **`README.md`**: Portuguese README

## Contributors

The **PatternExtractor** project has as main contributors:

- [@maripasa](https://github.com/maripasa)
- [@Kaiserg3](https://github.com/Kaiserg3)
- [@Lucasholanda5](https://github.com/Lucasholanda5)
- [@rafri41200](https://github.com/rafri41200)

![266834128-c75a6f3b-ce18-48c7-908e-8efe5aa9c254](https://github.com/maripasa/PatternExtractor/assets/123270648/be891264-39b2-4ff1-9551-bb95f52ce82c)
