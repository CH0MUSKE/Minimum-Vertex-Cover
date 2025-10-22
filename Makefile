CC = gcc

INC_DIR = header
# Dossier contenant les fichiers headers
SRC_DIR = source
# Dossier contenant les fichiers sources
OBJ_DIR = objet
# Dossier contenant les fichiers objets 
EXE_DIR = exe
# Dossier contenant les éxecutables 

# CFLAGS  = -Wall -I. -g -Wextra -pedantic -Wno-unused-parameter
CFLAGS  = -Wall -I. -g -Wextra -Wno-unused-parameter
# -I permet de prendre en compte tout les fichiers qui sont contenus dans les
# sous-dossiers contenus après le -I, dans ce cas tout les sous-dossiers

FILES = operationGraph operationTableau mesureFonction branchBound
# L'ensemble des noms des fichiers intermédiaires 

SRCS = $(patsubst %, $(SRC_DIR)/%.c, $(FILES))
# fonction patsubst, une fonction remplaçant tout mot (suite de caractères contigus)
# qui correspond au premier paramètre par le second paramètre 
# qui est passé dans le troisième paramètre (peut changer plusieurs mots)

OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(FILES))

#SRCS = $(SRC_DIR)/fichier1.c $(SRC_DIR)/fichier2.c $(SRC_DIR)/fichier3.c
#OBJS = $(OBJ_DIR)/fichier1.o $(OBJ_DIR)/fichier2.o $(OBJ_DIR)/fichier3.o
# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to your rescue.

DEPS = $(INC_DIR)/split.h
# Note: The above will soon get unwieldy.
# You will soon want to use an automatic dependency generator.


all: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -c $< -o $@ -lm

testGraphe : $(OBJS) $(OBJ_DIR)/testGraphe.o 
	$(CC) $(CFLAGS) -o $(EXE_DIR)/$@ $^ -lm

testTableau : $(OBJS) $(OBJ_DIR)/testTableau.o 
	$(CC) $(CFLAGS) -o $(EXE_DIR)/$@ $^ -lm

testPerformance : $(OBJS) $(OBJ_DIR)/testPerformance.o 
	$(CC) $(CFLAGS) -o $(EXE_DIR)/$@ $^ -lm

testBranchBound : $(OBJS) $(OBJ_DIR)/testBranchBound.o 
	$(CC) $(CFLAGS) -o $(EXE_DIR)/$@ $^ -lm

stu : 
	echo $(OBJS)