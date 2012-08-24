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
#include "../inc/entiertobinaire.h"
#include "../inc/puis.h"

void chiffrervFichier(char *source, char *secret, char *nouveau) {

	FILE *fichier_destination, *fichier_source, *fichier_secret;
	unsigned int caractereBase, caractereSecret;
	unsigned int ancien[16], binaire[16];
	int i;
	unsigned int total;
	
	//On ouvre les fichiers
	fichier_destination = fopen(nouveau, "wb+");
	fichier_source = fopen(source, "rb");
	fichier_secret = fopen(secret, "rb");
	
	caractereBase		= fgetc(fichier_source);
	caractereSecret	= fgetc(fichier_secret);

	do	{
		total = 0;
		entiertobinaire(caractereBase, ancien);
		entiertobinaire(caractereSecret, binaire);
		
		//On fait un XOR et on reconverti à la volée
		for(i=7;i>=0;i--) {
			total += ((ancien[i]^binaire[i])*puis(2,i));
		}
		
		//On écrit
		fwrite (&total, 1, 1, fichier_destination);
		
		//On lit le fichier secret et on le transforme en binaire
		caractereBase		= fgetc(fichier_source);
		caractereSecret	= fgetc(fichier_secret);
	}
	while (caractereSecret != EOF);

	//On ferme les fichiers
	fclose(fichier_destination);
	fclose(fichier_source);
	fclose(fichier_secret);
}
