SUBDIR=	module server

load unload	: _SUBDIR

all			: doc-doxygen

doc-doxygen	:
	${SH} ./doxy.sh

clean		:
	rm -rf doxygen.errors doc/*

.include <bsd.subdir.mk>
