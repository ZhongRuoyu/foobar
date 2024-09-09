PATCHELF = patchelf

.PHONY: all
all: wrapper.so ld-preload

wrapper.so: CFLAGS += -fpic
wrapper.so: LDFLAGS += -shared -ldl
wrapper.so: wrapper.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

ld-preload: CXXFLAGS += -std=c++17
ld-preload: ld-preload.cc

.PHONY: patch
patch: wrapper.so
	$(PATCHELF) --print-needed $^ | grep -Fq libdl.so.2 \
		|| $(PATCHELF) --add-needed libdl.so.2 $^

.PHONY: clean
clean:
	$(RM) wrapper.o wrapper.so ld-preload
