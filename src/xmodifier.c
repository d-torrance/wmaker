/* Grok X modifier mappings for shortcuts.

Most of this code was taken from src/event-Xt.c in XEmacs 20.3-b17.
The copyright(s) from the original XEmacs code are included below.

Perpetrator: Sudish Joseph <sj@eng.mindspring.net>, Sept. 1997. */

/* The event_stream interface for X11 with Xt, and/or tty frames.
 Copyright (C) 1991, 1992, 1993, 1994, 1995 Free Software Foundation, Inc.
 Copyright (C) 1995 Sun Microsystems, Inc.
 Copyright (C) 1996 Ben Wing.

 This file is part of XEmacs.

 XEmacs is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation; either version 2, or (at your option) any
 later version.

 XEmacs is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

 You should have received a copy of the GNU General Public License along
 with XEmacs; see the file COPYING. if not, write to the
 Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301 USA. */

#include "wconfig.h"

#include <string.h>
#include <strings.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include <WINGs/WUtil.h>
#include "WindowMaker.h"
#include "xmodifier.h"


/************************************************************************/
/*                            keymap handling                           */
/************************************************************************/

/* X bogusly doesn't define the interpretations of any bits besides
 ModControl, ModShift, and ModLock; so the Interclient Communication
 Conventions Manual says that we have to bend over backwards to figure
 out what the other modifier bits mean.  According to ICCCM:

 - Any keycode which is assigned ModControl is a "control" key.

 - Any modifier bit which is assigned to a keycode which generates Meta_L
 or Meta_R is the modifier bit meaning "meta".  Likewise for Super, Hyper,
 etc.

 - Any keypress event which contains ModControl in its state should be
 interpreted as a "control" character.

 - Any keypress event which contains a modifier bit in its state which is
 generated by a keycode whose corresponding keysym is Meta_L or Meta_R
 should be interpreted as a "meta" character.  Likewise for Super, Hyper,
 etc.

 - It is illegal for a keysym to be associated with more than one modifier
 bit.

 This means that the only thing that emacs can reasonably interpret as a
 "meta" key is a key whose keysym is Meta_L or Meta_R, and which generates
 one of the modifier bits Mod1-Mod5.

 Unfortunately, many keyboards don't have Meta keys in their default
 configuration.  So, if there are no Meta keys, but there are "Alt" keys,
 emacs will interpret Alt as Meta.  If there are both Meta and Alt keys,
 then the Meta keys mean "Meta", and the Alt keys mean "Alt" (it used to
 mean "Symbol," but that just confused the hell out of way too many people).

 This works with the default configurations of the 19 keyboard-types I've
 checked.

 Emacs detects keyboard configurations which violate the above rules, and
 prints an error message on the standard-error-output.  (Perhaps it should
 use a pop-up-window instead.)
 */

static int MetaMask, HyperMask, SuperMask, AltMask, ModeMask;

static const char *index_to_name(int indice)
{
	switch (indice) {
	case ShiftMapIndex:
		return "ModShift";
	case LockMapIndex:
		return "ModLock";
	case ControlMapIndex:
		return "ModControl";
	case Mod1MapIndex:
		return "Mod1";
	case Mod2MapIndex:
		return "Mod2";
	case Mod3MapIndex:
		return "Mod3";
	case Mod4MapIndex:
		return "Mod4";
	case Mod5MapIndex:
		return "Mod5";
	default:
		return "???";
	}
}

