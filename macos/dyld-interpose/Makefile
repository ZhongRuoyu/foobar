.PHONY: all
all: wrapper.dylib dyld-interpose

wrapper.dylib: CFLAGS += -fpic
wrapper.dylib: LDFLAGS += -shared
wrapper.dylib: wrapper.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dyld-interpose: CXXFLAGS += -std=c++17
dyld-interpose: dyld-interpose.cc

.PHONY: clean
clean:
	$(RM) wrapper.o wrapper.dylib dyld-interpose
