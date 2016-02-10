all:
	gcc -g -o3 -Wall -o nsh nsh.c

clean:
	$(RM) $(TARGET)