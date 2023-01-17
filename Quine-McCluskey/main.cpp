#include "bib.h"

using namespace std;

int main (){ 
    string mintermos; 
    string dontCares;
    int qntdVariaveis = 0; 
    int aux; 
    int nroMintermos, nroDontCares; 

    nroMintermos = nroDontCares = 0;

    bool colunaVazia = false; 
    bool continua = true; 

    int contagemColunas; 
    int nroDadosColuna;         //sempre representa o da coluna 0
    int nroDePares[4] = {0,0,0,0};         //vai representar o das diversas colunas
    int index = 0; 


/*------------------------------------------------------------------------------------------
    ETAPA 1 - RECEBER MAPA
    - receber mintermos
    - receber dontcares
    - receber tamanho 
    
    independente da quantidade mintermos e dontcares, salvar em array com tamanho adequado

    - conseguir colocar no mapa 
    - posteriormente, usar classe para mintermos ou linhas da coluna do metodo de Quine-McClusey 
*/
    
    //receber parametros do usuario 
    cout << "Insira os mintermos (separados por espaco): ";
    getline(cin, mintermos); 
    cout << "Insira os dont cares: "; 
    getline(cin, dontCares);
    cout << "Insira a quantidade de variaveis: ";
    cin >> qntdVariaveis;

    cout << "\nOs mintermos sao " << mintermos << ", os dontcares sao " << dontCares << " e o nro de variaveis eh " << qntdVariaveis <<".";

    //*** se variável 0 ou 1, ir pro fim 

    //passar valores para array
    if(mintermos == "") nroMintermos = 0; 
    else
        nroMintermos = tamArray(mintermos); 
    mintermo_ arrayMintermos[nroMintermos]; 
    stringToArray(mintermos, arrayMintermos); 
    
    preencheBinario(arrayMintermos, nroMintermos, qntdVariaveis); 

    if(dontCares == "") nroDontCares = 0;
    else
        nroDontCares = tamArray(dontCares); 
    mintermo_ arrayDontCares[nroDontCares]; 
    stringToArray(dontCares, arrayDontCares); 

    preencheBinario(arrayDontCares, nroDontCares, qntdVariaveis); 

    cout << "\n\nDesenho do mapa: ";
    desenhaMapa(arrayMintermos, nroMintermos, arrayDontCares, nroDontCares, qntdVariaveis); 


/*------------------------------------------------------------------------------------------
    ETAPA 2 - COLUNA 0 
    - passar dados do mapa para as tuplas 
        - binario, se ta preenchido, se nao 

    - listar todos os mintermos e dontcares em um ARRAY DE MINTERMOS chamado coluna0
    - nesse array, tenho número e número em binário, alem do dado se esta representado em outra coluna (oq vou decobrir por função), PRESENTE/AUSENTE na coluna

    - sei qual é a coluna com os primeiros dígitos do binário (de acordo com ab/a)


    - faço array da coluna, iterando como for necessário (verificar se a ordem de colunas importa e como contornar isso)
    - SE A COLUNA FICAR VAZIA, entao acabou o algoritmo e pulo pra prox parte (tabela mintermos)
*/
    nroDadosColuna = nroMintermos + nroDontCares; 
    //if entrada = 0....

    mintermo_ coluna0[nroDadosColuna]; 

    //preenchendo array da coluna 0
    for (int i = 0; i < nroMintermos; i++) {
        coluna0[i+nroDontCares] = arrayMintermos[i]; 
    }

    for (int i = 0; i < nroDontCares; i++) {
        coluna0[i] = arrayDontCares[i]; 
    }

    //ordenando array de coluna pra ficar compativel com o metodo de Quine
    //a ordenação leva em conta o tamanho, depois disso, eh so continuar colocando em ordem que vai estar "ordenado" 
    ordenaColuna(coluna0, nroDadosColuna,qntdVariaveis); 

    //printando coluna
    cout << "\n\ncoluna 0: \n";
    for (int i = 0; i<nroDadosColuna; i++){
        cout << get<3>(coluna0[i]) << ": " << get<1>(coluna0[i]) << "\n";
    }

/*------------------------------------------------------------------------------------------
    ETAPA 3 - COLUNA 1 

    - faço array da coluna, iterando como for necessário (verificar se a ordem de colunas importa e como contornar isso)
        - aqui eu preciso comparar um a um se foi encontrado outro igual, binario por binario
        (for aninhado) + lógica com strings 
        - se encontro coloco na próxima coluna (novo array.... se já foi ocupado... verificar essas questoes)
    - SE A COLUNA FICAR VAZIA, entao acabou o algoritmo e pulo pra prox parte (tabela mintermos)
*/

    
        //descobrindo numero de pares
        nroDePares[0] = encontraPares(coluna0, nroDadosColuna,coluna0[1],qntdVariaveis);
        
        //nroDePares[0] = nroDePares[0]/2; 
        //cout << "Nro de pares: " << nroDePares[0] << "\n";  

        //criando novo array para coluna 1
        //construir array levando em consideração não repetir já representados, e ordem de colunas
        //lembrar de preencher atributos 
        mintermo_ coluna1[nroDePares[0]]; 

            for(int i = 0; i < nroDePares[0]; i++) {
                get<1>(coluna1[i]) = ""; 
            }
            
                                       
            index = constroiArrayPares(coluna0, nroDadosColuna, coluna0[1], qntdVariaveis, coluna1, nroDePares[0], index);
            
            ordenaColuna(coluna1, nroDePares[0],qntdVariaveis-1);      //posso ir mudando o numero de pares pq no final vou conseguir o numero de todos iterando

            cout << "\n\ncoluna 1: \n";
            for (int i = 0; i<nroDePares[0]; i++){
                cout << get<3>(coluna1[i]) << ": " << get<1>(coluna1[i]) << "\n";
            } 
    


/*------------------------------------------------------------------------------------------
    ETAPA 4 - COLUNA 2
*/
    
        //aqui, eu vou preencher o get<0> da coluna, pois isso é usado para diferenciá-los na funcao abaixo. os numeros de get<0> servirao só pra isso, nao vale
        for (int i = 0; i<nroDePares[0];i++) {
            get<0>(coluna1[i]) = i; 
        }

        //descobrindo numero de pares iterando a coluna 1 que fiz
        
        nroDePares[1] = encontraPares(coluna1, nroDePares[0],coluna1[1],qntdVariaveis);
        
        
        //nroDePares[1] = nroDePares[1]/2; //TESTANDO 
        //cout << "Nro de pares: " << nroDePares[1] << "\n";  
    
            mintermo_ coluna2[nroDePares[1]]; 

            for(int i = 0; i < nroDePares[1]; i++) {
                get<1>(coluna2[i]) = ""; 
            }
            
            index = 0; 
            index = constroiArrayPares(coluna1, nroDePares[0], coluna1[1], qntdVariaveis, coluna2, nroDePares[1], index);
            ordenaColuna(coluna2, nroDePares[1],qntdVariaveis-1);      //posso ir mudando o numero de pares pq no final vou conseguir o numero de todos iterando

            //nroDePares[1] = index; 
            cout << "\n\ncoluna 2 \n";
            for (int i = 0; i<nroDePares[1]; i++){
                cout << get<3>(coluna2[i]) << ": " << get<1>(coluna2[i]) << "\n";
            } 
            
    

/*------------------------------------------------------------------------------------------
    ETAPA 5 - COLUNA 3
*/
        //aqui, eu vou preencher o get<0> da coluna, pois isso é usado para diferenciá-los na funcao abaixo. os numeros de get<0> servirao só pra isso, nao vale
        for (int i = 0; i<nroDePares[1];i++) {
            get<0>(coluna2[i]) = i; 
        }
        
        //descobrindo numero de pares iterando a coluna 1 que fiz
        nroDePares[2] = encontraPares(coluna2, nroDePares[1],coluna2[1],qntdVariaveis);
        
        mintermo_ coluna3[nroDePares[2]]; 
    
            for(int i = 0; i < nroDePares[2]; i++) {
                get<1>(coluna3[i]) = ""; 
            } 

            index = 0;                            
            index = constroiArrayPares(coluna2, nroDePares[1], coluna2[1], qntdVariaveis, coluna3, nroDePares[2], index);
        
            

            ordenaColuna(coluna3, nroDePares[2],qntdVariaveis-1);      //posso ir mudando o numero de pares pq no final vou conseguir o numero de todos iterando

            //nroDePares[2] = index; 
            
            cout << "\n\ncoluna 3 \n";
            for (int i = 0; i<nroDePares[2]; i++){
                cout << get<3>(coluna3[i]) << ": " << get<1>(coluna3[i]) << "\n";
            } 
    
/*------------------------------------------------------------------------------------------
    ETAPA 6 - COLUNA 4

*/
        //aqui, eu vou preencher o get<0> da coluna, pois isso é usado para diferenciá-los na funcao abaixo. os numeros de get<0> servirao só pra isso, nao vale
        for (int i = 0; i<nroDePares[2];i++) {
            get<0>(coluna3[i]) = i; 
        }

        //descobrindo numero de pares iterando a coluna 1 que fiz
            nroDePares[3] = encontraPares(coluna3, nroDePares[2],coluna3[1],qntdVariaveis);
        
        
        //nroDePares[3] = nroDePares[3]/8; //TESTANDO 
        //cout << "Nro de pares: " << nroDePares[3] << "\n";  
        
        mintermo_ coluna4[nroDePares[3]]; 

            for(int i = 0; i < nroDePares[3]; i++) {
                get<1>(coluna4[i]) = ""; 
            }
            
            index = 0; 
                                  
            index = constroiArrayPares(coluna3, nroDePares[2], coluna3[1], qntdVariaveis, coluna4, nroDePares[3], index);
            
            ordenaColuna(coluna4, nroDePares[3],qntdVariaveis-1);      //posso ir mudando o numero de pares pq no final vou conseguir o numero de todos iterando

            
            cout << "\n\ncoluna 4 \n";
            for (int i = 0; i<nroDePares[3]; i++){
                cout << get<3>(coluna4[i]) << ": " << get<1>(coluna4[i]) << "\n";
            } 
/*------------------------------------------------------------------------------------------
  
/*------------------------------------------------------------------------------------------
    ETAPA 6 - Tabela de cobertura
*/

    //criando coluna final
    int tamArrayFinal; 
    tamArrayFinal = nroDePares[0] + nroDePares[1] + nroDePares[2] + nroDePares[3]; 

    mintermo_ arrayFinal[tamArrayFinal];


    int contadorFinal = 0; 
    for (int i = 0; i < nroDadosColuna; i++) {
        if (!get<2>(coluna0[i])){
            arrayFinal[contadorFinal] = coluna0[i]; 
            contadorFinal++; 
        }
    }

    for (int i = 0; i < nroDePares[0]; i++) {
        if (!get<2>(coluna1[i])){
            arrayFinal[contadorFinal] = coluna1[i]; 
            contadorFinal++; 
        }
    }
    for (int i = 0; i < nroDePares[1]; i++) {
        if (!get<2>(coluna2[i])){
            arrayFinal[contadorFinal] = coluna2[i]; 
            contadorFinal++; 
        }
    }
    for (int i = 0; i < nroDePares[2]; i++) {
        if (!get<2>(coluna3[i])){
            arrayFinal[contadorFinal] = coluna3[i]; 
            contadorFinal++; 
        }
    }
    for (int i = 0; i < nroDePares[3]; i++) {
        if (!get<2>(coluna4[i]) ){
            arrayFinal[contadorFinal] = coluna4[i]; 
            contadorFinal++; 
        }
    }


    cout << "\n\ncoluna final \n";
    for (int i = 0; i<contadorFinal; i++){
        cout << get<3>(arrayFinal[i]) << " (" << get<2>(arrayFinal[i]) << ") :"  << get<1>(arrayFinal[i]) << "\n";
    } 

    desenhaTabela (mintermos, arrayMintermos, nroMintermos, arrayFinal, contadorFinal);

    
    

    //funcao que recebe string e devolve ela ordenada e sem numeros repetidos em um array
    //depois teria pegar o array e colocar em vírgulas de novo (facil)

/*------------------------------------------------------------------------------------------
    
    //faço ifs para que sejam feitas a quantidade de colunas de acordo com o número de variáveis
    (nao precisa eu acho)

    //faço while pra que seja encontrada não seja retornado coluna vazia

    //depois, itero todos, vendo quais nao estao marcados como já representados, e faço ARRAY FINAL
*/
    
    return 0; 
}


