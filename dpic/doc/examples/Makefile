nooption:
	cp sources/diag1.pic diag.pic
	cp sources/test1.tex tst.tex
	dpic diag.pic > diag.tex
#	latex tst
#	dvips -Ppdf tst.dvi

all: nooption epic pstricks pgf pdf mfpic psfrag postscript overlay metapost \
  xfig svg

epic:
	cp sources/diag2.pic diag.pic
	cp sources/test2.tex tst.tex
	dpic -t diag.pic > diag.tex
	latex tst
	dvips -Ppdf tst.dvi

pstricks:
	cp sources/diag1.pic diag.pic
	cp sources/test3.tex tst.tex
	dpic -p diag.pic > diag.tex
	latex tst
	dvips -Ppdf tst.dvi

pgf:
	cp sources/diag1.pic diag.pic
	cp sources/test9.tex tst.tex
	dpic -g diag.pic > diag.tex
	latex tst
	dvips -Ppdf tst.dvi

pdf:
	cp sources/diag1.pic diag.pic
	cp sources/test9.tex tst.tex
	dpic -g diag.pic > diag.tex
	pdflatex tst

mfpic:
	cp sources/diag1.pic diag.pic
	cp sources/test4.tex tst.tex
	dpic -m diag.pic > diag.tex
	latex tst
	mf tst-mfpic
	latex tst
	dvips tst.dvi

psfrag:
	cp sources/diag1.pic diag.pic
	cp sources/test5.tex tst.tex
	dpic -f diag.pic > diag.eps
	latex tst
	dvips -Ppdf tst

postscript:
	cp sources/diag6.pic diag.pic
	cp sources/test6.tex tst.tex
	dpic -r diag.pic > diag.eps
	latex tst
	dvips -Ppdf tst

svg:
	cp sources/diag6.pic diag.pic
	cp sources/test6.tex tst.tex
	dpic -v diag.pic > tst.svg

overlay:
	dpic -r sources/diagA.pic > diag.eps
	dpic -p sources/diagB.pic > diag.tex
	cp sources/test7.tex tst.tex
	latex tst
	dvips -Ppdf tst.dvi

metapost:
	cp sources/diag8.pic diag.pic
	cp sources/test8.tex tst.tex
	dpic -s diag.pic > diag.mp
	mpost --tex=latex diag.mp
	latex tst
	dvips -Ppdf tst

xfig:
	cp sources/diag9.pic diag.pic
	dpic -x diag.pic > diag.fig

clean:
	rm -f *.ps *.eps *.dvi *.log *.mp *.1 mpxerr* *pk *gf *.mpx *.dim *.mf
	rm -f *.tfm *.aux *.pfg tst.tex diag.pic diag.tex *.trace *.fig *.pdf *.svg
