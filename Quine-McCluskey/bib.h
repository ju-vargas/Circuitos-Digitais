#ifndef BIB_H
#define BIB_H

#include <iostream> 
#include <string>
#include <string.h>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

//CONSTANTES

//TYPEDEFS (OBJETOS) [o ideal eh depois passar isso para uma classe com suas funções] [primeiro to fazendo funcionar]
typedef std::tuple<int, string, bool, string, int> mintermo_;  
//numero
//numero em binario
//se foi decscrito com outro mintermo, 
//numeros que descreve caso seja par ---- formato "2,5,8,9"
//grupo por numeros de 1 (0,1,2,3,4)

typedef std::tuple<string, string, int, bool, bool> mintermo_tabela;  
//numeros que descreve
//binario
//tamanho
//essencial ou nao
//se sera mostrado na equacao






//CLASSES 


//FUNÇÕES 
int tamArray(string texto);
void stringToArray(string string, mintermo_ * arrayNumeros);
void desenhaMapa (mintermo_* mintermos, int tamMintermos, mintermo_* dontCares, int tamDontCares, int qntdVariaveis);
int binaryToDecimal(int n); 
string decimalToBinary(int num); 
void preencheBinario (mintermo_* array, int tam, int qntdVariaveis);
void swap(mintermo_ *n1, mintermo_ *n2); 
void ordenaColuna  (mintermo_* coluna, int nroDeDados, int variaveis); 
int encontraPares (mintermo_* coluna, int dadosColuna, mintermo_ procurado, int nroVariaveis);
int constroiArrayPares (mintermo_* coluna, int dadosColuna, mintermo_ procurado, int nroVariaveis, mintermo_* novaColuna, int dadosNovaColuna, int index); 
bool comparaPares (mintermo_ elementoUm, mintermo_ elementoDois);
int removeDuplicates(int arr[], int n); 
string stringToOrdenedString(string numerosContidos);
void desenhaTabela (string mintermos,  mintermo_* arrayMintermos, int nroMintermos, mintermo_* arrayFinal, int tamArrayFinal); 
bool taNaString (int nro, string stringBusca);
string binarioToMintermo(string binario); 


#endif