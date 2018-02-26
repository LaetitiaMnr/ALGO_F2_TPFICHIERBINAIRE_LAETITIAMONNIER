#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//manipuler des fichiers.

typedef struct ddn
{
    int j;
    int m;
    int annee;
} ddn;

typedef struct cId
{
    int numCarte;
    char nom[20];
    char prenom[20];
    char sexe;
    ddn naissance;
    char ville[20];
} carteId;

//Prototypes
carteId infoId(FILE*);
void creationFichier(carteId, FILE*);
void lectureFichier(FILE*, carteId);

//BUT : Un programme permettant d'écrire dans un fichier binaire et lire ces données.
//ENTREE : Choix du menu.
//SORTIE : Création d'une nouvelle carte d'ID ou l'affichage du fichier ou bien on quitte le programme.
int main()
{
    int choix = 0, nb = 1;
    FILE* fCarteId = NULL;
    carteId infoCarteId;

    do{
        system("@cls||clear");
        printf("--- Bienvenue ---\n");
        printf("1. Ajouter une carte d'identit\x82\n");
        printf("2. Chercher une carte d'identit\x82\n");
        printf("3. Quitter\n");
        scanf("%d", &choix);

        switch (choix){
            case 1: system("@cls||clear");
                    infoId(fCarteId);
                    nb = 1;
                    break;

            case 2: system("@cls||clear");
                    lectureFichier(fCarteId, infoCarteId);
                    nb = 1;
                    break;

            case 3: system("@cls||clear");
                    printf("A bientot\n");
                    nb = 2;
                    break;
        }
    } while (nb == 1);

    return 0;
}

//BUT : Ecrit dans un fichier binaire.
void creationFichier(carteId infoCarteId, FILE* fCarteId)
{
    fCarteId = fopen ("listeCarteId.txt","ab");
    fwrite(&infoCarteId, sizeof(infoCarteId), 1,fCarteId);
    fclose (fCarteId);
}

//BUT : Renseignement du type structuré carteId puis appelle de la procédure creationFichier() afin d'écrire dans un fichier binaire.
//ENTREE : Les informations pour la carteId.
carteId infoId(FILE* fCarteId)
{
    carteId infoCarteId;

    printf("Votre num\x82ro de carte d'identit\x82 : ");
    scanf("%d", &infoCarteId.numCarte);

    printf("Entrez votre nom : ");
    scanf("%s", infoCarteId.nom);

    printf("Entrez votre prenom : ");
    scanf("%s", infoCarteId.prenom);

    do {
        printf("Sexe : ");
        fflush(stdin);
        infoCarteId.sexe = getc(stdin);
        infoCarteId.sexe = toupper(infoCarteId.sexe);
    } while((infoCarteId.sexe != 'F') && (infoCarteId.sexe != 'M'));

    printf("Saisissez votre date de naissance :\n");
    scanf("%d", &infoCarteId.naissance.j);
    scanf("%d", &infoCarteId.naissance.m);
    scanf("%d", &infoCarteId.naissance.annee);

    printf("Ville : ");
    scanf("%s", infoCarteId.ville);

    creationFichier(infoCarteId, fCarteId);

    return infoCarteId;
}

//BUT : Lis le fichier binaire.
//SORTIE : Affiche les données du fichier binaire à l'écran.
void lectureFichier(FILE* fCarteId, carteId infoCarteId )
{
    char contenu[100];
    int i = 0, resultat;

    fCarteId = fopen ("listeCarteId.txt","rb");
    if (fCarteId == NULL) {
        printf("Erreur !\n");
        system("pause");
    }
    else {
        do {
            resultat = fread(&infoCarteId, sizeof(infoCarteId), 1, fCarteId);
            for (i = 0; i < resultat; i++) {
                printf("Numero ID : %d", infoCarteId.numCarte);
                printf("\n");

                strcpy(contenu, infoCarteId.nom);
                printf("Nom : %s\n", contenu);

                strcpy(contenu, infoCarteId.prenom);
                printf("Prenom : %s\n", contenu);

                printf("Sexe : %c\n", infoCarteId.sexe);

                printf("Date de naissance : %d/", infoCarteId.naissance.j);
                printf("%d/", infoCarteId.naissance.m);
                printf("%d", infoCarteId.naissance.annee);
                printf("\n");

                strcpy(contenu, infoCarteId.ville);
                printf("Ville : %s\n", contenu);
                printf("\n");
            }
        } while (!feof(fCarteId));
        system("pause");
        fclose (fCarteId);
    }
}
