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
libver_all := \
	dsi/1.6sp1 dsi/1.3 dsi/1.2 dsi/1.1p1 dsi/1.1 \
	ds/2.0/sp2p3 ds/2.0/sp2 ds/2.0/sp1p2

build_ver := $(build)/$(subst /,_,$(libver))

.PHONY: check
check:
define defver
check: check-$2
.PHONY: check-$2
check-$2:
	$(MAKE) libver=$1 package
	cat sums/$1/strip.sum | sed 's/^[^ ]* \*\?//' > $(build)/$2.strip
	cat $(build)/$2.strip | \
		sed 's/[^^]/[&]/g;s/\^/\\^/g;s/$$$$/$$$$/' | \
		grep -vf - sums/$1/lib.sum > $(build)/$2.sum
	cat sums/$1/strip.sum >> $(build)/$2.sum
	cat $(build)/$2.strip | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		xargs -r $(STRIP) -vgD -R .comment )
	cat $(build)/$2.sum | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		sha1sum --quiet -c - )
endef
$(foreach v,$(libver_all),$(eval $(call defver,$v,$(subst /,_,$v))))

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
