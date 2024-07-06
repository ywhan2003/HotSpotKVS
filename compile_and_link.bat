g++ -c ring_header.cpp -o ring_header.o
g++ -c ring_manager.cpp -o ring_manager.o
g++ -c client_simulator.cpp -o client_simulator.o
g++ -c client.cpp -o client.o

g++ ring_header.o ring_manager.o client_simulator.o client.o -o client

echo Compilation and linking completed.