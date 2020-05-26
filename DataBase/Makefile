all: generator.o fullbase.o classbase.o server.o
	g++ ZDV-207-main.cpp generator.o fullbase.o classbase.o server.o -o server -std=c++11 -lpthread
	g++ ZDV-207-client-main1.cpp -o client -std=c++11 -lpthread
	
generator.o: ZDV-207-generator.cpp
	g++ -c ZDV-207-generator.cpp -o generator.o -std=c++11
	
fullbase.o: ZDV-207-FullBase.cpp
	g++ -c ZDV-207-FullBase.cpp -o fullbase.o -std=c++11
	
classbase.o: ZDV-207-classbase.cpp
	g++ -c ZDV-207-classbase.cpp -o classbase.o -std=c++11
	
server.o: ZDV-207-server.cpp
	g++ -c ZDV-207-server.cpp -o server.o -std=c++11

