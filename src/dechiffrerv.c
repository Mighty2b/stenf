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
#include <pthread.h>
#include "../inc/chiffrervFichier.h"

int main(int argc,char **argv) {
	unsigned long long *taille_source;//La taille du fichier à cacher
	unsigned long long *taille_secret;//La taille de du fichier secret
	FILE *fichier_secret, *fichier_source;//La clé et la source

	fichier_source = fopen(argv[1], "rb");
	fichier_secret = fopen(argv[2], "rb");
	
	if(fichier_source == NULL) {
		printf("Le fichier chiffré n\'existe pas ou est vide\n");
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
		*taille_secret = ftell(fichier_secret);

		fclose(fichier_source);
		fclose(fichier_secret);

		//Si on peut pas cacher le fichier à cause de la taille
		if((*taille_source) > *taille_secret) {
			printf("Le fichier clé est trop petit");
		}
		else {
			chiffrervFichier(argv[1],argv[2],argv[3]);
		}
	}
    return EXIT_SUCCESS;
}