static void x_reset_modifier_mapping(Display * display)
{
	int modifier_index, modifier_key, column, mkpm;
	int meta_bit = 0;
	int hyper_bit = 0;
	int super_bit = 0;
	int alt_bit = 0;
	int mode_bit = 0;
	XModifierKeymap *x_modifier_keymap = XGetModifierMapping(display);

#define modwarn(name,old,other)							\
    wwarning ("%s (0x%x) generates %s, which is generated by %s.",		\
    name, code, index_to_name (old), other)

#define modbarf(name,other)							\
    wwarning ("%s (0x%x) generates %s, which is nonsensical.",			\
    name, code, other)

#define check_modifier(name,mask)						\
    if ((1<<modifier_index) != mask)						\
    wwarning ("%s (0x%x) generates %s, which is nonsensical.",			\
    name, code, index_to_name (modifier_index))

#define store_modifier(name,old)						\
    if (old && old != modifier_index)						\
    wwarning ("%s (0x%x) generates both %s and %s, which is nonsensical.",	\
    name, code, index_to_name (old),						\
    index_to_name (modifier_index));						\
    if (modifier_index == ShiftMapIndex) modbarf (name,"ModShift");		\
    else if (modifier_index == LockMapIndex) modbarf (name,"ModLock");		\
    else if (modifier_index == ControlMapIndex) modbarf (name,"ModControl");	\
    else if (sym == XK_Mode_switch)						\
    mode_bit = modifier_index; /* Mode_switch is special, see below... */	\
    else if (modifier_index == meta_bit && old != meta_bit)			\
    modwarn (name, meta_bit, "Meta");						\
    else if (modifier_index == super_bit && old != super_bit)			\
    modwarn (name, super_bit, "Super");						\
    else if (modifier_index == hyper_bit && old != hyper_bit)			\
    modwarn (name, hyper_bit, "Hyper");						\
    else if (modifier_index == alt_bit && old != alt_bit)			\
    modwarn (name, alt_bit, "Alt");						\
    else									\
    old = modifier_index;

	mkpm = x_modifier_keymap->max_keypermod;
	for (modifier_index = 0; modifier_index < 8; modifier_index++)
		for (modifier_key = 0; modifier_key < mkpm; modifier_key++) {
			KeySym last_sym = 0;
			for (column = 0; column < 4; column += 2) {
				KeyCode code = x_modifier_keymap->modifiermap[modifier_index * mkpm
									      + modifier_key];
				KeySym sym = (code ? XkbKeycodeToKeysym(display, code, 0, column) : 0);
				if (sym == last_sym)
					continue;
				last_sym = sym;
				switch (sym) {
				case XK_Mode_switch:
					store_modifier("Mode_switch", mode_bit);
					break;
				case XK_Meta_L:
					store_modifier("Meta_L", meta_bit);
					break;
				case XK_Meta_R:
					store_modifier("Meta_R", meta_bit);
					break;
				case XK_Super_L:
					store_modifier("Super_L", super_bit);
					break;
				case XK_Super_R:
					store_modifier("Super_R", super_bit);
					break;
				case XK_Hyper_L:
					store_modifier("Hyper_L", hyper_bit);
					break;
				case XK_Hyper_R:
					store_modifier("Hyper_R", hyper_bit);
					break;
				case XK_Alt_L:
					store_modifier("Alt_L", alt_bit);
					break;
				case XK_Alt_R:
					store_modifier("Alt_R", alt_bit);
					break;
				case XK_Control_L:
					check_modifier("Control_L", ControlMask);
					break;
				case XK_Control_R:
					check_modifier("Control_R", ControlMask);
					break;
				case XK_Shift_L:
					check_modifier("Shift_L", ShiftMask);
					break;
				case XK_Shift_R:
					check_modifier("Shift_R", ShiftMask);
					break;
				case XK_Shift_Lock:
					check_modifier("Shift_Lock", LockMask);
					break;
				case XK_Caps_Lock:
					check_modifier("Caps_Lock", LockMask);
					break;

					/* It probably doesn't make any sense for a modifier bit to be
					   assigned to a key that is not one of the above, but OpenWindows
					   assigns modifier bits to a couple of random function keys for
					   no reason that I can discern, so printing a warning here would
					   be annoying. */
				}
			}
		}
#undef store_modifier
#undef check_modifier
#undef modwarn
#undef modbarf

	/* If there was no Meta key, then try using the Alt key instead.
	   If there is both a Meta key and an Alt key, then the Alt key
	   is not disturbed and remains an Alt key. */
	if (!meta_bit && alt_bit)
		meta_bit = alt_bit, alt_bit = 0;

	/* mode_bit overrides everything, since it's processed down inside of
	   XLookupString() instead of by us.  If Meta and Mode_switch both
	   generate the same modifier bit (which is an error), then we don't
	   interpret that bit as Meta, because we can't make XLookupString()
	   not interpret it as Mode_switch; and interpreting it as both would
	   be totally wrong. */
	if (mode_bit) {
		const char *warn = 0;
		if (mode_bit == meta_bit)
			warn = "Meta", meta_bit = 0;
		else if (mode_bit == hyper_bit)
			warn = "Hyper", hyper_bit = 0;
		else if (mode_bit == super_bit)
			warn = "Super", super_bit = 0;
		else if (mode_bit == alt_bit)
			warn = "Alt", alt_bit = 0;
		if (warn) {
			wwarning("%s is being used for both Mode_switch and %s.",
			     index_to_name(mode_bit), warn);
		}
	}

	MetaMask = (meta_bit ? (1 << meta_bit) : 0);
	HyperMask = (hyper_bit ? (1 << hyper_bit) : 0);
	SuperMask = (super_bit ? (1 << super_bit) : 0);
	AltMask = (alt_bit ? (1 << alt_bit) : 0);
	ModeMask = (mode_bit ? (1 << mode_bit) : 0);	/* unused */

	XFreeModifiermap(x_modifier_keymap);
}