int tamArray(string texto){
    int tam = 0; 
    int tamArray; 

    tam = texto.length(); 

    //para obter qual deve ser o tamanho do array de números  
 
    for (int i = 0; i < tam; i++) {               
        if(texto[i] == ' ' && i != 0 && texto[i-1]!= ' ') tamArray++; 
        if (i+1 == tam && texto[i] != ' ')   tamArray++; 
    }
    return tamArray; 
}
    
void stringToArray(string texto, mintermo_ * arrayNumeros) {
    string stringAux =""; 
    int tam = 0; 
    int tamArray; 
    int aux; 
    int j = 0; 
    int i = 0; 
    bool teste = true; 

    tam = texto.length(); 

    texto = texto + ' '; 

    while (teste) {
        if (texto[i] == ' ') i++;
        else teste = false; 
    } 
    while (i < tam) {
        if (texto[i] == ' ') {
            i++; 
        }
        else {
            stringAux = stringAux + texto[i];
            i++;           
            if (texto[i] == ' ' ) {
                aux = stoi(stringAux); 
                get<0>(arrayNumeros[j]) = aux; 
                j++;
                stringAux = ""; 
            }   
        }
    }
}

void desenhaMapa (mintermo_* mintermos, int tamMintermos, mintermo_* dontCares, int tamDontCares, int qntdVariaveis) {

    int linhas = 0;
    int colunas = 0;
    int termos = 0; 


    switch (qntdVariaveis) {
        case 2:
            linhas = 2;
            colunas = 2; 
            termos = 4; 
            break;

        case 3:
            linhas = 2;
            colunas = 4; 
            termos = 8; 
            break;

        case 4:
            linhas = 4;
            colunas = 4; 
            termos = 16; 
            break;

        default:
            break;
    }

    //preencher o mapa na ordem normal (como se fosse tabela verdade)
    string mapa[termos]; 

    for (int i = 0; i < termos; i++) {
        mapa[i] = "   ";
        // aqui, preciso interar tanto os mintermos como dont cares
        for(int j = 0; j<tamMintermos; j++) {
            if (get<0>(mintermos[j]) == i) {
                mapa[i] = " 1 ";    
            }
        }
        for (int j = 0; j<tamDontCares; j++) {
            if (get<0>(dontCares[j]) == i) {
                mapa[i] = " X "; 
            }
        }    
    }

   cout << "\n"; 
    if (qntdVariaveis == 4) {
        cout << "|" << mapa[0] << "|" << mapa[4] << "|" << mapa[12] << "|" << mapa[8]  << "|\n";
        cout << "|" << mapa[1] << "|" << mapa[5] << "|" << mapa[13] << "|" << mapa[9]  << "|\n";
        cout << "|" << mapa[3] << "|" << mapa[7] << "|" << mapa[15] << "|" << mapa[11] << "|\n";
        cout << "|" << mapa[2] << "|" << mapa[6] << "|" << mapa[14] << "|" << mapa[10] << "|\n";
    }

    else if (qntdVariaveis == 3) {
        cout << "|" << mapa[0] << "|" << mapa[2] << "|" << mapa[6] << "|" << mapa[4]  << "|\n";
        cout << "|" << mapa[1] << "|" << mapa[3] << "|" << mapa[7] << "|" << mapa[5]  << "|\n";  
    }
  
    else if (qntdVariaveis == 2) {
        cout << "|" << mapa[0] << "|" << mapa[2] << "|\n";
        cout << "|" << mapa[1] << "|" << mapa[3] << "|\n";  
    }

    cout << "\n"; 
}

