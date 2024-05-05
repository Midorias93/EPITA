SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

config/libconfig.a:
	$(MAKE) -C $(SRC_DIR)config

utils/string/libstring.a:
	$(MAKE) -C utils

server/libserver.a:
	$(MAKE) -C server

daemon/libdaemon.a:
	$(MAKE) -C daemon
