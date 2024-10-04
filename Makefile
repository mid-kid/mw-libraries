MESON ?= meson

CROSS := meson/mwccarm.ini

build := build
libver := dsi/1.6sp1

.PHONY: all
all: $(build)/build.ninja
	$(MESON) compile -C build

.PHONY: check
check: package
	cat sums/$(libver)/lib.sum | grep -v 'ProfileLibrary' | ( \
		cd $(build)/install/lib/metroskrew/sdk/$(libver) && \
		sha1sum --quiet -c - )
	cat sums/$(libver)/profiler.sum | ( \
		cd $(build)/install/lib/metroskrew/sdk/$(libver) && \
		sha1sum --quiet -c - )

.PHONY: package
package: $(build)/build.ninja
	rm -rf $(build)/install
	$(MESON) install -C $(build) --destdir install

.PHONY: clean
clean:
	! test -f $(build)/build.ninja || \
		$(MESON) compile -C $(build) --clean

.PHONY: distclean
distclean:
	rm -rf $(build)
	$(MESON) subprojects purge --confirm || true

$(build)/build.ninja:
	$(MESON) setup $(build) --cross-file $(CROSS) \
		--prefix / -Dlibver=$(libver)
