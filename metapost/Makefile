
all: mpsproof.pdf

mpsproof.pdf: ans-heck.mp
	mpost -tex=latex $<
	pdftex mpsproof *.mps

clean:
	$(RM) *.aux *.log *.tex *.mpx *.mps *.pdf *~