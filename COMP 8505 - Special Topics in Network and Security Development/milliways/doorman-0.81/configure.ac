
AC_PREREQ(2.59)
AC_INIT([doormand],[V0.81],[bward2@users.sourceforge.net])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([doormand.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_LIBOBJ_DIR([Replacement_fns])

AC_PREFIX_DEFAULT([/usr/local])

AC_LANG(C)

AC_PROG_GCC_TRADITIONAL
AC_C_CONST
AC_PROG_CC

AM_PROG_LEX
AC_FUNC_REALLOC


AC_PATH_PROG([LSOF], [lsof], [no],
             [/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin:/usr/local/sbin])
if test "$LSOF" == "no"; then
    echo -e "\a"
    echo "*** Utility 'lsof' is missing; doormand cannot function properly without it."
    echo "*** (Get lsof at: ftp://lsof.itap.purdue.edu/pub/tools/unix/lsof/lsof.tar.gz)"
    echo
fi

AC_CHECK_HEADERS([netinet/in_systm.h])
AC_CHECK_HEADERS([netinet/in.h])

AC_CHECK_HEADERS([netinet/tcp.h], [], [],
[#if NETINET_SYS_SOCKET_H
# include <sys/socket.h>
# endif
])

AC_CHECK_HEADERS([netinet/udp.h], [], [],
[#if NETINET_SYS_SOCKET_H
# include <sys/socket.h>
# endif
])

AC_CHECK_HEADERS([pcap.h])
AC_CHECK_HEADERS([pcap/pcap.h])
AC_CHECK_HEADERS([sys/cdefs.h])
AC_CHECK_HEADERS([sys/sockio.h])


# find MD5 library                       For the time being, force use     ***
#                                        of our 'Replacement_fns' md5 code ***
#
#AC_SEARCH_LIBS([MD5Init], [md5 crypt sasl inn],,
#    LDFLAGS=-L/usr/lib/news
#    AC_SEARCH_LIBS([MD5Update], inn,,
#        LDFLAGS=-L/usr/local/lib
#        AC_SEARCH_LIBS([MD5Final], [md5 crypt sasl inn])
#    )
#)

AC_CHECK_FUNC([MD5Init], ,  [AC_LIBOBJ([md5])])
AC_CHECK_FUNC([hmac_md5], , [AC_LIBOBJ([hmac_md5])])
AC_CHECK_FUNC([daemon], ,   [AC_LIBOBJ([daemon])])

AC_CHECK_FUNCS([strsignal])

AC_SEARCH_LIBS([socket], socket)
AC_SEARCH_LIBS([yywrap], [fl l])
AC_SEARCH_LIBS([gethostbyname], nsl)
AC_SEARCH_LIBS([pcap_open_live], pcap, ,
 [echo;echo -e "\a";
  echo '*** pcap library is missing; doormand will not build. ***'
  echo;echo])


AC_CONFIG_FILES([ Makefile ])
AC_OUTPUT

