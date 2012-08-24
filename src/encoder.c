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

int encoder(unsigned int tab[16]) {
	int binaire[16];
	int taille=0;
	int i=0;
	int compteur=0;
	int a=2,b=2,c=2,d=2;
	int plus=0;
	
	//On recopi le tableau en mémoire
	while(tab[i] != 2) {
		binaire[i] = tab[i];
		i++;
	}
	
	taille = i;
	i=0;
	
	//On parcour le tableau et on remet dans tab. L'objectif est de detecter les chaines de quatre 1 ou plus et on leur ajoute un caractere
	while(i < taille) {	
		//Si on rencontre la chaine 1111 on ajoute un 1
		if((a == 0) && (b == c) && (c == d) && (d == binaire[i]) && (b == 1) && (plus == 0)) {
			plus = 1;
			tab[compteur] = 1;
			compteur++;
		}
		
		if((plus == 1) && (binaire[i] == '0')) {
			plus = 0;
		}
		
		tab[compteur] = binaire[i];
		a = b;
		b = c;
		c = d;
		d = binaire[i];
		
		i++;
		compteur++;
	}
	
	//si la fin  est:
	//0
	if(tab[compteur-1] == 0) {
		compteur--;
	}
	else {
		//01
		if(tab[compteur-2] == 0) {
			compteur -= 2;

		}
		else {
			//011
			if(tab[compteur-3] == 0) {
				compteur -= 3;
			}
			else {
				//0111
				if(tab[compteur-4] == 0) {
					compteur -= 4;
				}
			}
		}
	}
	
	return compteur;
}