int binaryToDecimal(int n){
    int num = n;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}

string decimalToBinary(int num) {
    int aux = num; 
    
    string r;
    while(num!=0) {r=(num%2==0 ?"0":"1")+r; num/=2;}
    return r;
}

void preencheBinario (mintermo_* array, int tam, int qntdVariaveis) {
    string auxString;
    int precision = 0; 
    string s; 
    size_t tamanhoString = qntdVariaveis; 

    for (int i = 0; i<tam; i++) {
        auxString = decimalToBinary(get<0>(array[i])); 
        precision = tamanhoString - min(tamanhoString, auxString.size());
        s = string(precision, '0').append(auxString);
        get<1>(array[i]) = s; 

        get<3>(array[i]) = to_string(get<0>(array[i]));     //colocando o equivalente do numero na propriedade de string de pares
    }
}

void swap(mintermo_ *n1, mintermo_ *n2){
	mintermo_ troca = *n1;
	*n1 = *n2;
	*n2 = troca;
}

void ordenaColuna  (mintermo_* coluna, int nroDeDados, int variaveis) { 
    
    int numero;         //numero de ums na string
    string auxString; 
    int contagem = 0;  
    int teste;

    //separo as strings em grupos de acordo com números de 1 
    for (int i = 0; i < nroDeDados; i++) {      //iterando sobre todos os dados da coluna 
        numero = 0; 

        auxString = get<1>(coluna[i]);
        for (int j = 0; j < variaveis; j++) {   //iterando sobre cada caractere da string dos dados 
            if (auxString[j] == '1'){
                numero++; 
            }
        }
        get<4>(coluna[i]) = numero;        
    }

    //agora que tem o atributo de grupo, ordeno ele 
    for (int i = 0; i < 5; i++) {                //pra zero 1, pra um 1, dois 1, tres 1, quatro 1
        for (int j = 0; j < nroDeDados; j++) {   //iterando em todos os lados da coluna 
            if (get<4>(coluna[j]) == i) {
                swap(coluna[j], coluna[contagem]); 
                contagem++; 
            }
        }
    } 
}

