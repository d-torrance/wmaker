defsdata_DATA = WMRootMenu WMWindowAttributes WindowMaker WMState WMGLOBAL

wpexecbindir = @wprefs_bindir@

EXTRA_DIST = WMGLOBAL WMWindowAttributes.in WMState.in

CLEANFILES = WMWindowAttributes WindowMaker WMState WMRootMenu

WMWindowAttributes: $(srcdir)/WMWindowAttributes.in
	$(AM_V_GEN)sed -e "s:#extension#:@ICONEXT@:" \
		$(srcdir)/WMWindowAttributes.in > WMWindowAttributes ; \
	chmod 644 WMWindowAttributes

WindowMaker: $(top_builddir)/src/wmaker
	$< --print-defaults > WindowMaker ; \
	chmod 644 WindowMaker

WMState: $(srcdir)/WMState.in
	$(AM_V_GEN)sed -e "s:#wprefs#:$(wpexecbindir)/WPrefs:" $(srcdir)/WMState.in > WMState ; \
	chmod 644 WMState

WMRootMenu: ./../plmenu
	$(AM_V_GEN)cp -f ./../plmenu WMRootMenu
