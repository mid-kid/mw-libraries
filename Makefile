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
libver_all := $(shell sed 's/#.*$$//;/^\s*$$/d' libvers.txt)

build_ver := $(build)/$(subst /,_,$(libver))

.NOTPARALLEL: check
.PHONY: check
check:

.NOTPARALLEL: full
.PHONY: full
full:

define defver
check: check-$2
.PHONY: check-$2
check-$2: full-$2
	cat sums/$1/strip.sum | sed 's/^[^ ]* \*\?//' > $(build)/$2.strip
	cat $(build)/$2.strip | \
		sed 's/[^^]/[&]/g;s/\^/\\^/g;s/$$$$/$$$$/' | \
		grep -vf - sums/$1/lib.sum > $(build)/$2.sum
	cat sums/$1/strip.sum >> $(build)/$2.sum || true
	cat $(build)/$2.strip | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		xargs -r $(STRIP) -vgD -R .comment )
	cat $(build)/$2.sum | ( \
		cd $(build)/install/lib/metroskrew/sdk/$1 && \
		sha1sum --quiet -c - )

full: full-$2
.PHONY: full-$2
full-$2:
	+$(MAKE) $(MAKEFLAGS) libver=$1 package
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
