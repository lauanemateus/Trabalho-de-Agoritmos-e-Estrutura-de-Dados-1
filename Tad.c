#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Tad.h"
#include<time.h>

void menu(){
    printf("\nDigite a opção a ser exercutada\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("Digite 1 para inserir uma atividade na agenda\n");
    printf("Digite 2 para mostrar as atividades marcadas para hoje\n");
    printf("Digite 3 para mostrar a proxima atividade que precisa ser feita\n");
    printf("Digite 4 para mostrar todas as atividades segunda a ordem cronologica de entrega\n");
    printf("Digite 5 para mostrar as atividades baseado na prioridade - Nota e Dificuldade - \n");
    printf("Digite 6 para mostrar todas as atividades a serem feitas até certo dia\n");
    printf("Digite 7 para mostrar todas as atividades de uma disciplina especifica\n");
    printf("Digite 8 para marcar como concluida a proxima atividade\n");
    printf("Digite 9 para marcar como concluida todas as atividades de um dia\n");
    printf("Digite 10 para marcar como concluida uma atividade especifica\n");
    printf("Digite 11 para mostrar todas as atividade de um dia\n");
    printf("Digite 0 para sair do programa\n");
    printf("-----------------------------------------------------------------------------------\n");
}

void tempoAtual(Data *atual){
    struct tm data;
    time_t segundos;
    time(&segundos);
    data = *localtime(&segundos);
    atual->dia = data.tm_mday;
    atual->mes = data.tm_mon+1;
    atual->ano = data.tm_year+1900;
}

void inserirApos(Agenda_Prioridade *agenda_prioridade, TipoApontador nova_tarefa, TipoApontador X){
    if(agenda_prioridade->tam==0){
        inserirInicio(agenda_prioridade, nova_tarefa);
    }
    nova_tarefa->prox = X->prox;
    X->prox = nova_tarefa;
    agenda_prioridade->tam++;
}

void inicializar(Agenda_Prioridade *agenda_prioridade){
    agenda_prioridade->inicio=NULL;
    agenda_prioridade->tam=0;
}
void inserirInicio(Agenda_Prioridade *agenda_prioridade, TipoApontador aux){
    if(aux==NULL){
        printf("Erro ao alocar\n");
        return ;
    }
    else{
        if(agenda_prioridade->inicio==NULL){
            aux->prox=NULL;
            agenda_prioridade->inicio=aux;
        }
        else{
            aux->prox = agenda_prioridade->inicio;
            agenda_prioridade->inicio=aux;
        }
    }
    agenda_prioridade->tam++;
}

void removerInicio(Agenda_Prioridade *agenda_prioridade){
    TipoApontador aux=agenda_prioridade->inicio;
    if(aux==NULL){
        printf("Não há nehuma atividade na agenda\n");
        return;
    }
    if(agenda_prioridade->inicio!=NULL){
        agenda_prioridade->inicio=aux->prox;
        free(aux);
        agenda_prioridade->tam--;
    }
}
void imprimirAgendaPrioridade(Agenda_Prioridade agenda_prioridade){
    TipoApontador aux;
    aux=agenda_prioridade.inicio;
    if(agenda_prioridade.tam==0){
        printf("Não há nenhuma atividade na agenda\n");
        return;
    }
    printf("-------------------Atividades da agenda-----------------\n");
    while(aux!=NULL){
        printf("Nome da atividade: %s\nDisciplina: %s\nDificuldade: %d\nNota: %d\nData de entrega: %02d/%02d/%04d\n",
            aux->nome, aux->disciplina, aux->dificuldade, aux->nota, aux->data.dia, aux->data.mes, aux->data.ano);
        printf("--------------------------------------------------------\n"); 
        aux=aux->prox;
    }
}

void imprimirDisciplina(Agenda_Prioridade agenda_prioridade, char disciplina[]){
    TipoApontador aux;
    aux=agenda_prioridade.inicio;
    int ok=0;
    if(agenda_prioridade.tam==0){
        printf("Não há nenhuma atividade na agenda\n");
        return;
    }
    while(aux!=NULL){
        if(strcmp(aux->disciplina, disciplina) == 0){
            if(ok==0){
                printf("----------------Atividades da disciplina----------------\n"); 
                ok=1;
            }
            printf("Nome da atividade: %s\nDisciplina: %s\nDificuldade: %d\nNota: %d\nData de entrega: %02d/%02d/%04d\n",
                aux->nome, aux->disciplina, aux->dificuldade, aux->nota, aux->data.dia, aux->data.mes, aux->data.ano);
            printf("--------------------------------------------------------\n"); 
        }
        aux=aux->prox;
    }
    if(ok==0){
        printf("Não há atividade da disciplina %s\n", disciplina);
    }
}

void retiraApos(Agenda_Prioridade *agenda_prioridade, TipoApontador X){
    TipoApontador aux;
    if(agenda_prioridade->tam==1){
        return;
    }
    aux = X->prox;
    X->prox = aux->prox;
    agenda_prioridade->tam--;
    free(aux);
}

void removerAgendaPrioridade(Agenda_Prioridade *agenda_prioridade, char nome[]){
    int i=0;
    TipoApontador aux = agenda_prioridade->inicio;
    while(aux!=NULL ){
        if(i==0 && strcmp(nome, aux->nome)==0){
            removerInicio(agenda_prioridade);
            return;
        }
        else if(agenda_prioridade->tam>1 && aux->prox!=NULL && strcmp(nome, aux->prox->nome)==0){
            retiraApos(agenda_prioridade, aux);
            return;
        }
        else aux = aux->prox;
        i++;
    }
}

void inserirAgendaPrioridade(Agenda_Prioridade *agenda_prioridade, TipoApontador nova_tarefa){ // função que irá inserir o elemento já na sua ordem de prioridade
    int prioridade = nova_tarefa->nota + nova_tarefa->dificuldade;
    TipoApontador aux = agenda_prioridade->inicio;
    if(aux==NULL || aux->nota+aux->dificuldade<prioridade){
        inserirInicio(agenda_prioridade, nova_tarefa);
        return;
    }
    while(aux->prox!=NULL){
        if(aux->prox->nota + aux->prox->dificuldade <prioridade){
          inserirApos(agenda_prioridade, nova_tarefa, aux);
          return;
        }
      aux = aux->prox;
    }
    inserirApos(agenda_prioridade, nova_tarefa, aux);
}

void atribuirNO(TipoApontador nova_tarefa, char nome[], char disciplina[], int dificuldade, int nota, Data data){
    strcpy(nova_tarefa->nome, nome);
    strcpy(nova_tarefa->disciplina, disciplina);
    nova_tarefa->dificuldade = dificuldade;
    nova_tarefa->nota = nota;
    nova_tarefa->data.dia = data.dia, nova_tarefa->data.mes = data.mes, nova_tarefa->data.ano = data.ano;
}
void inicializar_2(Agenda_Vetorial *agenda_vetorial){
  agenda_vetorial->tam=0;
}
void inserir(Agenda_Vetorial *agenda_vetorial, TipoApontador aux){
    if(agenda_vetorial->tam==maxTAM){
        printf("Tamanho limite atingido, favor liberar espaço\n");
        return ;
    }
    else{
      agenda_vetorial->Vet[agenda_vetorial->tam]=*aux;
    }
    agenda_vetorial->tam++;
}

void removerAgendaVetorial(Agenda_Vetorial *agenda_vetorial, char nome[]){
    for(int i=0; i<agenda_vetorial->tam; i++){
        if(strcmp(agenda_vetorial->Vet[i].nome, nome)==0){
          printf("Atividade %s removida da agenda\n", nome);
          for(int j=i; j<agenda_vetorial->tam-1; j++){
              agenda_vetorial->Vet[j]=agenda_vetorial->Vet[j+1];
          }
          agenda_vetorial->tam--;
          return;
        }
    }
    printf("A atividade %s não se encontra na agenda para ser removida\n", nome);
}

void selectionSort(Agenda_Vetorial *agenda_vetorial){
    int i, j, min, tam; 
    NO aux_2;
    tam=agenda_vetorial->tam;
    for (i = 0; i < agenda_vetorial->tam; i++) 
    {
        min = i; 
        for (j = i+1; j < agenda_vetorial->tam; j++){ 
            if (comparaDatas(agenda_vetorial->Vet[j].data, agenda_vetorial->Vet[min].data, agenda_vetorial, j, min)==1){
              min=j;
            }
        }
        aux_2 = agenda_vetorial->Vet[i];
        agenda_vetorial->Vet[i]=agenda_vetorial->Vet[min];
        agenda_vetorial->Vet[min] = aux_2;
    } 
}

int comparaDatas(Data d1, Data d2, Agenda_Vetorial *agenda_vetorial, int i, int j){
    if(d1.ano < d2.ano){
      return 1;
    }
    else if(d1.ano == d2.ano){
      if(d1.mes < d2.mes) return 1;
      else if(d1.mes == d2.mes){
        if(d1.dia < d2.dia){
          return 1;
        }
        else if(d1.dia==d2.dia){
          int prioridade1 = agenda_vetorial->Vet[i].nota + agenda_vetorial->Vet[i].dificuldade; 
          int prioridade2 = agenda_vetorial->Vet[j].nota + agenda_vetorial->Vet[j].dificuldade; 
          if(prioridade1>prioridade2) return 1;
          return 0;
        }
      }
      else return 0;
    }
    else return 0;
    return 0;
}

int buscaSequencial(Agenda_Vetorial *agenda_vetorial, char nome[]){
  int i;
  for(i=0; i<agenda_vetorial->tam; i++){
    if(strcmp(agenda_vetorial->Vet[i].nome, nome)==0){
      printf("Elemento encontrado na posição %d da lista de prioridades\n", i+1);
      break;
    }
  }
  return i;
}

int comparaDatasBuscaBinaria(Data d1, Data d2, Agenda_Vetorial *agenda_vetorial){
    if(d1.ano < d2.ano){
      return 1;
    }
    else if(d1.ano == d2.ano){
        if(d1.mes < d2.mes) return 1;
        else if(d1.mes == d2.mes){
            if(d1.dia <= d2.dia){
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

int buscaBinaria(Agenda_Vetorial *agenda_vetorial, Data x){ // vai pegar a posição da primeira atividade da data buscada
    int n = agenda_vetorial->tam;
    int l=0, r = n-1, mid, ans=-1;
    Data atual;
    while(l<=r){
        mid = (r+l)/2;
        atual = agenda_vetorial->Vet[mid].data;
        if(comparaDatasBuscaBinaria(x,atual, agenda_vetorial)){ 
            ans = mid;
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return ans;
}

void Merge(int ini, int meio, int fim, Agenda_Vetorial *agenda_vetorial){
    int i=ini, j = meio+1, k=0;
    Agenda_Vetorial aux;
    aux.tam=0;
    Data d1, d2;
    while(i<=meio && j<=fim){
        d1 = agenda_vetorial->Vet[i].data;
        d2 = agenda_vetorial->Vet[j].data;
        if(comparaDatas(d1, d2, agenda_vetorial, i, j)==1){
            aux.Vet[k++] = agenda_vetorial->Vet[i++];
            aux.tam++;
        }
        else {aux.tam++; aux.Vet[k++] = agenda_vetorial->Vet[j++];}
    }
    while(i<=meio){
        aux.Vet[k++] = agenda_vetorial->Vet[i++];
        aux.tam++;
    }
    while(j<=fim){
        aux.tam++;
        aux.Vet[k++] = agenda_vetorial->Vet[j++];
    }
    for(i=ini; i<=fim; i++){
        agenda_vetorial->Vet[i] = aux.Vet[i-ini];
    }
}

void MergeSort(int ini, int fim, Agenda_Vetorial *agenda_vetorial){
    if(ini<fim){
        int meio = (ini+fim)/2;
        MergeSort(ini, meio, agenda_vetorial);
        MergeSort(meio+1, fim, agenda_vetorial);
        Merge(ini, meio, fim, agenda_vetorial);
    }
} 

void imprimirAgendaVetorial(Agenda_Vetorial agenda_vetorial){
  if(agenda_vetorial.tam==0){
    printf("Parabens!!! Todas as atividades estão concluidas\n");
  }
  for(int i=0; i<agenda_vetorial.tam; i++){
    if(i==0) printf("-------------------Atividades da agenda-----------------\n");
    printf("Nome: %s\n", agenda_vetorial.Vet[i].nome);
    printf("Disciplina: %s\n", agenda_vetorial.Vet[i].disciplina);
    printf("Dificuldade: %d\n", agenda_vetorial.Vet[i].dificuldade);
    printf("Nota: %d\n", agenda_vetorial.Vet[i].nota);
    printf("Data de entrega: %02d/%02d/%02d\n", agenda_vetorial.Vet[i].data.dia, agenda_vetorial.Vet[i].data.mes, agenda_vetorial.Vet[i].data.ano);
    printf("--------------------------------------------------------\n");
  }
}

void mostrarAtividadesDia (Agenda_Vetorial agenda_vetorial, Data atual){
    int i,ok=0;
    if(agenda_vetorial.tam==0){
      printf("Parabens!!! Todas as atividades estão concluidas\n");
      return;
    }
    for(i=0; i<agenda_vetorial.tam; i++){
        if(agenda_vetorial.Vet[i].data.dia==atual.dia && agenda_vetorial.Vet[i].data.mes==atual.mes && agenda_vetorial.Vet[i].data.ano==atual.ano){
            if(ok==0){
                printf("-------------------Atividades do dia-------------------\n");
                ok=1;
            }
            printf("Nome: %s\n", agenda_vetorial.Vet[i].nome);
            printf("Disciplina: %s\n", agenda_vetorial.Vet[i].disciplina);
            printf("Dificuldade: %d\n", agenda_vetorial.Vet[i].dificuldade);
            printf("Nota: %d\n", agenda_vetorial.Vet[i].nota);
            printf("Data de entrega: %02d/%02d/%02d\n", agenda_vetorial.Vet[i].data.dia, agenda_vetorial.Vet[i].data.mes, agenda_vetorial.Vet[i].data.ano);
            printf("--------------------------------------------------------\n");
        }
        else break;
    }
    if(i==0){
        printf("Não há atividades para hoje\n");
    }
}

int removerAtrasadas(Agenda_Vetorial *agenda_vetorial, Agenda_Prioridade *agenda_prioridade, Data atual){
    int i=0,qtd=0;
    while(i<agenda_vetorial->tam){
        if(comparaDatasHoje(agenda_vetorial->Vet[i].data, atual)==1){
            removerAgendaPrioridade(agenda_prioridade, agenda_vetorial->Vet[i].nome);
            removerAgendaVetorial(agenda_vetorial, agenda_vetorial->Vet[i].nome);
            qtd++;
            i--;
        }
        i++;
    }
    if(qtd==0) return 0;
    return 1;      
}
int comparaDatasHoje(Data d1, Data d2){
    if(d1.ano < d2.ano)
      return 1;
      
    else if(d1.ano == d2.ano){
        if(d1.mes < d2.mes) return 1;
        
        else if(d1.mes == d2.mes){
            if(d1.dia < d2.dia) return 1;
            else if(d1.dia==d2.dia)return 2;
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

void imprimirAteData(Agenda_Vetorial agenda_vetorial, Data x){
    printf("-----Atividades até a Data %02d/%02d/%04d-------------------\n", x.dia, x.mes, x.ano);
    for(int i=0; i<agenda_vetorial.tam; i++){
        if(comparaDatasHoje(agenda_vetorial.Vet[i].data, x)>0){
            printf("Nome: %s\n", agenda_vetorial.Vet[i].nome);
            printf("Disciplina: %s\n", agenda_vetorial.Vet[i].disciplina);
            printf("Dificuldade: %d\n", agenda_vetorial.Vet[i].dificuldade);
            printf("Nota: %d\n", agenda_vetorial.Vet[i].nota);
            printf("Data de entrega: %02d/%02d/%04d\n", agenda_vetorial.Vet[i].data.dia, agenda_vetorial.Vet[i].data.mes, agenda_vetorial.Vet[i].data.ano);
            printf("--------------------------------------------------------\n");
        }
        else break;
    }
    printf("--------------------------------------------------------\n");
}


void mostrarProximaAtividade(Agenda_Prioridade agenda_prioridade, Agenda_Vetorial agenda_vetorial, Data x){
    if(agenda_vetorial.tam>0 && agenda_vetorial.Vet[0].data.dia==x.dia && agenda_vetorial.Vet[0].data.mes==x.mes && agenda_vetorial.Vet[0].data.ano == x.ano){
        printf("------------A proxíma atividade é----------------------\n");
        printf("Nome: %s\n", agenda_vetorial.Vet[0].nome);
        printf("Disciplina: %s\n", agenda_vetorial.Vet[0].disciplina);
        printf("Dificuldade: %d\n", agenda_vetorial.Vet[0].dificuldade);
        printf("Nota: %d\n", agenda_vetorial.Vet[0].nota);
        printf("Data de entrega: %02d/%02d/%04d\n", agenda_vetorial.Vet[0].data.dia, agenda_vetorial.Vet[0].data.mes, agenda_vetorial.Vet[0].data.ano);
        printf("--------------------------------------------------------\n");
    }
    else if(agenda_prioridade.inicio!=NULL){
        printf("------------A proxíma atividade é----------------------\n");
        printf("Nome: %s\n", agenda_prioridade.inicio->nome);
        printf("Disciplina: %s\n", agenda_prioridade.inicio->disciplina);
        printf("Dificuldade: %d\n", agenda_prioridade.inicio->dificuldade);
        printf("Nota: %d\n", agenda_prioridade.inicio->nota);
        printf("Data de entrega: %02d/%02d/%04d\n", agenda_prioridade.inicio->data.dia, agenda_prioridade.inicio->data.mes, agenda_prioridade.inicio->data.ano);
        printf("--------------------------------------------------------\n");
    }
    else printf("Todas atividades concluidas!!!\n");
}
int concluirAtividadesDia(Agenda_Vetorial *agenda_vetorial, Agenda_Prioridade *agenda_prioridade, Data x){
    int ans=0, tam, i=0;
    tam=agenda_vetorial->tam;
    while(i<agenda_vetorial->tam){
        if(agenda_vetorial->Vet[i].data.dia==x.dia && agenda_vetorial->Vet[i].data.mes==x.mes && agenda_vetorial->Vet[i].data.ano==x.ano){
            removerAgendaPrioridade(agenda_prioridade, agenda_vetorial->Vet[i].nome);
            removerAgendaVetorial(agenda_vetorial, agenda_vetorial->Vet[i].nome);
            ++ans;
            i--;
        }
        i++;
    }
    return ans;
}   

void concluirAtividadesDeUmDia(Agenda_Vetorial *agenda_vetorial,Agenda_Prioridade *agenda_prioridade, Data data){
    int y,cont=0, j;
    y = buscaBinaria(agenda_vetorial, data);
    if(y==-1 || agenda_vetorial->Vet[y].data.dia!=data.dia || agenda_vetorial->Vet[y].data.mes!=data.mes || agenda_vetorial->Vet[y].data.ano!=data.ano){
        printf("Não há atividades para esse dia\n");
        return;
    }
    for(int i=y; i<agenda_vetorial->tam; i++){
        if(agenda_vetorial->Vet[i].data.dia==data.dia && agenda_vetorial->Vet[i].data.mes==data.mes && agenda_vetorial->Vet[i].data.ano==data.ano){
            removerAgendaPrioridade(agenda_prioridade, agenda_vetorial->Vet[i].nome);
            removerAgendaVetorial(agenda_vetorial, agenda_vetorial->Vet[i].nome);  
            cont++, i--;
        }
    }
    printf("Parabens, você concluiu %d atividade(s)!!!\n", cont);
}

void concluirProximaAtividade(Agenda_Prioridade *agenda_prioridade, Agenda_Vetorial *agenda_vetorial, Data x){
    if(agenda_prioridade->tam==0){
        printf("Parabens!!! Todas as atividades estão concluidas\n");
        return;
    }
    if(agenda_vetorial->Vet[0].data.dia==x.dia && agenda_vetorial->Vet[0].data.mes==x.mes && agenda_vetorial->Vet[0].data.ano == x.ano){
        removerAgendaPrioridade(agenda_prioridade, agenda_vetorial->Vet[0].nome);
        removerAgendaVetorial(agenda_vetorial, agenda_vetorial->Vet[0].nome);
    }
    else{
        removerAgendaVetorial(agenda_vetorial, agenda_prioridade->inicio->nome);
        removerAgendaPrioridade(agenda_prioridade, agenda_prioridade->inicio->nome);
    }
}
void MostrarAtividadesDeUmDia(Agenda_Vetorial *agenda_vetorial, Data x){
    int res=buscaBinaria(agenda_vetorial, x), count=0;
    if(res==-1 || agenda_vetorial->Vet[res].data.dia!=x.dia || agenda_vetorial->Vet[res].data.mes!=x.mes || agenda_vetorial->Vet[res].data.ano!=x.ano){
        printf("Não há atividades para esse dia\n");
        return;
    }
    else{
        printf("-------------Ativades do dia----------------------------\n");
        for(int i=res; i<agenda_vetorial->tam; i++){
            if(agenda_vetorial->Vet[i].data.dia==x.dia && agenda_vetorial->Vet[i].data.mes==x.mes && agenda_vetorial->Vet[i].data.ano==x.ano){
                printf("Nome: %s\n", agenda_vetorial->Vet[i].nome);
                printf("Disciplina: %s\n", agenda_vetorial->Vet[i].disciplina);
                printf("Dificuldade: %d\n", agenda_vetorial->Vet[i].dificuldade);
                printf("Nota: %d\n", agenda_vetorial->Vet[i].nota);
                printf("--------------------------------------------------------\n");   
            }
        }
    }
}