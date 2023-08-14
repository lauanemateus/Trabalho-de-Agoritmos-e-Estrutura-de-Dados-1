#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

#define maxTAM 100
#define stringTAM 50

typedef struct NO *TipoApontador;

typedef struct Data{
    int dia, mes, ano;
} Data;

typedef struct NO{
    char nome[stringTAM];
    char disciplina[stringTAM];
    int dificuldade;
    int nota;
    Data data;
    TipoApontador prox;
} NO;

typedef struct{
    TipoApontador inicio;
    int tam;
}Agenda_Prioridade;

typedef struct{
    NO Vet[maxTAM];
    int tam;
}Agenda_Vetorial;

void menu();
void inicializar(Agenda_Prioridade *agenda_prioridade);
void tempoAtual(Data *atual);
void inserirInicio(Agenda_Prioridade *agenda_prioridade, TipoApontador  aux);
void removerInicio(Agenda_Prioridade *agenda_prioridade);
void imprimirAgendaPrioridade(Agenda_Prioridade agenda_prioridade);
void inserirApos(Agenda_Prioridade *agenda_prioridade, TipoApontador nova_tarefa, TipoApontador X);
void imprimirDisciplina(Agenda_Prioridade agenda_prioridade, char disciplina[]);
void atribuirNO(TipoApontador new_no, char nome[], char disciplina[], int dificuldade, int nota, Data data);
void removerAgendaPrioridade(Agenda_Prioridade *agenda_prioridade, char nome[]);
void inserirAgendaPrioridade(Agenda_Prioridade *agenda_prioridade, TipoApontador nova_tarefa);
void inicializar_2(Agenda_Vetorial *agenda_vetorial);
void inserir(Agenda_Vetorial *agenda_vetorial, TipoApontador aux);
void removerAgendaVetorial(Agenda_Vetorial *agenda_vetorial, char nome[]);
void selectionSort(Agenda_Vetorial *agenda_vetorial);
int comparaDatas(Data d1, Data d2,Agenda_Vetorial *agenda_vetorial, int i, int j);
int buscaSequencial(Agenda_Vetorial *agenda_vetorial, char nome[]);
int comparaDatasBuscaBinaria(Data d1, Data d2, Agenda_Vetorial *agenda_vetorial);
int buscaBinaria(Agenda_Vetorial *agenda_vetorial, Data x);
void imprimirAgendaVetorial(Agenda_Vetorial agenda_vetorial);
void imprimirAteData(Agenda_Vetorial agenda_vetorial, Data x);
void MergeSort(int ini, int fim, Agenda_Vetorial *agenda_vetorial);
void Merge(int ini, int meio, int fim, Agenda_Vetorial *agenda_vetorial);
void mostrarAtividadesDia (Agenda_Vetorial agenda_vetorial, Data atual);    
int concluirAtividadesDia(Agenda_Vetorial *agenda_vetorial, Agenda_Prioridade *agenda_prioridade, Data x);
void mostrarProximaAtividade(Agenda_Prioridade agenda_prioridade, Agenda_Vetorial agenda_vetorial, Data x);
void concluirProximaAtividade(Agenda_Prioridade *agenda_prioridade, Agenda_Vetorial *agenda_vetorial, Data x);
int removerAtrasadas(Agenda_Vetorial *agenda_vetorial, Agenda_Prioridade *agenda_prioridade, Data atual);
int comparaDatasHoje(Data d1, Data d2);
void MostrarAtividadesDeUmDia(Agenda_Vetorial *agenda_vetorial, Data x);
void concluirAtividadesDeUmDia(Agenda_Vetorial *agenda_vetorial,Agenda_Prioridade *agenda_prioridade, Data data);