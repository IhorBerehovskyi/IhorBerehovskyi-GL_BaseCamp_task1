SRC = server.cpp main.cpp
OUTPUT = server

ifdef _WIN32
OUTPUT = server.exe
server:
	if [ ! -f $(OUTPUT) ]; then touch $(OUTPUT); fi
	g++ $(SRC) -o $(OUTPUT)
else
server:
	if [ ! -f $(OUTPUT) ]; then touch $(OUTPUT); fi
	g++ $(SRC) -o $(OUTPUT)
endif
