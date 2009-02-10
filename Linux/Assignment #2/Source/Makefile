# Makefile for Assignment #2 - Message Queue File Transfer
#
# Author: Steffen L. Norgren
#

SINGLE_CLIENT=single-client
MULTI_CLIENT=multi-client

SUBDIRS=${SINGLE_CLIENT} ${MULTI_CLIENT}

# Default Target

all: 
	@echo
	@echo "#######################################"
	@echo "### BUILDING ALL TARGETS ###"
	@echo "#######################################"
	@echo
	for i in ${SUBDIRS} ; do \
		( cd $$i ; make ) ; \
	done

# Rules to build individual targets

single-client:
	@cd ${SINGLE_CLIENT} ; make

multi-client:
	@cd ${MULTI_CLIENT} ; make

clean:
	rm -f *_*
	for i in ${SUBDIRS} ; do \
		( cd $$i ; make clean ) ; \
	done

install:
	for i in $(SUBDIRS) ; do \
		(cd $$i ; make install ); \
	done
