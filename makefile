CC=gcc
MKDIR=mkdir -p
RM=rm -rf
INSTALL=install

INCDIR=include
SRCDIR=src
OUTDIR=out

CFLAGS=-c -fpic -I$(INCDIR) -Wall -o
LDFLAGS=-shared -o

PREFIX=/usr/local
OUTPUT=libtheapi.so

SOURCES=$(shell find $(SRCDIR) -name *.c)
HEADERS=$(shell find $(INCDIR) -name *.h)
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(OUTDIR)/%.o)
DEPENDS=$(OBJECTS:.o=.d)

.PHONY: all clean install uninstall
all: $(OUTDIR) $(OUTDIR)/$(OUTPUT)
clean:
	$(RM) $(OUTDIR)

install:
	$(INSTALL) $(OUTDIR)/$(OUTPUT) $(PREFIX)/lib/$(OUTPUT)
	$(INSTALL) -m644 $(INCDIR)/* $(PREFIX)/include
uninstall:
	$(RM) $(PREFIX)/lib/$(OUTPUT)
	$(RM) $(HEADERS:$(INCDIR)/%=$(PREFIX)/include/%)

# thank you based stackoverflow
-include $(DEPENDS)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -MMD -MF $(patsubst %.o,%.d,$@) -MT $@ $< $(CFLAGS) $@

$(OUTDIR):
	@$(MKDIR) $(OUTDIR)

$(OUTDIR)/$(OUTPUT): $(OUTDIR) $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) $@
