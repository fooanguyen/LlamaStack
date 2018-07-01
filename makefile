all: driver1.o Llama.o LlamaNode.o
	g++ -ansi -Wall driver1.o Llama.o LlamaNode.o -o output.out

driver1.o: driver1.cpp 
	g++ -ansi -Wall -c driver1.cpp

Llama.o: Llama.cpp 
	g++ -ansi -Wall -c Llama.cpp

LlamaNode.o: LlamaNode.cpp 
	g++ -ansi -Wall -c LlamaNode.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~*.h.gch *#

val:
	valgrind ./output.out

run:
	./output.out

