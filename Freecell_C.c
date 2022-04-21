#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{false, true} bool;

typedef struct stCarta{
    short numero;
    char naipe;
    struct stCarta *prox;
}tCarta; //estrutura das cedulas

tCarta *primMesa[8]; //pilhas de cartas
tCarta *primNaipe[4];//pilha de naipes
tCarta *temp[4];//�rea auxiliar temporaria
tCarta *primMonte = NULL;//indica o in�cio da lista de cartas a serem geradas.

int tp, np, m, m2, quant;//utilizadas para movimenta��o (valores passados em cada uma das fun��es)

void inicializaGame(void){
    int i;
    for(i=0; i<8; i++){//cada posicao de primMesa = NULL;
        primMesa[i] = NULL;
    }
    for(i=0; i<4; i++){//cada posicao de primNaipe = NULL;
        primNaipe[i] = NULL;
    }
    for(i=0; i<4; i++){//cada posicao de temp = NULL;
        temp[i] = NULL;
    }
}

void geraBaralho(void){
    int i, j;
    tCarta *novo = NULL;

    for(i=3; i<7; i++){//naipes
        for(j=1; j<=13; j++){//cartas
            novo = (tCarta*)malloc(sizeof(tCarta));//alocando memoria
            novo->naipe = i;
            novo->numero = j;
            novo->prox = primMonte;
            primMonte = novo;
        }
    }
}

void embaralhaBaralho(void){
    int i, j, k, posicao1, posicao2;
    tCarta *aux = NULL, *elem1 = NULL, *elem2 = NULL;
    
    for(i=0; i<1000; i++){//loop acontece 1000 vezes(vontade divina)
        posicao1 = rand()%52;//sorteia carta 1
        posicao2 = rand()%52;//sorteia carta 2


        elem1 = primMonte;
        elem2 = primMonte;
        aux = primMonte;

        if((posicao1 != posicao2)&&(posicao1>0)&&(posicao2>0)){//se os numeros sorteados nao forem iguais e forem maior que 0
            for(j=0; j<posicao1; j++){//caminhar elemento 1 at� a carta sorteada atualizando ponteiros
                elem1 = elem1->prox;
            }
            for(k=0; k<posicao2; k++){//caminhar elemento 2 at� a carta sorteada atualizando ponteiros
                elem2 = elem2->prox;
            }
            //troca
            aux->numero = elem1->numero;
            aux->naipe = elem1->naipe;
            elem1->numero = elem2->numero;
            elem1->naipe = elem2->naipe;
            elem2->numero = aux->numero;
            elem2->naipe = aux->naipe;
        }
        else{
            i--;
        }
    }
}

void distribuirMesa(void){
    int i, j;

    tCarta *atual = NULL;

    for(i=0; i<6; i++){
        for(j=0; j<8; j++){
            atual = primMonte;
            primMonte = atual->prox;

            atual->prox = primMesa[j];
            primMesa[j] = atual;

        }
    }

    for(i=0; i<4; i++){
        atual = primMonte;
        primMonte = atual->prox;

        atual->prox = primMesa[i];
        primMesa[i] = atual;
    }
}

