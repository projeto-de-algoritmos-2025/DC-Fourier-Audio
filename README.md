# DC-Fourier-Audio

### Vídeo
Apresentação de demonstração do trabalho presente [aqui](https://youtu.be/6mJUpj8y1og)

## Introdução

O Fourier Audio é um programa de análise de áudio que gera um gráfico de frequências de um arquivo de áudio. Utilizando o algoritmo de divisão e conquista Fast Fourier Transform (FFT), ele identifica as frequências mais predominantes na série temporal do áudio e exibe em um gráfico. Quanto maior a predominância de uma frequência, maior o ponto que a representa no gráfico Frequência x Magnitude.

## Implementação

Para realizar, essa análise, o algoritmo FFT divide o vetor que representa a sequência do áudio ao longo do tempo em duas metades, uma metade corresponde as casas pares do vetor, e outro, equivale as casas ímpares. Esse processo é feito recursivamente para cada subvetor gerado. O caso base ocorre quando o subvetor possui apenas um elemento. Abaixo está a exemplificação da divisão.

    FFT(x) = conquista(FFT(es), FFT(os))

em que "es" é o subvetor com elementos cuja casa era par, e "os", o subvetor das casas ímpares. 


Na parte da conquista, o vetor de entrada x é reconstruído de forma que:

    x[i] = es[i] + S*os[i]
    x[i + N/2] = es[i] - S*os[i]

## Uso

O software foi desenvolvido em uma distribuição Linux, e o guia de uso terá como base sistemas operacionais Linux.

Inicialmente, clone o repositório, ou baixe o .zip e descompacte-o.

Será necessário que sua máquina tenha o compilador g++, e o python 3.11 instalados. Além disso, é necessário a biblioteca matplotlib do python, e o make para usar o Makefile.

    sudo apt install make
    sudo apt install python3-dev
    pip install matplotlib


Na raiz do repositório, use o comando:

     make build 

para compilar o projeto. A compilação retornará alguns warnings, mas gerará o executável.

Para rodar a aplicação, usa-se o comando:

    make run FILE=path/to/file
 
em que "path/to/file" é o caminho para um arquivo de áudio.

Os formatos de áudio aceitos são .wav e .mp3

Na pasta 'samples' há dois arquivos de áudio para testar a aplicação.
