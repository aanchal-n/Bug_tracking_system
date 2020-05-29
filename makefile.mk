Output: frontend.o backend_1.o
	gcc frontend.o backend_1.o 
frontend.o: frontend.c backend.h
	gcc -c frontend.c
backend_1.o: backend_1.c backend.h
	gcc -c backend_1.c