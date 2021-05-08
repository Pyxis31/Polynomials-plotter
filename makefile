############################
# Définition des variables #
############################

# Chemins d'installation
DIR_MGW = C:/MinGW/
DIR_GTK = C:/LibC/GTK+

# Répertoires pour trouver les fichiers .h de la bibliothèque
INCLUDES =	-I$(DIR_GTK)/include/gtk-2.0 \
			-I$(DIR_GTK)/include/glib-2.0 \
			-I$(DIR_GTK)/lib/glib-2.0/include \
			-I$(DIR_GTK)/include/cairo \
			-I$(DIR_GTK)/include/pango-1.0 \
			-I$(DIR_GTK)/lib/gtk-2.0/include \
			-I$(DIR_GTK)/include/gdk-pixbuf-2.0 \
			-I$(DIR_GTK)/include \
			-I$(DIR_GTK)/include/freetype2 \
			-I$(DIR_GTK)/include/libpng14 \
			-I$(DIR_GTK)/include/atk-1.0
	
# Répertoires pour trouver les fichiers .lib de la bibliothèque
LIBS =	-L$(DIR_GTK)/lib \
		-lglib-2.0 \
		-lgio-2.0 \
		-lcairo \
		-latk-1.0 \
		-lgdk-win32-2.0 \
		-lgdk_pixbuf-2.0 \
		-lgthread-2.0 \
		-lgtk-win32-2.0 \
		-lgdi32 \
		-lpango-1.0 \
		-lpangocairo-1.0 \
		-lpangowin32-1.0 \
		-lintl \
		-lgobject-2.0 \
		-lgmodule-2.0

########################################
# Définition des règles de compilation #
########################################

# Compilateur, options de compilation et options de construction
CC=gcc
CFLAGS=-g -mwindows -c -Wall -mms-bitfields
LDFLAGS=-mwindows -Wall -mms-bitfields

# Noms de l'exécutable et des fichiers sources
EXEC=TemplateGTK.exe
SRC=main.c poly.c audio.c

# Noms des fichiers objets (fichiers sources avec l'extension .c remplacée par .o)
OBJ=$(SRC:.c=.o)

# Edition de lien : construction de l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
		$(CC) $(LDFLAGS) $(OBJ) ressources.o $(LIBS) -o $(EXEC)

# Compilation : génération des fichiers objets ".o" à partir des fichiers sources ".c" :
audio.o: audio.c
		$(CC) $(CFLAGS) $(INCLUDES) audio.c
poly.o: poly.c
		$(CC) $(CFLAGS) $(INCLUDES) poly.c
divers.o: divers.c
		$(CC) $(CFLAGS) $(INCLUDES) divers.c	
main.o: main.c
		$(CC) $(CFLAGS) $(INCLUDES) main.c

