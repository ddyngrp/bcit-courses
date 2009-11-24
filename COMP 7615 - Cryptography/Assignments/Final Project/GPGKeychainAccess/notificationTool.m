/*
 notificationTool.m
 GPG Keychain Access
 http://macgpg.sourceforge.net/

 Copyright (c) 2005 MacGPG Project. All rights reserved.

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

#import <Foundation/Foundation.h>

int main(int argc, const char *argv[])
{
	if (2 == argc) {
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		[[NSDistributedNotificationCenter defaultCenter] postNotificationName:[NSString stringWithCString:argv[1]] object:nil];
		// uncomment the following to display the notification in the console
		// fprintf(stderr, "%s\n", argv[1]);
		[pool release];
	} else {
		fprintf(stderr, "Usage: notificationtool notification_name\n");
	}
	return 0;
}