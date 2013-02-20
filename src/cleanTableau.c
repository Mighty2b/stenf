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

void cleanTableau(unsigned int binaire[16], unsigned int ancien[16], int fin) {
	int i, j=0;
	
	for (i=0;i<fin;i++) {
		binaire[i] = 2;
	}
	
	while(binaire[i] != 2) {
		ancien[j] = binaire[i];
		binaire[i] = 2;
		i++;
		j++;
	}
}
