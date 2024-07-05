g++ -c ring_header.cpp -o ring_header.o
g++ -c ring_manager.cpp -o ring_manager.o
g++ -c test.cpp -o test.o

g++ ring_header.o ring_manager.o test.o -o test_program

echo Compilation and linking completed.