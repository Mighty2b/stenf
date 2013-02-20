###
# This file is part of Stenf.
# 
# Stenf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Stenf is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Stenf.  If not, see <http://www.gnu.org/licenses/>.
###

#Makefile pour la construction du programme
CC=gcc -Wall

# quand on tape "make" sans paramètre 
all: cacher retrouver chiffrerv dechiffrerv

complete: clean cacher retrouver chiffrerv dechiffrerv

# Compilation des programmes principaux

cacher: cacher.o tools.o
	$(CC) -o bin/cacher cacher.o tools.o

retrouver: retrouver.o tools.o
	$(CC) -o bin/retrouver retrouver.o tools.o

chiffrerv: chiffrerv.o stenf.o tools.o
	$(CC) -o bin/chiffrerv chiffrerv.o stenf.o tools.o

dechiffrerv: dechiffrerv.o stenf.o tools.o
	$(CC) -o bin/dechiffrerv dechiffrerv.o stenf.o tools.o

# Compilation des outils 
stenf.o: src/stenf.c
	$(CC) -c src/stenf.c
	
tools.o: src/tools.c
	$(CC) -c src/tools.c
	
# Cacher les données
cacher.o: src/cacher.c
	$(CC) -c src/cacher.c
	
# Retrouver les données
retrouver.o: src/retrouver.c
	$(CC) -c src/retrouver.c

# Chiffrer avec la méthode de Vernam
chiffrerv.o: src/chiffrerv.c
	$(CC) -c src/chiffrerv.c

# Dechiffrer avec la méthode de Vernam
dechiffrerv.o: src/dechiffrerv.c
	$(CC) -c src/dechiffrerv.c

# pour faire le ménage 
clean:
	rm -f *~ *.o bin/cacher bin/retrouver bin/chiffrerv bin/dechiffrerv
