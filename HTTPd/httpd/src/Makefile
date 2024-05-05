include flags.mk

OBJ = main.o

LIBS = config/libconfig.a \
	utils/string/libstring.a \
	server/libserver.a \
	daemon/libdaemon.a

all: httpd

httpd: $(OBJ) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) -Wl,--start-group $(LIBS) -Wl,--end-group

clean:
	$(MAKE) -C utils clean
	$(MAKE) -C config clean
	$(MAKE) -C server clean
	$(MAKE) -C daemon clean
	$(RM) httpd main.o

include libs.mk

.PHONY: all
