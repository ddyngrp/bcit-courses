## Process this file with automake to produce Makefile.in

# bin_SCRIPTS =
	      
sbin_PROGRAMS = doormand
bin_PROGRAMS  = knock


knock_SOURCES = knock.c utilities.c utilities.h

EXTRA_knock_SOURCES = Replacement_fns/md5.c\
		      Replacement_fns/hmac_md5.c\
		      Replacement_fns/daemon.c\
		      Replacement_fns/getopt.c

knock_DEPENDENCIES = @LIBOBJS@

knock_LDADD = $(LIBOBJS)



doormand_SOURCES = doormand.c utilities.c utilities.h lexer.l

EXTRA_doormand_SOURCES = Replacement_fns/md5.c\
			 Replacement_fns/hmac_md5.c\
			 Replacement_fns/daemon.c\
			 Replacement_fns/getopt.c

doormand_DEPENDENCIES = @LIBOBJS@

doormand_LDADD = $(LIBOBJS)

man1_MANS = knock.1
man5_MANS = knockcf.5 doormand.cf.5 guestlist.5
man8_MANS = doormand.8

cfgdir = $(sysconfdir)/doormand

install_sh = my-install-sh


cfg_DATA = doormand.cf.EXAMPLE\
	   guestlist.EXAMPLE\
	   iptables_add iptables_delete\
	   ipchains_add ipchains_delete\
	   ipf_add ipf_delete\
	   ipfw_add ipfw_delete\
	   pfctl_add pfctl_delete

AM_CFLAGS=-Wall -DCONFIG_DIR="\"$(cfgdir)\""

install-data-local:
	chmod 744 $(DESTDIR)$(cfgdir)/iptables_add
	chmod 744 $(DESTDIR)$(cfgdir)/iptables_delete
	chmod 744 $(DESTDIR)$(cfgdir)/ipchains_add
	chmod 744 $(DESTDIR)$(cfgdir)/ipchains_delete
	chmod 744 $(DESTDIR)$(cfgdir)/ipf_add
	chmod 744 $(DESTDIR)$(cfgdir)/ipf_delete
	chmod 744 $(DESTDIR)$(cfgdir)/ipfw_add
	chmod 744 $(DESTDIR)$(cfgdir)/ipfw_delete
	chmod 744 $(DESTDIR)$(cfgdir)/pfctl_add
	chmod 744 $(DESTDIR)$(cfgdir)/pfctl_delete
	chmod 600 $(DESTDIR)$(cfgdir)/guestlist.EXAMPLE
	chmod 644 $(DESTDIR)$(cfgdir)/doormand.cf.EXAMPLE