int encontraPares (mintermo_* coluna, int dadosColuna, mintermo_ procurdo, int nroVariaveis) {
    int traco = -1;
    int nroDePares = 0;
    string binarioBase;       // de qual string q procuro igual 

    string copiaTraco;
    string auxString; 
    string copiaStrColuna;

    string auxGeral = {}; 
    string geral = {}; 
    string copiaComTraco = {};
    string copiaAuxString  ={}; 
    mintermo_ procurado; 

    int ajuda = 0; 
    
    string ajudaString; 
    bool tem = false;

    //vou iterar pra todos os da coluna
    for (int i = 0; i<dadosColuna;i++) {
       

        //pego o primeiro elemento da coluna
        procurado = coluna[i]; 
        //pego o seu valor em binario
        binarioBase = get<1>(procurado);

        //cout << "\n\nprocurando para: " << get<3>(procurado) << "\n" ; 
 
        //agora, vou procurar os semelhantes para _000, 0_00, 00_0, 000_
        traco = -1; 
        for (int j = 0; j < nroVariaveis; j++) {
            traco++; 
            
            //cria string equivalente (sem o algorismo do traco) em copiaTraco 
            copiaTraco = {};
            copiaComTraco = {}; 
            for (int j = 0; j<nroVariaveis; j++) {          
                if ( j!= traco) 
                    copiaTraco = copiaTraco + binarioBase[j]; 
            }

            if (traco < 4)
                copiaComTraco = copiaTraco.insert(traco, 1, '-');

            //cout << "\n comparando com: "; 
            //procura string equivalente na coluna
            for (int k = 0; k<dadosColuna; k++) {              
                //para isso, faz a string equivalente da coluna de acordo com iteracao
                copiaStrColuna = get<1>(coluna[k]); 
                auxString = {}; 
                copiaAuxString = {}; 
                for (int l = 0; l<nroVariaveis; l++) {      
                    if ( l!= traco) 
                        auxString = auxString + copiaStrColuna[l]; 
                } 
                if (traco < 4)
                    copiaAuxString = auxString.insert(traco, 1, '-');
                
                //cout <<  get<3>(coluna[k]) << ", "; 

                if(copiaAuxString == copiaComTraco && k != i) {
                    //cout << copiaAuxString << "=" << copiaComTraco << "\n"; 
                    auxGeral = {}; 
                    auxGeral += get<3>(procurado) + ',';
                    auxGeral += get<3>(coluna[k]);

                    auxGeral = stringToOrdenedString(auxGeral); 

                    auxGeral = " -" + auxGeral; 
                    auxGeral += "- "; 
                    
                    //cout << auxGeral << ":" << geral << "\n"; 
                    ajuda = auxGeral.length(); 
                    tem = false; 
                    for (int x = 0; x < geral.length(); x++) {
                        ajudaString = {}; 
                        for (int y = 0; y < ajuda; y++) {
                            ajudaString += geral[x+y];
                        }
                        if (ajudaString == auxGeral) {
                            tem = true; 
                        }
                    }
                    
                    if (!tem)  {
                        geral += auxGeral; 
                        get<2>(procurado) = true;
                        get<2>(coluna[k]) = true;
                        //cout << "auxGeral:"<< auxGeral << "\n";
                        
                        nroDePares++;
                        //cout << "numero de pares = " << nroDePares << "\n";
                    }    
                }
            }
        }
    cout << "nroDepares: " << nroDePares; 
    return nroDePares;
    }
    return 0; 
}


