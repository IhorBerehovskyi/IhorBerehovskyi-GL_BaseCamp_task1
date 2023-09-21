SRC = client.cpp main.cpp
OUTPUT = server

ifdef _WIN32
OUTPUT = client.exe
client:
	if [ ! -f $(OUTPUT) ]; then touch $(OUTPUT); fi
	g++ $(SRC) -o $(OUTPUT)
else
client:
	if [ ! -f $(OUTPUT) ]; then touch $(OUTPUT); fi
	g++ $(SRC) -o $(OUTPUT)
endif