void imprime(void){
    int i;
    tCarta *atual = NULL;

    printf("\t\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    printf("\n\t\t\t\t\xBA    SEJA BEM-VINDO AO FREECELL!    \xBA\n");
    printf("\t\t\t\t\xC8");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n");

    printf("[TEMP]: ");//impressao temporaria
    for(i=0; i<4; i++){
        atual = temp[i];
        if(atual != NULL){
            printf("%d-[%2d/%c] ", i, atual->numero, atual->naipe);
        }
        else{
            printf("%d-[   ] ", i);
        }
    }
    printf("\n\n");

    for(i=0; i<4; i++){
        atual = primNaipe[i];
        printf("[NAIPE %d] = ", i);//ala dos naipes
        while(atual != NULL){
            printf("[%2d/%c] ", atual->numero, atual->naipe);
            atual = atual->prox;
        }
        printf("\n");
    }
    printf("\n");

    for(i=0; i<8; i++){
        atual = primMesa[i];
        printf("[MESA %d] = ", i);//mesa
        while(atual != NULL){
            printf("[%2d/%c] ", atual->numero, atual->naipe);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void moveMesaTemp(void){
    tCarta *aux = NULL;

    if((temp[tp]==NULL)&&(primMesa[m]!=NULL)&&((tp<=3)&&(tp>=0))&&((m<=7)&&(m>=0))){//se a pilha temporia estiver vazia e pilha da mesa n estiver vazia e atende os limites
        aux = primMesa[m];
        primMesa[m] = aux->prox;
        aux->prox = temp[tp];
        temp[tp] = aux;
        printf("\nMovimento realizado!");
    }
    else{
        printf("\nMovimento invalido!\n");
    }
}

void moveTempMesa(void){
    tCarta *aux = NULL;

    if(temp[tp]!=NULL){
        if((tp<=3)&&(tp>=0)&&(m<=7)&&(m>=0)){//limites
            if(primMesa[m]==NULL){
                aux = temp[tp];
                temp[tp] = aux->prox;
                aux->prox = primMesa[m];
                primMesa[m] = aux;
                printf("\nMovimento realizado!\n");
            }
            else{
                if(temp[tp]->numero < primMesa[m]->numero){
                    if((((temp[tp]->naipe==3)||(temp[tp]->naipe==4))&&((primMesa[m]->naipe==5)||(primMesa[m]->naipe==6)))||
                    (((temp[tp]->naipe==5)||(temp[tp]->naipe==6))&&((primMesa[m]->naipe==3)||(primMesa[m]->naipe==4)))){//testando as cores
                        aux = temp[tp];
                        temp[tp] = aux->prox;
                        aux->prox = primMesa[m];
                        primMesa[m] = aux;
                        printf("\nMovimento realizado!\n");
                    }
                    else{
                        printf("\nMovimento invalido: cores iguais\n");
                    }
               }
               else{
                    printf("\nMovimento invalido: numero maior ou igual\n");
               }
           }
        }
        else{
            printf("\nMovimento invalido: limites estourados\n");
        }
    }
}

void moveMesaNaipe(void){
    tCarta *aux = NULL;

    switch(primMesa[m]->naipe){
    case 3:
        if((primNaipe[np]==NULL)&&(primMesa[m]->numero==1)&&(np<=3)&&(np>=0)){//se o monte estiver vazio e a carta da mesa for �s + teste limite parcial (restante esta na main - adaptacao feita)
            aux = primMesa[m];
            primMesa[m] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(primMesa[m]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da mesa ser = a do naipe +1
                if((primNaipe[np]->naipe==3)&&(primNaipe[np]->numero < primMesa[m]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da mesa(esse ultimo eh inutil, tirar depois)
                    aux = primMesa[m];
                    primMesa[m] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;

    case 4:
       if((primNaipe[np]==NULL)&&(primMesa[m]->numero==1)&&(np<=3)&&(np>=0)){//se o monte estiver vazio e a carta da mesa for �s
            aux = primMesa[m];
            primMesa[m] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(primMesa[m]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da mesa ser = a do naipe +1
                if((primNaipe[np]->naipe==4)&&(primNaipe[np]->numero < primMesa[m]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da mesa(esse ultimo eh inutil, tirar depois)
                    aux = primMesa[m];
                    primMesa[m] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }

    break;

    case 5:
      if((primNaipe[np]==NULL)&&(primMesa[m]->numero==1)&&(np<=3)&&(np>=0)){//se o monte estiver vazio e a carta da mesa for �s
            aux = primMesa[m];
            primMesa[m] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(primMesa[m]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da mesa ser = a do naipe +1
                if((primNaipe[np]->naipe==5)&&(primNaipe[np]->numero < primMesa[m]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da mesa(esse ultimo eh inutil, tirar depois)
                    aux = primMesa[m];
                    primMesa[m] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
        break;

    case 6:
        if((primNaipe[np]==NULL)&&(primMesa[m]->numero==1)&&(np<=3)&&(np>=0)){//se o monte estiver vazio e a carta da mesa for �s
            aux = primMesa[m];
            primMesa[m] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(primMesa[m]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da mesa ser = a do naipe +1
                if((primNaipe[np]->naipe==6)&&(primNaipe[np]->numero < primMesa[m]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da mesa(esse ultimo eh inutil, tirar depois)
                    aux = primMesa[m];
                    primMesa[m] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;
    }//end SC
}

void moveNapeTemp(void){
    tCarta *aux = NULL;

    if((temp[tp]==NULL)&&(primNaipe[np]!=NULL)&&((tp<=3)&&(tp>=0))&&((np<=3)&&(np>=0))){//se a pilha temporia estiver vazia e pilha de naipe nao estiver vazia e atende os limites
        aux = primNaipe[np];
        primNaipe[np] = aux->prox;
        aux->prox = temp[tp];
        temp[tp] = aux;
        printf("\nMovimento realizado!");
    }
    else{
        printf("\nMovimento invalido!\n");
    }
}

void moveTempNape(void){
    tCarta *aux = NULL;

    switch(temp[tp]->naipe){
    case 3:
        if((primNaipe[np]==NULL)&&(temp[tp]->numero==1)&&(np<=3)&&(np>=0)&&(tp<=3)&&(tp>=0)){//se o monte estiver vazio e a carta do temp for �s + teste limite
            aux = temp[tp];
            temp[tp] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(temp[tp]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da temp ser = a do naipe +1
                if((primNaipe[np]->naipe==3)&&(primNaipe[np]->numero < temp[tp]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da temp
                    aux = temp[tp];
                    temp[tp] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;

    case 4:
        if((primNaipe[np]==NULL)&&(temp[tp]->numero==1)&&(np<=3)&&(np>=0)&&(tp<=3)&&(tp>=0)){//se o monte estiver vazio e a carta do temp for �s + teste limite
            aux = temp[tp];
            temp[tp] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(temp[tp]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da temp ser = a do naipe +1
                if((primNaipe[np]->naipe==4)&&(primNaipe[np]->numero < temp[tp]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da temp
                    aux = temp[tp];
                    temp[tp] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;

    case 5:
        if((primNaipe[np]==NULL)&&(temp[tp]->numero==1)&&(np<=3)&&(np>=0)&&(tp<=3)&&(tp>=0)){//se o monte estiver vazio e a carta do temp for �s + teste limite
            aux = temp[tp];
            temp[tp] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(temp[tp]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da temp ser = a do naipe +1
                if((primNaipe[np]->naipe==5)&&(primNaipe[np]->numero < temp[tp]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da temp
                    aux = temp[tp];
                    temp[tp] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;

    case 6:
        if((primNaipe[np]==NULL)&&(temp[tp]->numero==1)&&(np<=3)&&(np>=0)&&(tp<=3)&&(tp>=0)){//se o monte estiver vazio e a carta do temp for �s + teste limite
            aux = temp[tp];
            temp[tp] = aux->prox;
            aux->prox = primNaipe[np];
            primNaipe[np] = aux;
            printf("\nMovimento realizado!\n");
        }
        else{
            if((primNaipe[np]!=NULL)&&(temp[tp]->numero == primNaipe[np]->numero+1)){//se o monte ja possuir carta e o numero da carta da temp ser = a do naipe +1
                if((primNaipe[np]->naipe==6)&&(primNaipe[np]->numero < temp[tp]->numero)){//condi��es: naipe ser igual e numero do monte de naipe menor que da temp
                    aux = temp[tp];
                    temp[tp] = aux->prox;
                    aux->prox = primNaipe[np];
                    primNaipe[np] = aux;
                    printf("\nMovimento realizado!\n");
                }
                else{
                    printf("\nMovimento Invalido!\n");
                }
            }
            else{
                printf("\nMovimento Invalido!\n");
            }
        }
    break;
    }//end SC
}

void moveNapeMesa(void){
    tCarta *aux = NULL;

    if(primNaipe[np]!=NULL){
        if((np<=3)&&(np>=0)&&(m<=7)&&(m>=0)){//limites
            if(primMesa[m]==NULL){
                aux = primNaipe[np];
                primNaipe[np] = aux->prox;
                aux->prox = primMesa[m];
                primMesa[m] = aux;
                printf("\nMovimento realizado!\n");
            }
            else{
                if(primNaipe[np]->numero < primMesa[m]->numero){
                    if((((primNaipe[np]->naipe==3)||(primNaipe[np]->naipe==4))&&((primMesa[m]->naipe==5)||(primMesa[m]->naipe==6)))||
                    (((primNaipe[np]->naipe==5)||(primNaipe[np]->naipe==6))&&((primMesa[m]->naipe==3)||(primMesa[m]->naipe==4)))){//testando as cores
                        aux = primNaipe[np];
                        primNaipe[np] = aux->prox;
                        aux->prox = primMesa[m];
                        primMesa[m] = aux;
                        printf("\nMovimento realizado!\n");
                    }
                    else{
                        printf("\nMovimento invalido: cores iguais\n");
                    }
               }
               else{
                    printf("\nMovimento invalido: numero maior ou igual\n");
               }
           }
        }
        else{
            printf("\nMovimento invalido: limites estourados\n");
        }
    }
}

void moveMesaMesa (void){
    tCarta *aux = NULL;
    tCarta *auxPack[quant];

    int i;

    if((primMesa[m]!=NULL)&& (m2<=7)&&(m2>=0)&&(m<=7)&&(m>=0)&&(m!=m2)){
        if((m2<=7)&&(m2>=0)&&(m<=7)&&(m>=0)&&(m!=m2)){//limites
            if(primMesa[m2]==NULL){
                aux = primMesa[m];
                primMesa[m] = aux->prox;
                aux->prox = primMesa[m2];
                primMesa[m2] = aux;
                printf("\nMovimento realizado!\n");
            }
            else{
                if(primMesa[m]->numero < primMesa[m2]->numero){
                    if((((primMesa[m2]->naipe==3)||(primMesa[m2]->naipe==4))&&((primMesa[m]->naipe==5)||(primMesa[m]->naipe==6)))||
                    (((primMesa[m2]->naipe==5)||(primMesa[m2]->naipe==6))&&((primMesa[m]->naipe==3)||(primMesa[m]->naipe==4)))){
                        aux = primMesa[m];
                        primMesa[m] = aux->prox;
                        aux->prox = primMesa[m2];
                        primMesa[m2] = aux;
                        printf("\nMovimento realizado!\n");
                    }
                    else{
                        printf("\nMovimento invalido: cores iguais\n");
                    }
                }
                else{
                    printf("\nMovimento invalido: numero maior ou igual\n");
                }
            }
        }
        else{
            printf("\nMovimento invalido: limites estourados\n");
        }
    }
    else{
        printf("\nMovimento invalido: mesa de origem vazia ou mesas iguais!\n");
    }
}


void destroiPilha(void){
    tCarta *atual, *apaga;

    for(int i=0;i<8;i++){
        atual = primMesa[i];
        while(atual != NULL){
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }//end while
    }
    for(int j=0;j<4;j++){
        atual = primNaipe[j];
        while(atual != NULL){
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }//end while
    }

    for(int l=0;l<4;l++){
        atual = temp[l];
        while(atual != NULL){
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }//end while
    }
}

int main(int argc, char **argv){
    printf("\t\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    printf("\n\t\t\t\t\xBA    SEJA BEM-VINDO AO FREECELL!    \xBA\n");
    printf("\t\t\t\t\xC8");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n");

    bool beg = false;
    int auxbeg = 0;
    do{
        printf("1: REGRAS DO JOGO\n");
        printf("2: START GAME\n");
        printf("\nOp: ");
        scanf("%d", &auxbeg);

        if(auxbeg == 1){
            printf("\nO objetivo do jogador eh mover todas as cartas para as pilhas de naipes em ordem crescente no naipe, usando o menor numero possivel de movimentos\n");  
            system("pause");
            system("cls");
            beg = true;      
        }else{
            if(auxbeg == 2){
                system("cls");
                beg = true;
            }
        }
    }while(beg == false);
    
    srand(time(NULL));
    int op;

    inicializaGame();
    geraBaralho();
    embaralhaBaralho();
    distribuirMesa();
    imprime();

    do{
        printf("\nO que deseja fazer?\n\n");
        printf("(1) Mesa - Temporaria");
        printf("\n(2) Temporaria - mesa");
        printf("\n(3) Mesa - Naipe");
        printf("\n(4) Naipe - Temporaria");
        printf("\n(5) Temporario - Naipes");
        printf("\n(6) Naipe - Mesa");
        printf("\n(7) Mesa - Mesa");
        printf("\n(8) Sair\n\n");
        scanf("%d", &op);

        switch(op){
        case 1:
            printf("\nDigite a pilha que deseja retirar a carta: ");
            scanf("%d",&m);
            printf("\nDigite a pilha temporaria que deseja depositar a carta: ");
            scanf("%d", &tp);
            moveMesaTemp();
            printf("\n");
            imprime();
            break;

        case 2:
            printf("\nDigite a pilha temporaria que deseja retirar a carta: ");
            scanf("%d", &tp);
            printf("\nDigite a pilha da mesa que deseja depositar a carta: ");
            scanf("%d", &m);
            moveTempMesa();
            printf("\n");
            imprime();
            break;

        case 3:
            printf("\nDigite a pilha da mesa que deseja retirar a carta: ");
            scanf("%d", &m);
            printf("\nDigite a pilha de naipes que deseja depositar a carta: ");
            scanf("%d", &np);
            if(m<=7 && m>=0){
                moveMesaNaipe();
                printf("\n");
                imprime();
            }
            else{
                printf("\nMovimento invalido\n\n");
                imprime();
            }
            break;

        case 4:
            printf("\nDigite a pilha de naipes que deseja retirar a carta: ");
            scanf("%d",&np);
            printf("\nDigite a pilha temporaria que deseja depositar a carta: ");
            scanf("%d", &tp);
            moveNapeTemp();
            printf("\n");
            imprime();
            break;

        case 5:
            printf("\nDigite a pilha temporaria que deseja retirar a carta: ");
            scanf("%d",&tp);
            printf("\nDigite a pilha de naipe que deseja depositar a carta: ");
            scanf("%d", &np);
            moveTempNape();
            printf("\n");
            imprime();
            break;

        case 6:
            printf("\nDigite a pilha de naipe que deseja retirar a carta: ");
            scanf("%d",&np);
            printf("\nDigite a pilha da mesa que deseja depositar a carta: ");
            scanf("%d", &m);
            moveNapeMesa();
            printf("\n");
            imprime();
            break;

        case 7:
            printf("\nDigite a pilha da mesa que deseja retirar a carta: ");
            scanf("%d",&m);
            printf("\nDigite a pilha da mesa que deseja depositar a carta: ");
            scanf("%d", &m2);
            moveMesaMesa();
            printf("\n");
            imprime();
            break;

        case 8:
            break;

        default:
            break;
        }

    }while(op!=8);
    printf("\nOBRIGADO PELO GAME! VOLTE SEMPRE!");
    destroiPilha();

    return 0;
}