int constroiArrayPares (mintermo_* coluna, int dadosColuna, mintermo_ procurao, int nroVariaveis, mintermo_* novaColuna, int dadosNovaColuna, int idex) {
    int traco = -1;
    int nroDePares = 0;
    int index = 0; 

    string binarioBase;       // de qual string q procuro igual 

    string copiaTraco;
    string auxString; 
    string copiaStrColuna;

    string auxGeral = {}; 
    string geral = {}; 
    string copiaComTraco = {};
    string copiaAuxString  ={}; 

    mintermo_ procurado; 
    mintermo_ mintermoAux;

    bool jaEsta = false; 

    int ajuda = auxGeral.length(); 
    string ajudaString; 
    bool tem = false;

    //vou iterar pra todos os da coluna
    for (int i = 0; i<dadosColuna;i++) {
       

        //pego o primeiro elemento da coluna
        procurado = coluna[i]; 
        //pego o seu valor em binario
        binarioBase = get<1>(procurado);

        //cout << "\n\nprocurando para: " << get<3>(procurado) << "\n" ; 
 
        //agora, vou procurar os semelhantes para _000, 0_00, 00_0, 000_
        traco = -1; 
        for (int j = 0; j < nroVariaveis; j++) {
            traco++; 
            
            //cria string equivalente (sem o algorismo do traco) em copiaTraco 
            copiaTraco = {};
            copiaComTraco = {}; 
            for (int j = 0; j<nroVariaveis; j++) {          
                if ( j!= traco) 
                    copiaTraco = copiaTraco + binarioBase[j]; 
            }

            if (traco < 4)
                copiaComTraco = copiaTraco.insert(traco, 1, '-');

            //cout << "\n comparando com: "; 
            //procura string equivalente na coluna
            for (int k = 0; k<dadosColuna; k++) {              
                //para isso, faz a string equivalente da coluna de acordo com iteracao
                copiaStrColuna = get<1>(coluna[k]); 
                auxString = {}; 
                copiaAuxString = {}; 
                for (int l = 0; l<nroVariaveis; l++) {      
                    if ( l!= traco) 
                        auxString = auxString + copiaStrColuna[l]; 
                } 
                if (traco < 4)
                    copiaAuxString = auxString.insert(traco, 1, '-');
                
                //cout <<  get<3>(coluna[k]) << ", "; 

                if(copiaAuxString == copiaComTraco && k != i) {       //melhor eh ver pelo numero em binario
                
                    //criar novo mintermos 
                    get<2>(procurado) = true;
                    get<2>(coluna[k]) = true;

                    get<3>(mintermoAux) = {}; 
                    string AAAA; 
                    AAAA = get<3>(procurado);
                    AAAA += ",";
                    AAAA += get<3>(coluna[k]);        //vai ser o par. tipo 1,2 (em primeiro vai sempre o procurado)
                    AAAA = stringToOrdenedString(AAAA); 
                    get<3>(mintermoAux) = AAAA;
                    
                    get<1>(mintermoAux) = copiaComTraco; 
                    
                    //verificar se já está no array (pelo e se não estiver colocar  //
                    auxGeral = {}; 
                    auxGeral += get<3>(procurado) + ',';
                    auxGeral += get<3>(coluna[k]);

                    auxGeral = stringToOrdenedString(auxGeral); 

                    auxGeral = " -" + auxGeral; 
                    auxGeral += "- "; 
                    
                    //cout << auxGeral << ":" << geral << "\n"; 
                    ajuda = auxGeral.length(); 
                    tem = false; 
                    for (int x = 0; x < geral.length(); x++) {
                        ajudaString = {}; 
                        for (int y = 0; y < ajuda; y++) {
                            ajudaString += geral[x+y];
                        }
                        if (ajudaString == auxGeral) {
                            jaEsta = true; 
                        }
                    }


                    if (!jaEsta) {
                       
                        geral += auxGeral; 
                        novaColuna[index] = mintermoAux; 
                        index++; 

                        //cout << "mintermo aux = " << get<1>(novaColuna[index]) << "\n"; 
                    }
                    jaEsta = false;     
                }
            }
        }
    } 
    return index;
    
}

