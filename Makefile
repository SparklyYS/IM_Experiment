exe=main

OBJS= 	src/main.o	

DEPS= 	src/graph.h	

%.o: %.cpp ${DEPS}
	g++ -c $< -o $@

${exe}: ${OBJS}
	g++ ${OBJS} -o ${exe}

clean: 
	rm -rf src/*.o src/${exe}
