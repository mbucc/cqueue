DOCD=.

DOCCO=/usr/local/bin/docco

all: slist.html slistofslists.html

%.html: ../examples/%.c
	${DOCCO} -o ${DOCD} ../examples/$(basename $(notdir $@)).c

${DOCCO}: 
	sudo npm install -g docco

clean:
	rm -f *.html *.css

