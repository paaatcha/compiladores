all:
	flex -i trab4.l
	bison -v -t trab4.y
	gcc -o trab4 trab4.tab.c Hash.c Lista.c primos.c Variavel.c Funcao.c MasterNode.c executar.c Programa.c Comando.c Expressao.c Terminal.c PilhaArv.c -lfl -lm
	rm *.tab.c
	pdflatex interpretador.tex
	rm *.log
	rm *.aux
	
clean:        
	rm trab4 trab4.output interpretador.pdf
