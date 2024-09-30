MESON ?= meson

CROSS := meson/mwccarm.ini

build := build

.PHONY: all
all: $(build)/build.ninja
	$(MESON) compile -C build

.PHONY: clean
clean:
	! test -f $(build)/build.ninja || \
		$(MESON) compile -C $(build) --clean

.PHONY: distclean
distclean:
	rm -rf $(build)
	$(MESON) subprojects purge --confirm || true

$(build)/build.ninja:
	$(MESON) setup $(build) --cross-file $(CROSS)
