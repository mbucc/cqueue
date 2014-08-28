# @since Tue Aug 26 20:36:01 EDT 2014
# @author Mark Bucciarelli <mkbucc@gmail.com>


all: samples docs

#---------------------------------------------------
#
#                                              Examples
#
#---------------------------------------------------

samples:
	(cd examples ; make)

#---------------------------------------------------
#
#                                        Documentation
#
#---------------------------------------------------

docs:
	(cd docco ; make)


#---------------------------------------------------
#
#                                                Other
#
#---------------------------------------------------

clean:
	(cd examples ; make clean)
	(cd docco ; make clean)

	



