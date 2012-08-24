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

void fusionTableau(unsigned int nouveau[16], unsigned int ancien[16], int taille) {
	int i,j;
	unsigned binaire[8];
	
	//On sauvegarde le nouveau
	for(i=0;i<taille;i++) {
			binaire[i] = nouveau[i];
	}
	
	i = 0;
	//On recopi l'ancien
	while(ancien[i] != 2) {
		nouveau[i] = ancien[i];
		i++;
	}
	
	//On remet le nouveau
	for(j=0;j<taille;j++) {
			nouveau[i] = binaire[j];
			i++;
	}
	nouveau[i] = 2;
}
