FILE = main_referat

pdf: $(FILE).pdf
	evince $(FILE).pdf &

cleanall:
	rm -f *.dvi *.aux *.log  *.out *.bbl *.blg *.toc *.ps $(FILE).pdf

clean:
	rm -f $(FILE).dvi $(FILE).aux $(FILE).log 

cleanpdf:
	rm $(FILE).pdf 


$(FILE).dvi: $(FILE).tex 
	latex $(FILE)
	latex $(FILE)
	bibtex $(FILE)
	latex $(FILE) 

$(FILE).pdf: $(FILE).dvi $(FILE).aux
	#dvips $(FILE).dvi -t a4 -o $(FILE).ps
	dvips -t a4  -G0 $(FILE).dvi -o $(FILE).ps
	#dvips -Ppdf -D1200 main_referat
	ps2pdf -sPAPERSIZE=a4 -dMaxSubsetPct=100 -dCompatibilityLevel=1.2 -dSubsetFonts=true -dEmbedAllFonts=true $(FILE).ps

.KEEP_STATE:
