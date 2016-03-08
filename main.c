/*
TITRE : main.c
AUTEUR : William DEREN
PROJET : Jeu du Plus ou Moins
DATE : 17/01/2015
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "screen.h"
#include "utility.h"

int Compteur = 0,nb_Max = 0;
int Compteur1 = 0, Compteur2 = 0;

int main ( int argc, char** argv )
{
    int nombreMystere = 0, nombreEntre = 0, Mode = 0;
    int nombreMystere1 = 0, nombreEntre1 = 0;
    int nombreMystere2 = 0, nombreEntre2 = 0;
    const int MIN = 1;

    int Quitter;

    do
    {
        /* affichage du haut de page */
        Title();

        Mode = getNbJoueurs();

        nb_Max = getDifficulte();

        switch (Mode)
        {
        case 1: /* 1 joueur */


            // Génération du nombre aléatoire

            srand(time(NULL));
            nombreMystere = (rand() % (nb_Max - MIN + 1)) + MIN;

            printf("Choissisez un nombre entre 1 et %d\n",nb_Max);

            /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */

            do
            {
                nombreEntre = testvaleur();

                /* ajout d'un compteur de coups */
                Compteur++;
                // On compare le nombre entré avec le nombre mystère

                if (nombreMystere > nombreEntre)
                {
                    printf("C'est plus !\n\n");
                }
                else if (nombreMystere < nombreEntre)
                {
                    printf("C'est moins !\n\n");
                }
                else
                {
                    Resultat(0);
                }


            } while (nombreEntre != nombreMystere);

            break;

        case 2: /* 2 joueurs */

            // joueur1
            nombreMystere1 = getNbMystere1(1);

            /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */
            /* on efface tout et on affiche le titre*/
            Title();
            /* le joueur 2 doit trouver le nombre mystere suivant le niveau de difficulté */
            printf("\n\nLe joueur 2 doit trouver le nombre mystere entre 1 et %d: \n",nb_Max);


            do
            {
                nombreEntre1 = testvaleur();

                /* ajout d'un compteur de coups */
                Compteur2++;
                // On compare le nombre entré avec le nombre mystère

                if (nombreMystere1 > nombreEntre1)
                {
                    printf("C'est plus !\n\n");
                }
                else if (nombreMystere1 < nombreEntre1)
                {
                    printf("C'est moins !\n\n");
                }
                else
                {
                    Resultat(2);
                }


            } while (nombreEntre1 != nombreMystere1);

            //joueur2
            nombreMystere2 = getNbMystere1(2);

            /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */
            /* on efface tout et on affiche le titre*/
            Title();
            /* le joueur 1 doit trouver le nombre mystere suivant le niveau de difficulté */
            printf("\n\nLe joueur 1 doit trouver le nombre mystere entre 1 et %d: \n",nb_Max);


            do
            {
                nombreEntre2 = testvaleur();

                /* ajout d'un compteur de coups */
                Compteur1++;
                // On compare le nombre entré avec le nombre mystère

                if (nombreMystere2 > nombreEntre2)
                {
                    printf("C'est plus !\n\n");
                }
                else if (nombreMystere2 < nombreEntre2)
                {
                    printf("C'est moins !\n\n");
                }
                else
                {
                    Resultat(1);
                }


            } while (nombreEntre2 != nombreMystere2);

            /* comparaisons des 2 compteurs pour trouver le vainqueur */
            if (Compteur1 < Compteur2)
            {
                printf("Le joueur 1 est le vainqueur et a trouve le chiffre mystere en seulement %d coups\n\n",Compteur1);
            }
            else if (Compteur2 < Compteur1)
            {
                printf("Le joueur 2 est le vainqueur et a trouve le chiffre mystere en seulement %d coups\n\n",Compteur2);
            }
            else
            {
                printf("Egalite entre les 2 joueurs avec %d coups pour le joueur 1 et %d coups pour le joueur 2\n\n",Compteur1,Compteur2);
            }

            getchar();

            break;

        default:
            break;

        }

        /* quiter ou recommencer le prog */
        Quitter = mnuQuit();

    } while (Quitter != 2);

    return 0;

}


int testvaleur()
{
    char ch_valeur[5] = "";
    int nb_valeur, ret;

    /* Tant que la chaine est invalide, elle ne comporte pas ce que
       l'on veut, on continue. */
    do
    {
        /*initialisation ret si hors gabarit */
        ret = 0;

        do
        {
            if (ret != 1)
            {
                // On demande le nombre
                printf("\n\nQuel est le nombre ? ");
            }

            fgets(ch_valeur, sizeof ch_valeur, stdin);

            /*On nettoie notre chaine et le buffer stdin*/
            Chaine_clean(ch_valeur);

            /*On convertie notre chaine en entier*/
            ret = sscanf(ch_valeur, "%d", &nb_valeur);

        } while( ret != 1);

    } while ((nb_valeur < 1) || (nb_valeur > nb_Max));

    return nb_valeur;
}

