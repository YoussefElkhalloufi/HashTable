#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Eleve Eleve;
struct Eleve{
    char *nom;
    Eleve* suivant;
};

#define taille 10
Eleve* tableau[10];

void initialize(){
    for(int i=0; i<taille; i++){
        tableau[i]= NULL;
    }
}

int hacher(char *nom){
    int nomHacher = 0;

    for(int i = 0; nom[i]!= '\0'; i++){
        nomHacher += nom[i];
    }

    nomHacher %= taille;
    return nomHacher;
}


void inserer(char *nom){
    Eleve *eleve = malloc(sizeof(Eleve));
    eleve->nom = nom;
    eleve->suivant = NULL;

    int index = hacher(nom);
    if(tableau[index] == NULL){//La case est vide
        tableau[index] = eleve;
    }else{//La case est rempli -> CHAINAGE
        Eleve *tmp = tableau[index];
        while(tmp->suivant != NULL){
            tmp = tmp->suivant;
        }
        tmp->suivant = eleve;
    }
}



void supprimer(char *nom){
    int index = hacher(nom);
    Eleve *tmp = tableau[index];
    Eleve *precedent = NULL;
    while(tmp != NULL){
        if(strcmp(nom, tmp->nom) == 0) break;
        else {
            precedent = tmp;
            tmp = tmp->suivant;
        }
    }
    if(tmp == NULL){
        printf("tmp est null\n");
        return ;
    }
    if(precedent == NULL) {
        //supprimer la tete de la liste
        tableau[index] = tmp->suivant;
    }else{//supprimer un element au millieu
        precedent->suivant = tmp->suivant;
    }

    free(tmp);
}

void afficherTableau(){
    for(int i = 0; i<taille; i++){
        if(tableau[i] == NULL){
            printf("\t%d\t-----\n", i);
        }else{
            printf("\t%d\t", i);
            Eleve *tmp = tableau[i];
            while(tmp != NULL){
                printf("%s  -> ", tmp->nom);
                tmp = tmp->suivant;
            }
            printf(" NULL\n");

        }
    }
}

bool find(char *nom){
    int index = hacher(nom);
    Eleve *tmp = tableau[index];
    while(tmp != NULL){
        if(strcmp(nom, tmp->nom) == 0) return true;
        tmp = tmp->suivant;
    }
    return false;

}


int main()
{

    printf("Teste de la fonction de hachage :\n");
        printf("\tYoussef  ->  %d\n", hacher("Youssef"));
        printf("\tKhalil   ->  %d\n", hacher("Khalil"));
        printf("\tZakaria  ->  %d\n", hacher("Zakaria"));
        printf("\tSamira   ->  %d\n", hacher("Samira"));
        printf("\tTrevor   ->  %d\n", hacher("Trevor"));
        printf("\tMichael  ->  %d\n", hacher("Michael"));
        printf("\tKarima   ->  %d\n", hacher("Karima"));
        printf("\tRosemary ->  %d\n", hacher("Rosemary"));



    printf("\nTableau initial des eleves :\n");
    afficherTableau();

    printf("\nInsertion des eleves au tableau:");
    inserer("Youssef");
    inserer("Khalil");
    inserer("Samira");
    inserer("Zakaria");
    inserer("Trevor");
    inserer("Michael");
    inserer("Karima");
    inserer("Rosemary");


    printf("\nAffichage du tableau apres insertion :\n");
    afficherTableau();

    printf("\n\nSuppression de 'Zakaria' ");
    supprimer("Zakaria");
    printf("\nAffichae apres suppression de 'Zakaria'\n");
    afficherTableau();

    printf("\nVeuillez saisir un nom : ");
    char nom[30];
    scanf("%s", &nom);
    if(find(nom)== true) printf("L'evleve existe");
    else printf("L'eleve n'existe pas");


    return 0;
}
