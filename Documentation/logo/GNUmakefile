depth = ../..

STEPMAKE_TEMPLATES=documentation
XPM_FILES=$(call src-wildcard,*.xpm)

lilypond-icon = $(outdir)/lilypond.ico
ly-icon = $(outdir)/ly.ico

include $(depth)/make/stepmake.make

ifeq ($(PLATFORM_WINDOWS),yes)

$(outdir)/%.ico: %.xpm
	$(call ly_progress,Making,$@,< xpm)
	$(buildscript-dir)/genicon $< $@

default: $(lilypond-icon) $(ly-icon)

endif # PLATFORM_WINDOWS

local-dist: $(icon) 
xgifs: $(OUTGIF_FILES)
pngs: $(OUTPNG_FILES)

ifeq ($(out),www)
local-WWW-1: $(OUTPNG_FILES)
endif
