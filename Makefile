test : test.c simulation.c
	gcc test.c simulation.c -o simulator
simulator: ${PROC}.c simulation.c
	gcc simulation.c ${PROC}.c -o simulator