bool comparaPares (mintermo_ elementoUm, mintermo_ elementoDois) {

    string stringUm; 
    string stringDois; 
    string auxUm; 
    string auxDois; 
    bool ehIgual = true; 
    bool tem = false; 

    size_t tam = 0; 
    size_t tam2 = 0; 
 
    stringUm = get<3>(elementoUm); 
    stringDois = get<3>(elementoDois); 

    tam = stringUm.length();
    tam2 = stringDois.length();  
    
    //if(tam != tam2) return false; 

    int j = 0; 

    while (j<tam){
        auxUm = {};   
        while (stringUm[j] != ',' && j<tam) {
            auxUm = auxUm + stringUm[j]; 
            j++; 
        }
        j++; //pra pular a virgula

        //auxUm representa número, agora vou procurar ele em stringDois     
        tem = false; 
        if (auxUm.length() == 2) {
            for(int k = 0; k < (tam2-1); k++) { // 0,1,2,13 tam=8  k<7
                    if ((stringDois[k] == auxUm[0]) && stringDois[k+1] == auxUm[1]) {
                        tem = true;                         
                    }
            }
        }
        else if (auxUm.length() == 1) {
                for(int k = 0; k < tam2; k++) { // 0,1,2,13 tam=8  k<7
                    if (stringDois[k] == auxUm[0] && stringDois[k-1] != '1') {
                        tem = true; 
                    }
                }
        }
        if (!tem) 
            ehIgual = false; 
    }

    //cout << "\n" <<stringUm << " = " << stringDois << " (" << ehIgual << ")"; 
    return ehIgual; 
}
int removeDuplicates(int arr[], int n) {
    // Return, if array is empty or contains a single
    // element
    if (n == 0 || n == 1)
        return n;
  
    int temp[n];
  
    // Start traversing elements
    int j = 0;
    // If current element is not equal to next element
    // then store that current element
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];
  
    // Store the last element as whether it is unique or
    // repeated, it hasn't stored previously
    temp[j++] = arr[n - 1];
  
    // Modify original array
    for (int i = 0; i < j; i++)
        arr[i] = temp[i];
  
    return j;
}

