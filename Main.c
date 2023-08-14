#include "Tad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

int main() {
    int x, n, y, i, j;
    Agenda_Prioridade agenda_prioridade; 
    Agenda_Vetorial agenda_vetorial;
    TipoApontador aux, aux_;
    char nome[stringTAM], disciplina[stringTAM];
    int dificuldade, nota;
    Data data, data_atual;
    inicializar(&agenda_prioridade); // inicializa agenda com apontadores
    inicializar_2(&agenda_vetorial); // inicializa agenda vetorial
    
    tempoAtual(&data_atual); // salva a data do dia que o programa esta sendo usado

    // as informacoes das duas listas sao lidas no arquivo binario
    FILE *arq = NULL;
    arq = fopen("dados.bin", "rb");
    if(arq == NULL){
        printf("Erro\n");
        return 0;
    }
    fread((void*)&agenda_prioridade.tam, sizeof(int), 1, arq);
    for(i=0; i<agenda_prioridade.tam; i++){
        if(i==0){
            agenda_prioridade.inicio = (TipoApontador)malloc(sizeof(NO));
            aux = agenda_prioridade.inicio;
        }
        fread((void*)aux->nome, sizeof(char), stringTAM, arq);
        fread((void*)aux->disciplina, sizeof(char), stringTAM, arq);
        fread((void*)&aux->dificuldade, sizeof(int), 1, arq);
        fread((void*)&aux->nota, sizeof(int), 1, arq);
        fread((void*)&aux->data, sizeof(Data), 1, arq);
        aux->prox = (TipoApontador)malloc(sizeof(NO));
        if(i!=agenda_prioridade.tam-1) aux = aux->prox;
    }
    if(aux!=NULL){
        aux->prox = NULL;
    }
    fread((void*)&agenda_vetorial.tam, sizeof(int), 1, arq);
    fread((void*)agenda_vetorial.Vet, sizeof(NO), maxTAM, arq);

    selectionSort(&agenda_vetorial);
    printf("Data de hoje: %02d/%02d/%04d\n", data_atual.dia, data_atual.mes, data_atual.ano);
    printf("------Remoção automatica de atividades atrasadas--------\n");
    removerAtrasadas(&agenda_vetorial, &agenda_prioridade, data_atual);
    printf("--------------------------------------------------------\n");

    menu();
    while(scanf("%d", &x)!=EOF){
        printf("\n");
        switch(x){
            case 0: // antes do programa terminar, o programa atualiza as informacoes das listas no arquivo binario
                fclose(arq);
                arq = fopen("dados.bin", "wb");
                if(arq == NULL){
                    printf("Erro\n");
                    return 0;
                }
                fwrite((void*)&agenda_prioridade.tam, sizeof(int), 1, arq);
                for(i=0; i<agenda_prioridade.tam; i++){
                    if(i==0){
                        aux = agenda_prioridade.inicio;
                    }
                    fwrite((void*)aux->nome, sizeof(char), stringTAM, arq);
                    fwrite((void*)aux->disciplina, sizeof(char), stringTAM, arq);
                    fwrite((void*)&aux->dificuldade, sizeof(int), 1, arq);
                    fwrite((void*)&aux->nota, sizeof(int), 1, arq);
                    fwrite((void*)&aux->data, sizeof(Data), 1, arq);
                    aux = aux->prox;
                }
                aux = agenda_prioridade.inicio;
                while(aux!=NULL){
                    aux_ = aux->prox;
                    free(aux);
                    aux = aux_;
                }
                fwrite((void*)&agenda_vetorial.tam, sizeof(int), 1, arq);
                fwrite((void*)agenda_vetorial.Vet, sizeof(NO), maxTAM, arq);
                printf("Programa finalizado.\n");
                return 0;
            case 1: //inserir uma atividade na agenda
                printf("Digite o nome da atividade: ");
                scanf("%*c%[^\n]", nome);
                printf("Digite o nome da disciplina: ");
                scanf("%*c%[^\n]", disciplina);
                printf("Digite a sua dificuldade nessa disciplina (de 0 a 10): ");
                scanf("%d", &dificuldade);
                printf("Digite a nota que vale essa atividade (de 1 a 10): ");
                scanf("%d", &nota);
                printf("Digite a data da atividade\n");
                printf("Dia: ");
                scanf("%d", &data.dia);
                printf("Mês: ");
                scanf("%d", &data.mes);
                printf("Ano: ");
                scanf("%d", &data.ano);
                aux = (TipoApontador)malloc(sizeof(NO));
                printf("\n");
                atribuirNO(aux, nome, disciplina, dificuldade, nota, data);
                inserir(&agenda_vetorial, aux);
                inserirAgendaPrioridade(&agenda_prioridade, aux);
                break;
            case 2: // mostrar as atividades do dia
                printf("\n");
                MergeSort(0, agenda_vetorial.tam-1, &agenda_vetorial);
                mostrarAtividadesDia(agenda_vetorial, data_atual);
                break;
            case 3: // para mostrar a proxima atividade que precisa ser feita
                printf("\n");
                selectionSort(&agenda_vetorial);
                mostrarProximaAtividade(agenda_prioridade, agenda_vetorial, data_atual);
                break;
            case 4: // mostrar todas as atividades segunda a ordem cronologica de entrega
                printf("\n");
                selectionSort(&agenda_vetorial);
                imprimirAgendaVetorial(agenda_vetorial);
                break;
            case 5: // mostrar as atividades baseado na prioridade - Nota e Dificuldade -
                printf("\n");
                imprimirAgendaPrioridade(agenda_prioridade);
                break;
            case 6: // mostrar todas as atividades a serem feitas ate certo dia
                printf("Digite a data a qual será realizada a comparação\n");
                printf("Dia: ");
                scanf("%d", &data.dia);
                printf("Mês: ");
                scanf("%d", &data.mes);
                printf("Ano: ");
                scanf("%d", &data.ano);
                printf("\n");
                selectionSort(&agenda_vetorial);
                imprimirAteData(agenda_vetorial, data);
                break;
            case 7: // mostrar todas as atividades de uma disciplina
                printf("Digite a disciplina na qual deseja mostrar as atividades: ");
                scanf("%*c%[^\n]", disciplina);
                printf("\n");
                imprimirDisciplina(agenda_prioridade, disciplina);
                break;
            case 8: // marcar como concluida a proxima atividade
                printf("\n");
                MergeSort(0, agenda_vetorial.tam-1, &agenda_vetorial);
                concluirProximaAtividade(&agenda_prioridade, &agenda_vetorial, data_atual);
                break;
            case 9: // marcar como concluida todas as atividades de um dia
                printf("\n");
                MergeSort(0, agenda_vetorial.tam-1, &agenda_vetorial);
                printf("Digite a data na qual deseja remover as atividades\n");
                printf("Dia: ");
                scanf("%d", &data.dia);
                printf("Mês: ");
                scanf("%d", &data.mes);
                printf("Ano: ");
                scanf("%d", &data.ano);
                y = buscaBinaria(&agenda_vetorial, data);
                concluirAtividadesDeUmDia(&agenda_vetorial, &agenda_prioridade, data);
                break;
            case 10: // marcar como concluida uma atividade especifica
                printf("Digite o nome da atividade que deseja remover: ");
                printf("\n");
                scanf("%*c%[^\n]", nome);
                removerAgendaPrioridade(&agenda_prioridade, nome);
                removerAgendaVetorial(&agenda_vetorial, nome);
                break;
            case 11: //mostrar todas as atividades de uma data especifica
                selectionSort(&agenda_vetorial);
                printf("Digite a data a ser consultada\n");
                printf("Dia: ");
                scanf("%d", &data.dia);
                printf("Mês: ");
                scanf("%d", &data.mes);
                printf("Ano: ");
                scanf("%d", &data.ano);
                MostrarAtividadesDeUmDia(&agenda_vetorial, data);
                break;
            default:
                printf("Digitação errada\n");
                break;
        }
        menu();
    }
}   