const char *wXModifierToShortcutLabel(int mask)
{
	if (mask < 0)
		return NULL;

	if (mask == ShiftMask)
		return "Sh+";
	if (mask ==  ControlMask)
		return "^";
	if (mask ==  AltMask)
		return "A+";
	if (mask ==  Mod1Mask)
		return "M1+";
	if (mask ==  Mod2Mask)
		return "M2+";
	if (mask ==  Mod3Mask)
		return "M3+";
	if (mask ==  Mod4Mask)
		return "M4+";
	if (mask ==  Mod5Mask)
		return "M5+";
	if (mask ==  MetaMask)
		return "M+";

	wwarning("Can't convert keymask %d to shortcut label", mask);
	return NULL;
}

int wXModifierFromKey(const char *key)
{
	if (strcasecmp(key, "SHIFT") == 0 && ShiftMask != 0)
		return ShiftMask;
	else if (strcasecmp(key, "CONTROL") == 0 && ControlMask != 0)
		return ControlMask;
	else if (strcasecmp(key, "ALT") == 0 && AltMask != 0)
		return AltMask;
	else if (strcasecmp(key, "META") == 0 && MetaMask != 0)
		return MetaMask;
	else if (strcasecmp(key, "SUPER") == 0 && SuperMask != 0)
		return SuperMask;
	else if (strcasecmp(key, "HYPER") == 0 && HyperMask != 0)
		return HyperMask;
	else if (strcasecmp(key, "MOD1") == 0 && Mod1Mask != 0)
		return Mod1Mask;
	else if (strcasecmp(key, "MOD2") == 0 && Mod2Mask != 0)
		return Mod2Mask;
	else if (strcasecmp(key, "MOD3") == 0 && Mod3Mask != 0)
		return Mod3Mask;
	else if (strcasecmp(key, "MOD4") == 0 && Mod4Mask != 0)
		return Mod4Mask;
	else if (strcasecmp(key, "MOD5") == 0 && Mod5Mask != 0)
		return Mod5Mask;
	else
		return -1;
}

/* Wrapper so that we may fit the WM naming conventions, yet leave the
 original XEmacs function name in place. */
void wXModifierInitialize(void)
{
	x_reset_modifier_mapping(dpy);
}