//recebe a string em numeros contidos
string stringToOrdenedString(string numerosContidos) {
    
    int tamArrayFim = 0; 
    int auxStringCount = 0; 
    string auxStringFim = {}; 

    auxStringCount = numerosContidos.length(); 
    for (int i = 0; i < auxStringCount; i++) {
        if (numerosContidos[i] != ',' && numerosContidos[i+1] == ',') {
            tamArrayFim++;
        }
    }
    if (numerosContidos[auxStringCount-1] != ',')
        tamArrayFim++; 

    int arrayFim[tamArrayFim];

    int i = 0; 
    int j = 0; 
    while (i<tamArrayFim) {
        if (numerosContidos[j] != ',' && numerosContidos[j+1] == ','){
            auxStringFim = numerosContidos[j]; 
            arrayFim[i] = stoi(auxStringFim);
            i++;
        }
        if (numerosContidos[j] != ',' && numerosContidos[j+1] != ','){
            auxStringFim = numerosContidos[j];
            auxStringFim += numerosContidos[j+1]; 
            arrayFim[i] = stoi(auxStringFim);
            i++;
            j++;
        }
        j++;
    }
    sort(arrayFim, arrayFim + tamArrayFim);
    tamArrayFim = removeDuplicates(arrayFim, tamArrayFim); 
        
    int newArray[tamArrayFim];
    copy(arrayFim, arrayFim + tamArrayFim, newArray); 

    string retorno = {}; 

    for (int i = 0; i<tamArrayFim; i++) {        
        retorno += to_string(newArray[i]);

        if (i != (tamArrayFim-1))
            retorno += ',';
    } 
    return retorno; 
}

