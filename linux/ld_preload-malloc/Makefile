.PHONY: all
all: ld_preload.so

ld_preload.so: override CFLAGS += -fpic
ld_preload.so: override LDFLAGS += -shared -ldl
ld_preload.so: ld_preload.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) ld_preload.o ld_preload.so
