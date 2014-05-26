ODIR = ./TrabalhoEDPos/TrabalhoEDPos
IDIR = ./TrabalhoEDPos/TrabalhoEDPos

CC = gcc
CFLAGS=-I$(IDIR)


_DEPS = graph.h kruskal.h dijkstra.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph.o kruskal.o dijkstra.o TrabalhoEDPos.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(ODIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graph: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 