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
