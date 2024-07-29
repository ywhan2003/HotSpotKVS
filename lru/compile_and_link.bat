g++ -c key_value_store.cpp -o key_value_store.o
g++ -c client_simulator.cpp -o client_simulator.o
g++ -c client.cpp -o client.o

g++ key_value_store.o client_simulator.o client.o -o client

echo Compilation and linking completed.