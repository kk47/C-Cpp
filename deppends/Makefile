include common.def

DIRS = protobuf boost log4cpp xsd

ifeq ($(TARGETOS), WINDOWS)
DIRS += xerces-c dokan
endif

ifeq ($(TARGETOS), LINUX)
DIRS += xerces-c jemalloc requests
endif

ifeq ($(TARGETOS), OSX)
DIRS += xerces-c3
endif

.PHONY: all $(DIRS) clean

all: $(DIRS)

$(DIRS):
	@if [ "x$(CPPET)" = "x" ]; then \
		echo "Please set environment variable 'CPPET' first.";\
		exit 1; \
	fi
	@if [ "x$(TARGETOS)" = "x" ]; then \
		echo "Please set proper 'TARGETOS' in common.def.";\
		exit 1; \
	fi

	@$(MAKE) -C $@

clean:
	@for i in $(DIRS); do\
		$(MAKE) -C $$i clean; \
    done; 
