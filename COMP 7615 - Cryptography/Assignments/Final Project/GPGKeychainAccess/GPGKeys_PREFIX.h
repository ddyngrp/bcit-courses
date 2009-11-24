/*
 GPGKeys_PREFIX.h
 GPG Keychain Access
 http://macgpg.sourceforge.net/

 Created by Randall Wood on Tue Jun 24 2003.
 Copyright (c) 2003 Randall Wood. All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*!
 @header GPG Keychain
 @abstract The GPG Keychain Prefix controls compilation options for the GPG Keychain
 @discussion GPG Keychain can be compiled with certain options turned on or off. All
 such options are configured in the prefix. In addition each option may be turned on
 or off seperately for each build style.

 This system of controlling compilation options allows a deployment build to retain
 older behaivors while a development build is working on changing those features.

 Note that there is one significant build structure that we can't muck with in this
 way: GPGME.framework versioning. The gpgme.h header in libgpgme is very specific
 about this: the GPGME_VERSION definition is not to be used for version checking. It
 has to be done at runtime.
 */

/*!
 @define VERBOSE_LOGGING
 @abstract Controls how logging to console is handled
 @discussion By default logging is turned on for DEVELOPMENT style builds and off for DEPLOYMENT
 style builds. This macro is used to flag that setting. If the application is built without specifying
 the VERBOSE_LOGGING setting using -D VERBOSE_LOGGING=[1|0], it gets turned on here.
 */
#ifndef VERBOSE_LOGGING
#define VERBOSE_LOGGING 1
#endif

/*!
 @define USE_SYSTEM_PREFERENCES
 @abstract Controls how preferences are handled
 @discussion The preferences for GPG Keychain can at present be displayed either
 in a window owned by GPG Keychain or in a pane in the System Preferences.app

 If the preferences are to be loaded by GPG Keychain, they must exist in the folder:
 /path/to/GPG Keychain.app/Contents/Resources/PreferencePanes, whereas if they are to
 be loaded by System Preferences, they must exist in the folder
 &lt;domain&gt;/Library/PreferencePanes
 */
#ifndef USE_SYSTEM_PREFERENCES
#define USE_SYSTEM_PREFERENCES 0
#endif

/*!
 @define USE_MULTIPLE_PREFERENCES
 @abstract Allow multiple preference panes to be loaded by GPG Keychain
 @discussion GPG Keychain can load multiple preference panes in the style of
 System Preferences.app or it may be compiled to just load one preference pane.
 */
#ifndef USE_MULTIPLE_PREFERENCES
#define USE_MULTIPLE_PREFERENCES 0
#endif

/*!
 @define INTEGRATE_WITH_ICAL
 @abstract Integrate some GPG Keychain functions with iCal
 @discussion Users who create expiring keys might like to be reminded to create a
 new key before the old one expires.
 */
#ifndef INTEGRATE_WITH_ICAL
#define INTEGRATE_WITH_ICAL 0
#endif