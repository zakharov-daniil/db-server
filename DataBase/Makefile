all: generator.o fullbase.o classbase.o server.o
	g++ ZDV-207-main.cpp generator.o fullbase.o classbase.o server.o -o server
	g++ ZDV-207-client-main.cpp -o
	
generator.o: ZDV-207-generator.cpp
	g++ -c ZDV-207-generator.cpp -o generator.o
	
fullbase.o: ZDV-207-FullBase.cpp
	g++ -c ZDV-207-FullBase.cpp -o fullbase.o
	
classbase.o: ZDV-207-classbase.cpp
	g++ -c ZDV-207-classbase.cpp -o classbase.o
	
server.o: ZDV-207-server.cpp
	g++ -c ZDV-207-server.cpp -o server.o