void desenhaTabela (string mintermos, mintermo_* arrayMintermos, int nroMintermos, mintermo_* arrayFinal, int tamArrayFinal) {
    string aux;
    int auxEssencial = 0; 

    mintermo_tabela minTabela[tamArrayFinal];
    //array de mintermos 
    for (int i = 0; i < tamArrayFinal; i++) {
        aux = get<3>(arrayFinal[i]); 
        get<0>(minTabela[i]) = get<3>(arrayFinal[i]); 
        get<1>(minTabela[i]) = get<1>(arrayFinal[i]);
        get<2>(minTabela[i]) = ((aux.length())/2) + 1;
    }

    //imprimindo tabela
    cout << "\nTABELA DE COBERTURA: ";
    cout << "\n     ";
    cout << mintermos; 
    cout << "\n     ";
    
    for(int i = 0; i < tamArrayFinal; i++) {
        for(int j = 0; j<nroMintermos; j++) {
            aux = to_string(get<0>(arrayMintermos[j])); 

            if (taNaString(get<0>(arrayMintermos[j]), get<0>(minTabela[i]))) {
                if(aux.length() == 2) cout << "X  ";
                else if(aux.length() == 1)cout << "X ";
            }
            else {
                if(aux.length() == 2) cout << "   ";
                else if(aux.length() == 1)cout << "  ";
            }
                
        }
        cout << get<0>(minTabela[i]); 
        cout << "\n     ";
    }

    //setando descrito por mintermo como falso, pra poder usar abaixo
    for (int i = 0; i < nroMintermos; i++){
        get<2>(arrayMintermos[i]) = false; 
    }

    
    //marcando essenciais
    for (int i = 0; i < nroMintermos; i++) {        //iterando pra todos os mintermos
        auxEssencial = 0;
        for (int j = 0; j < tamArrayFinal; j++) {   //procurando no array quantos descrevem
            if (taNaString(get<0>(arrayMintermos[i]), get<0>(minTabela[j]))){
                //numero de mintermos                 par de Mintermos
                auxEssencial++;
            }
        }
        if (auxEssencial == 1) {
            for (int j = 0; j < tamArrayFinal; j++) {   //procurando no array quantos descrevem
                if (taNaString(get<0>(arrayMintermos[i]), get<0>(minTabela[j]))){
                    //numero de mintermos                 par de Mintermos
                    get<3>(minTabela[j]) = true; 
                    get<4>(minTabela[j]) = true; 
                    get<2>(arrayMintermos[i]) = true; 
                }
            }
        }
    }

    //imprimir uma parte do texto

    cout << "\n\nPrimos essenciais: \n";

    for (int i = 0; i < tamArrayFinal; i++) {
        if (get<3>(minTabela[i])) 
            cout << get<0>(minTabela[i]) << " = " << binarioToMintermo(get<1>(minTabela[i]))<<"\n";
    }  

    //marcar os outros marcados pelos primos essenciais como ja descritos
    for (int i = 0; i < tamArrayFinal; i++) {
        if (get<3>(minTabela[i])){
            for(int j = 0; j < nroMintermos; j++) {
                if (taNaString(get<0>(arrayMintermos[j]), get<0>(minTabela[i]))) {
                    get<2>(arrayMintermos[j]) = true; 
                }
            }
        }
    }  

    // percorrer e decidir outros (deixar essenciais de fora)
    for (int i = 0; i < nroMintermos; i++) {                        //iterando pra todos os mintermos
        
        if(!get<2>(arrayMintermos[i])){                             //se o mintermo nao ta descrito ainda 
            for (int j = tamArrayFinal-1; j >= 0; j--) {               //procurando no array um q descreva ele, comecando dos q descrevem mais pra menos
                if (taNaString(get<0>(arrayMintermos[i]), get<0>(minTabela[j])) && !get<2>(arrayMintermos[i])){
                    get<4>(minTabela[j]) = true; 
                    get<2>(arrayMintermos[i]) = true; 
                }
            }
        }
    }

    // imprimir resultado
    cout << "\n\nFuncao sugerida: \n";

    bool primeiro = true; 
    for (int i = 0; i < tamArrayFinal; i++) {
        if (get<4>(minTabela[i])) 
            if(primeiro) {
                cout << binarioToMintermo(get<1>(minTabela[i]));
                primeiro = false; 
            }
            else cout  << " + " << binarioToMintermo(get<1>(minTabela[i]));
    }  
    cout << "\n"; 
    for (int i = 0; i < tamArrayFinal; i++) {
        if (get<4>(minTabela[i])) 
            
        cout  << get<0>(minTabela[i]) << " ";
    } 
}
bool taNaString (int nro, string stringBusca) {
    int count; 
    bool tem; 
    string nroString; 

    nroString = to_string(nro); 
    count = stringBusca.length(); 

    //nroString representa o número, agora vou procurar ele na string    
    tem = false; 
    if (nroString.length() == 2) {
        for(int k = 0; k < (count-1); k++) { // 0,1,2,13 tam=8  k<7
                if ((stringBusca[k] == nroString[0]) && stringBusca[k+1] == nroString[1]) {
                    tem = true;                         
                }
        }
    }
    else if (nroString.length() == 1) {
        for(int k = 0; k < count; k++) { // 0,1,2,13 tam=8  k<7
            if (stringBusca[k] == nroString[0] && stringBusca[k-1] != '1') {
                tem = true; 
            }
        }
    }
    return tem; 
}

string binarioToMintermo(string binario) {

    int count;
    string mintermo; 

    count = binario.length();

    for (int i = 0; i<count; i++) {
        if (binario[i] != '-'){
            if (binario[i] == '0') {
                if (i == 0)
                    mintermo += "A'"; 
                if (i == 1)
                    mintermo += "B'"; 
                if (i == 2)
                    mintermo += "C'"; 
                if (i == 3)
                    mintermo += "D'"; 
            }
            else if(binario[i] == '1') {
                if (i == 0)
                    mintermo += "A"; 
                if (i == 1)
                    mintermo += "B"; 
                if (i == 2)
                    mintermo += "C"; 
                if (i == 3)
                    mintermo += "D"; 
            }
        } 
    }
    return mintermo; 
}