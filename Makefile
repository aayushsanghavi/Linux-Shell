SOURCES.c = main.c pinfo.c run.c start.c read.c background.c tilda.c
INCLUDES= 
CFLAGS=
SLIBS= 
PROGRAM= main

OBJECTS= $(SOURCES.c:.c=.o)

.KEEP_STATE:

debug := CFLAGS= -g

all debug: $(PROGRAM)

$(PROGRAM): $(INCLUDES) $(OBJECTS)
	$(LINK.c) -o $@ $(OBJECTS) $(SLIBS)

clean:
	rm -f $(PROGRAM) $(OBJECTS)

