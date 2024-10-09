MESON ?= meson

CROSS := meson/mwccarm.ini

build := build

libver := dsi/1.6sp1

build_ver := $(build)/$(subst /,_,$(libver))

.PHONY: all
all: $(build_ver)/build.ninja
	$(MESON) compile -C $(build_ver)

.PHONY: check
check: package
	cat sums/$(libver)/lib.sum | grep -v 'ProfileLibrary' | ( \
		cd $(build)/install/lib/metroskrew/sdk/$(libver) && \
		sha1sum --quiet -c - )
	cat sums/$(libver)/profiler.sum | ( \
		cd $(build)/install/lib/metroskrew/sdk/$(libver) && \
		sha1sum --quiet -c - )

.PHONY: package
package: $(build_ver)/build.ninja
	$(MESON) install -C $(build_ver) --destdir ../install

.PHONY: clean
clean:
	! test -f $(build_ver)/build.ninja || \
		$(MESON) compile -C $(build_ver) --clean

.PHONY: distclean
distclean:
	rm -rf $(build)
	$(MESON) subprojects purge --confirm || true

$(build_ver)/build.ninja:
	mkdir -p $(build_ver)
	$(MESON) setup $(build_ver) --cross-file $(CROSS) \
		--prefix / -Dlibver=$(libver)