int getNbJoueurs()
{

    char ch_Joueurs[2] = "";
    int nb_joueurs, ret;

    /* Tant que la chaine est invalide, elle ne comporte pas ce que
       l'on veut, on continue. */

    /* On demande a l'utilisateur d'entrer le nombre de joueurs. */
    MenuNbJoueur();


    do
    {
        /*initialisation ret si le numéro de série est hors gabarit */
        ret = 0;

        do
        {
            if (ret != 1)
            {
                printf("Votre choix ? ");
            }

            fgets(ch_Joueurs, sizeof ch_Joueurs, stdin);

            /*On nettoie notre chaine et le buffer stdin*/
            Chaine_clean(ch_Joueurs);

            /*On convertie notre chaine en entier*/
            ret = sscanf(ch_Joueurs, "%d", &nb_joueurs);

        } while( ret != 1);

    } while ((nb_joueurs < 1) || (nb_joueurs > 2));

    return nb_joueurs;


}

int getDifficulte()
{

    char ch_Difficulte[2] = "";
    int nb_diff, ret, returnMax;

    /* Tant que la chaine est invalide, elle ne comporte pas ce que
       l'on veut, on continue. */

    /* On demande a l'utilisateur d'entrer le nombre de joueurs. */
    MenuDifficulte();


    do
    {
        /*initialisation ret si hors gabarit */
        ret = 0;

        do
        {
            if (ret != 1)
            {
                printf("Votre choix ? ");
            }

            fgets(ch_Difficulte, sizeof ch_Difficulte, stdin);

            /*On nettoie notre chaine et le buffer stdin*/
            Chaine_clean(ch_Difficulte);

            /*On convertie notre chaine en entier*/
            ret = sscanf(ch_Difficulte, "%d", &nb_diff);

        } while( ret != 1);

    } while ((nb_diff < 1) || (nb_diff > 3));

    switch (nb_diff)
    {

    case 1:
        returnMax = 100;
        break;

    case 2:
        returnMax = 1000;
        break;

    case 3:
        returnMax = 10000;
        break;

    default:
        returnMax = 100;
        break;

    }

    return returnMax;


}

int mnuQuit()
{

    char ch_quit[4] = "";
    int c, ret;

    /* on efface tout et on affiche le menu pour quitter */
    Title();

    printf("1 - Recommencer\n");
    printf("2 - Quitter\n");
    printf("\n\n");

    /*remise à zéro des compteurs*/
    Compteur = 0;
    Compteur1 = 0;
    Compteur2 = 0;

    do
    {
        /*initialisation ret si la valeur est hors gabarit */
        ret = 0;

        do
        {
            if (ret != 1)
            {
                printf("Votre choix ? ");
            }

            fgets(ch_quit, sizeof ch_quit, stdin);

            /*On nettoie notre chaine et le buffer stdin*/
            Chaine_clean(ch_quit);

            /*On convertie notre chaine en entier*/
            ret = sscanf(ch_quit, "%d", &c);

        } while( ret != 1);

    } while ((c < 1) || (c > 2));

    return c;

}

void Resultat(int joueur)
{
    switch (joueur)
    {
    case 0:
        printf ("\n\nBravo, vous avez trouve le nombre mystere en %d coups!!!\n\n",Compteur);
        printf("Appuyez sur enter pour continuer...\n");
        getchar();
        break;
    case 1:
        printf ("\n\nBravo, vous avez trouve le nombre mystere en %d coups!!!\n\n",Compteur1);
        printf("Appuyez sur enter pour continuer...\n");
        getchar();
        break;
    case 2:
        printf ("\n\nBravo, vous avez trouve le nombre mystere en %d coups!!!\n\n",Compteur2);
        printf("Appuyez sur enter pour continuer...\n");
        getchar();
        break;
    }

}

int getNbMystere1(int joueur)
{

    char ch_Mystere1[5] = "";
    int nb_Mystere1, ret;

    /* Tant que la chaine est invalide, elle ne comporte pas ce que
       l'on veut, on continue. */

    /* le joueur 1 choisi le nombre mystere suivant le niveau de difficulté */
    printf("\n\nLe joueur %d doit choisir le nombre mystere entre 1 et %d: \n",joueur,nb_Max);

    do
    {
        /*initialisation ret si hors gabarit */
        ret = 0;

        do
        {
            if (ret != 1)
            {
                printf("Votre choix ? ");
            }

            fgets(ch_Mystere1, sizeof ch_Mystere1, stdin);

            /*On nettoie notre chaine et le buffer stdin*/
            Chaine_clean(ch_Mystere1);

            /*On convertie notre chaine en entier*/
            ret = sscanf(ch_Mystere1, "%d", &nb_Mystere1);

        } while( ret != 1);

    } while ((nb_Mystere1 < 1) || (nb_Mystere1 > nb_Max));

    return nb_Mystere1;


}
