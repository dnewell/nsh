P=nsh
OBJECTS=
CFLAGS= -g -o3 -Wall -Werror
LDLIBS=
CC=c99
TARGET=$(P)

all:
	(TARGET): $(OBJECTS)

clean:
	$(RM) $(TARGET)