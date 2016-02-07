all:
	gcc -g -o3 -Wall -Werror -o nsh nsh.c

clean:
	$(RM) $(TARGET)