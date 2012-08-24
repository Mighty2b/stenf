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

#include "../inc/puis.h"

void retrouverFichier(char *source, char *nouveau) {
	FILE *fichier_nouveau, *fichier_source;
	unsigned int type=2;//Le décalage
	unsigned int i, j=0, k, caractereActuel;
	unsigned int total;
	unsigned int a=2, b=2, c=2, d=2, e=2, f=2;//Detection de fin
	int fin = 0;
	
	//On ouvre les fichiers
	fichier_nouveau = fopen(nouveau, "wb+");
	fichier_source = fopen(source, "rb");
	
	//On saute l'entête
	for(i=0;i<8;i++) {
		fgetc(fichier_source);
	}
	
	while(1)	{	
		for(k=1;k<=type;k++)	{
			caractereActuel = fgetc(fichier_source);
			
			if(caractereActuel == EOF)	{
				fin = 1;
				break;
			}
			
			if(k == type-1) {									
					a = b;
					b = c;
					c = d;
					d = e;
					e = f;
					f = (caractereActuel%2);
				
				total += ((caractereActuel%2)*puis(2,(j%8)));
				j++;
				
				if((a == 0) && (b == 1) && (b == c) && (c == d) && (d == e)) {
					if(a == f) {
						fin = 1;
						break;
					}
					else {//On vire le caractere de control
						j--;
						total -= puis(2,(j%8));
					}
				}
			}
		}
	
		if(fin == 1) {
			break;
		}
		
		if(j%8 == 0) {
			//On écrit le fichier
			fwrite (&total, 1, 1, fichier_nouveau);
			total = 0;
		}
	}
}

