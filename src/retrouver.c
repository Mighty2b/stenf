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
#include "../inc/retrouverFichier.h"

int main(int argc,char **argv) {

	FILE *fichier_source;

	fichier_source = fopen(argv[1], "rb");
	
	if(fichier_source == NULL) {
		printf("Le fichier source n\'existe pas ou est vide\n");
	}
	else {
		retrouverFichier(argv[1],argv[2]);
	}
    return EXIT_SUCCESS;
}

