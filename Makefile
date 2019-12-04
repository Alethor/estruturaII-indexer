all:
	@gcc indexer.c -o indexer
	@echo "compilando..."
clean:
	rm -rf *.o
	rm -rf indexer
