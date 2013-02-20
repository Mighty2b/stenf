/***
* This file is part of Stenf.
* 
* Stenf is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Stenf is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Stenf.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdio.h>
#include <stdlib.h>
#include "../inc/tools.h"
#include "../inc/cacher.h"

int main(int argc,char **argv) {
	unsigned long long *taille_source;//La taille du fichier à cacher
	unsigned long long *taille_secret;//La taille de du fichier secret
	unsigned long long taille2;//La taille necessaire pour cacher le fichier
	FILE *fichier_secret, *fichier_source;//La clé et la source
	
	unsigned int type=2;//Le décalage

	fichier_source = fopen(argv[1], "rb");
	fichier_secret = fopen(argv[2], "rb");
	
	if(fichier_source == NULL) {
		printf("Le fichier source n\'existe pas ou est vide\n");
	}
	else if(fichier_secret == NULL) {
		printf("Le fichier à cacher n\'existe pas ou est vide\n");
	}
	else if(argc == 3) {
		printf("Entrez le nom de votre nouveau fichier");
	}
	else {
		//On reserve la mémoire
		taille_source = malloc(sizeof(long long));
		taille_secret = malloc(sizeof(long long));
		
		//On se positionne à la fin des fichiers
		fseek(fichier_source, 0, SEEK_END);
		fseek(fichier_secret, 0, SEEK_END);
		
		//On récuperer la position de l'octet
		*taille_source = ftell(fichier_source);
		*taille_secret = ftell(fichier_secret)*8;

		//On calcul la taille minimale du fichier, la formule est 72+type*8*taillefichiersecret et on prend 20% de marge
		taille2 = (72+type*(*taille_secret)*1.2);
		
		fclose(fichier_source);
		fclose(fichier_secret);

		//Si on peut pas cacher le fichier à cause de la taille
		if((*taille_source) < taille2) {
			printf("Le fichier à cacher est trop volumineux.\n");
			printf("Il vous faut un fichier de minimum %lli octets\n\n", taille2);
		}
		else {
			//On cache le premier dans le 2nd
			cacherFichier(argv[1],argv[2],argv[3], type);
		}
	}
    return EXIT_SUCCESS;
}

void cacherFichier(char *source, char *secret, char *nouveau, unsigned int type) {

	FILE *fichier_destination, *fichier_source, *fichier_secret;
	unsigned int caractereActuel, caractereSecret;
	int i, j, fin;
	unsigned int ancien[16], binaire[16], maillonFin[16];
	//On ouvre les fichiers
	fichier_destination = fopen(nouveau, "wb+");
	fichier_source = fopen(source, "rb");

	//On copie les premiers octets correspondants au type mime
	for(i=0;i<8;i++) {
		caractereActuel = fgetc(fichier_source);
		fwrite (&caractereActuel, 1, 1, fichier_destination);
	}

	fichier_secret = fopen(secret, "rb");

	remplir(ancien);
	remplir(binaire);
	remplir(maillonFin);

	maillonFin[0] = 0;
	maillonFin[1] = 1;
	maillonFin[2] = 1;
	maillonFin[3] = 1;
	maillonFin[4] = 1;
	maillonFin[5] = 0;

	caractereSecret = fgetc(fichier_secret);

	do	{
		entiertobinaire(caractereSecret, binaire);

		//On concatene avec ce qu'il nous reste
		fusionTableau(binaire, ancien, 8);

		//On supprime ancien
		remplir(ancien);

		//On encode le binaire
		fin = encoder(binaire);

		//On écrit jusqu'au dernier 0
		for(i=0;i<fin;i++) {
			for(j=1;j<=type;j++)	{
				caractereActuel = fgetc(fichier_source);

				if(j == type-1) {
					caractereActuel = 0x00 + caractereActuel - caractereActuel%2 + binaire[i];
				}
				else {
					caractereActuel = 0x00 + caractereActuel;
				}

				fwrite (&caractereActuel, 1, 1, fichier_destination);
			}
		}

		//On enleve ce qu'on a écrit
		cleanTable(binaire, ancien, fin);

		//On lit le fichier secret et on le transforme en binaire
		caractereSecret = fgetc(fichier_secret);
	}
	while (caractereSecret != EOF);
	//On fusione ce qu'il reste avec le maillon de fin
	fusionTableau(maillonFin, ancien, 6);

	//On met les caracteres restant + le maillon de fin
	i = 0;
	while(maillonFin[i] != 2) {
		for(j=1;j<=type;j++)	{
			caractereActuel = fgetc(fichier_source);

			if(j == type-1) {
				caractereActuel = 0x00 + caractereActuel - caractereActuel%2 + maillonFin[i];
			}
			else {
				caractereActuel = 0x00 + caractereActuel;
			}

			fwrite (&caractereActuel, 1, 1, fichier_destination);
		}
		i++;
	}

	while ((caractereActuel = fgetc(fichier_source)) != EOF)	{
		fwrite (&caractereActuel, 1, 1, fichier_destination);
	}

	//On ferme les fichiers
	fclose(fichier_destination);
	fclose(fichier_source);
	fclose(fichier_secret);
}
