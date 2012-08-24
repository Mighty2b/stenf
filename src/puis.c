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

unsigned int puis(unsigned int a, unsigned int b) {
	unsigned long resultat;
	unsigned int i;
	
	if(b > 0) {
		resultat = a;

		for(i=1;i<b;i++) {
			resultat=resultat*a;	
		}
	}
	else {
		resultat=1;
	}
	
	return resultat;
}
