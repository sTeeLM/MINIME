GFXBOOT   = $(shell which gfxboot)
PRODUCT   = $(shell perl -ne 'print if s/^product=//' ../config)
HELPFILES = $(addsuffix .hlp, $(shell for i in * ; do [ -d $$i ] && echo $$i ; done))

HELPSRC   = main*
HELPNAVI  = navi
ENTITIES  = product='$(PRODUCT)' fkey_help=F1 fkey_lang=F2 fkey_video=F3 fkey_kernelopts=F4 fkey_reboot=F5

%.hlp: %
	$(GFXBOOT) --help-create $@ --define $(ENTITIES) --navi $</$(HELPNAVI).html $</$(HELPSRC).html || true

all: .ready

.ready:	$(HELPFILES)
	@touch .ready

clean:
	rm -f .ready *.hlp *~

