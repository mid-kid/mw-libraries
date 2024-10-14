MESON ?= meson

ifndef STRIP
STRIP := $(shell command -v arm-none-eabi-strip 2> /dev/null)
endif
ifndef STRIP
STRIP := $(shell command -v strip 2> /dev/null)
endif

CROSS := meson/mwccarm.ini

build := build

libver := dsi/1.6sp1
libver_all := dsi/1.6sp1 dsi/1.3 dsi/1.2

build_ver := $(build)/$(subst /,_,$(libver))

.PHONY: check
check:
define defver
ver := $$(subst /,_,$1)
check: check-$$(ver)
.PHONY: check-$$(ver)
check-$$(ver):
	$(MAKE) libver=$1 package
	cat sums/$1/lib.sum | grep -v 'ProfileLibrary' | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		sha1sum --quiet -c - )
	$(STRIP) -vgD -R .comment $(build)/install/lib/metroskrew/sdk/$1/Profiler/Lib/*.a
	cat sums/$1/profiler.sum | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		sha1sum --quiet -c - )
endef
$(foreach v,$(libver_all),$(eval $(call defver,$(v))))

.PHONY: all
all: $(build_ver)/build.ninja
	$(MESON) compile -C $(build_ver)

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
