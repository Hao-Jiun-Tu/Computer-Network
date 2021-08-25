CC = g++
CFLAGS = -Wall
DEF = PORT=1234
EXE = server client

server:
	@$(CC) $(CFLAGS) -D $(DEF) server.cpp -o server
	./server
client:
	@$(CC) $(CFLAGS) -D $(DEF) client.cpp -o client
	./client

.PHONY: clean
clean:
	@rm $(EXE)
