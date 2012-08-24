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

cacher: cacher.o cacherFichier.o remplir.o entiertobinaire.o fusionTableau.o puis.o encoder.o cleanTableau.o
	$(CC) -o bin/cacher cacher.o cacherFichier.o remplir.o entiertobinaire.o fusionTableau.o puis.o encoder.o cleanTableau.o

retrouver: retrouver.o retrouverFichier.o puis.o
	$(CC) -o bin/retrouver retrouver.o retrouverFichier.o puis.o

chiffrerv: chiffrerv.o chiffrervFichier.o entiertobinaire.o puis.o
	$(CC) -o bin/chiffrerv chiffrerv.o chiffrervFichier.o entiertobinaire.o puis.o

dechiffrerv: dechiffrerv.o chiffrervFichier.o entiertobinaire.o puis.o
	$(CC) -o bin/dechiffrerv dechiffrerv.o chiffrervFichier.o entiertobinaire.o puis.o

# Compilation des modules 
# Cacher les données
cacher.o: src/cacher.c
	$(CC) -c src/cacher.c

cacherFichier.o: src/cacherFichier.c
	$(CC) -c src/cacherFichier.c

remplir.o: src/remplir.c
	$(CC) -c src/remplir.c

entiertobinaire.o: src/entiertobinaire.c
	$(CC) -c src/entiertobinaire.c

fusionTableau.o: src/fusionTableau.c
	$(CC) -c src/fusionTableau.c

encoder.o: src/encoder.c
	$(CC) -c src/encoder.c

cleanTableau.o: src/cleanTableau.c
	$(CC) -c src/cleanTableau.c

puis.o: src/puis.c
	$(CC) -c src/puis.c

# Retrouver les données
retrouver.o: src/retrouver.c
	$(CC) -c src/retrouver.c

retrouverFichier.o: src/retrouverFichier.c
	$(CC) -c src/retrouverFichier.c

# Chiffrer avec la méthode de Vernam
chiffrerv.o: src/chiffrerv.c
	$(CC) -c src/chiffrerv.c

chiffrervFichier.o: src/chiffrervFichier.c
	$(CC) -c src/chiffrervFichier.c

# Dechiffrer avec la méthode de Vernam
dechiffrerv.o: src/dechiffrerv.c
	$(CC) -c src/dechiffrerv.c

# pour faire le ménage 
clean:
	rm -f *~ *.o bin/cacher bin/retrouver bin/chiffrerv bin/dechiffrerv
