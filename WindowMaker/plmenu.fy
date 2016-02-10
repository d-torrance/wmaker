("Programma's",
 ("Ynfo",
  ("Ynfopaniel", INFO_PANEL),
  ("Juridyske ynfo", LEGAL_PANEL),
  ("Systeemconsole", EXEC, "xconsole"),
  ("Systeembelêsting", SHEXEC, "xosview || xload"),
  ("Proseslist", EXEC, "xterm -e top"),
  ("Hantliedingblêder", EXEC, "xman")
 ),
 ("Utfiere...", SHEXEC, "%a(Utfiere,Typ út te fieren kommando:)"),
 ("XTerm", EXEC, "xterm -sb"),
 ("Mozilla Firefox", EXEC, "firefox"),
 ("Wurkromten", WORKSPACE_MENU),
 ("Programma's",
  ("Gimp", SHEXEC, "gimp >/dev/null"),
  ("Ghostview", EXEC, "ghostview %a(Fier te besjen bestân yn)"),
  ("Xpdf", EXEC, "xpdf %a(Fier te besjen PDF yn)"),
  ("Abiword", EXEC, "abiword"),
  ("Dia", EXEC, "dia"),
  ("OpenOffice.org",
   ("OpenOffice.org", EXEC, "ooffice"),
   ("Writer", EXEC, "oowriter"),
   ("Rekkenblêd", EXEC, "oocalc"),
   ("Draw", EXEC, "oodraw"),
   ("Impress", EXEC, "ooimpress")
  ),
  ("Tekstbewurkers",
   ("XEmacs", EXEC, "xemacs"),
   ("Emacs", EXEC, "emacs"),
   ("XJed", EXEC, "xjed"),
   ("VI", EXEC, "xterm -e vi"),
   ("GVIM", EXEC, "gvim"),
   ("NEdit", EXEC, "nedit"),
   ("Xedit", EXEC, "xedit")
  ),
  ("Multymedia",
   ("XMMS",
    ("XMMS", EXEC, "xmms"),
    ("XMMS ôfspylje/skoftsje", EXEC, "xmms -t"),
    ("XMMS stopje", EXEC, "xmms -s")
   ),
   ("Xine fideospiler", EXEC, "xine"),
   ("MPlayer", EXEC, "mplayer")
  )
 ),
 ("Helpmiddels",
  ("Rekkenmasine", EXEC, "xcalc"),
  ("Finstereigenskippen", SHEXEC, "xprop | xmessage -center -title 'xprop' -file -"),
  ("Lettertypekiezer", EXEC, "xfontsel"),
  ("Fergrutsje", EXEC, "wmagnify"),
  ("Kleurekaart", EXEC, "xcmap"),
  ("X-programma deadzje", EXEC, "xkill")
 ),
 ("Seleksje",
  ("Kopiearje", SHEXEC, "echo '%s' | wxcopy"),
  ("E-maile nei", EXEC, "xterm -name mail -T Pine -e pine %s"),
  ("Navigearje", EXEC, "mozilla %s"),
  ("Sykje yn hantlieding", EXEC, "MANUAL_SEARCH(%s)")
 ),
 ("Kommando's",
  ("Oare ferbergje", HIDE_OTHERS),
  ("Alles toane", SHOW_ALL),
  ("Ikoanen skikke", ARRANGE_ICONS),
  ("Fernije", REFRESH),
  ("Beskoattelje", EXEC, "xlock -allowroot -usefirst")
 ),
 ("Uterlik",
  ("Tema's", OPEN_MENU, "-noext #wmdatadir#/Themes $HOME/GNUstep/Library/WindowMaker/Themes WITH setstyle"),
  ("Stilen", OPEN_MENU, "-noext #wmdatadir#/Styles $HOME/GNUstep/Library/WindowMaker/Styles WITH setstyle"),
  ("Ikoanesets", OPEN_MENU, "-noext #wmdatadir#/IconSets $HOME/GNUstep/Library/WindowMaker/IconSets WITH seticons"),
  ("Eftergrûn",
   ("Effen",
	("Swart", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, black)'"),
	("Blau",  EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#505075\")'"),
	("Indigo", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#243e6c\")'"),
	("Marineblau", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#224477\")'"),
	("Poarper", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#554466\")'"),
	("Weet", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, wheat4)'"),
	("Donkergriis", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#333340\")'"),
	("Wynread", EXEC, "wdwrite WindowMaker WorkspaceBack '(solid, \"#400020\")'")
   ),
   ("Kleurferrin",
	("Sinneûndergong", EXEC, "wdwrite WindowMaker WorkspaceBack '(mvgradient, deepskyblue4, black, deepskyblue4, tomato4)'"),
	("Loft", EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, blue4, white)'"),
	("Blautinten",     EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#7080a5\", \"#101020\")'"),
	("Indigotinten",    EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#746ebc\", \"#242e4c\")'"),
	("Poarpertinten",    EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#654c66\", \"#151426\")'"),
	("Weettinten",     EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#a09060\", \"#302010\")'"),
	("Griistinten",     EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#636380\", \"#131318\")'"),
	("Wynreadtinten",  EXEC, "wdwrite WindowMaker WorkspaceBack '(vgradient, \"#600040\", \"#180010\")'")
   ),
   ("Ofbyldingen", OPEN_MENU, "-noext #wmdatadir#/Backgrounds $HOME/GNUstep/Library/WindowMaker/Backgrounds WITH wmsetbg -u -t")
   ),
   ("Tema bewarje", SHEXEC, "getstyle -t $HOME/GNUstep/Library/WindowMaker/Themes/\"%a(Temanamme)\""),
   ("Ikoaneset bewarje", SHEXEC, "geticonset $HOME/GNUstep/Library/WindowMaker/IconSets/\"%a(Ikoanesetnamme)\""),
   ("Foarkarrehelpmiddel", EXEC, "/usr/local/GNUstep/Applications/WPrefs.app/WPrefs")
   ),
   ("Sesje",
    ("Sesje bewarje", SAVE_SESSION),
    ("Sesje wiskje", CLEAR_SESSION),
	("Window Maker werstarte", RESTART),
	("BlackBox starte", RESTART, blackbox),
	("IceWM starte", RESTART, icewm),
	("Ofslute", EXIT)
   )
)
