SHELL = /bin/sh

LIB_DIR = /home/wangzw/Downloads/doulinklistlib/lib/
BIN_DIR = /home/wangzw/Downloads/doulinklistlib/bin/
OBJECT_DIR = /home/wangzw/Downloads/doulinklistlib/obj/
APP_DIR = /home/wangzw/Downloads/doulinklistlib/

$(shell mkdir -p ${LIB_DIR})
$(shell mkdir -p ${BIN_DIR})
$(shell mkdir -p ${OBJECT_DIR})


RM = rm -fr
CC = gcc
AR = ar rc


SRC_OBJECT = $(APP_DIR)gdllib.c $(APP_DIR)demo.c 
H_OBJECT = $(APP_DIR)gdllib.h
OBJECT = gdllib.o
DY_SRC_OBJECT = $(APP_DIR)demo.c
DY_OBJECT = demo.o
LIB_OBJECT = libdoull.a
BIN_OBJECT = demo


libdoull.a : gdllib.o
	$(AR) libdoull.a gdllib.o
	mv libdoull.a $(LIB_DIR)

gdllib.o : $(SRC_OBJECT) $(H_OBJECT)
	$(CC) -c $(SRC_OBJECT)

$(BIN_OBJECT) : $(DY_OBJECT) $(OBJECT)
	$(CC) -o $(BIN_OBJECT) $(OBJECT_DIR)$(DY_OBJECT) $(LIB_DIR)$(LIB_OBJECT)
	mv $(BIN_OBJECT) $(BIN_DIR)

$(DY_OBJECT) : $(DY_SRC_OBJECT)
	$(CC) -c $(DY_SRC_OBJECT) -o $(DY_OBJECT)
	mv $(OBJECT) $(DY_OBJECT) $(OBJECT_DIR)

clean :
	$(RM) $(LIB_DIR) $(BIN_DIR) $(OBJECT_DIR) $(OBJECT) $(DY_OBJECT)
