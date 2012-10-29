Installation Notes:
===================

There are no specific requirements for this Android application
apart from either the emulator or android phone having Internet
access.

Misc Notes:
===========

The RSS Feeds have been hard-coded within the "RssReader.java" class.
This was done in the interest of time (too many things to do at once
at the moment). It should be noted that if you wish to add your own
RSS feed, you need to get the full feed URL.

For instance, the RSS feed for "http://slashdot.org" is actually
"http://rss.slashdot.org/Slashdot/slashdot". A future implementation
of this application could parse the home page for a particular site
in order to look for RSS feed info.

Functional Program Listing:
===========================

For both this application and the in-class demo, I made use of
"Working with XML on Android" from IBM's developerWorks. However,
my resulting project is far more complicated than the simple
examples used within this document. For the most part, the
SAX Parser and SAX Handler are very similar to my original
demo and that of IBM's article. However, because these classes
perform simple tasks, relatively few changes were necessary apart
from specifically managing the tags used within RSS feeds.

One of the major challenges that I refused to give up was that of
data communication between activities. When the application launches,
it downloads all the articles within each references RSS feed. When a
user clicks on a feed within the list, an ArrayList of all that
particular feed's articles needed to be passed onto the new activity.
Unfortunately, this isn't as simple as passing bundled strings as
the ArrayList needs to implement the Parcelable interface.

There are few examples on the Internet dealing with passing an
ArrayList of objects within a bundle. After much trial and error, I
came across a tutorial on passing ArrayLists across activities. More
specifically, an example that dealt with ArrayLists of complex data
objects and not simply one of primitive types. This article was
heavily referenced by my application.

Overall, I couldn't really say that my application in novel. However,
I doubt I would have become so familiar with the Parcelable interface
without doing this project. It should be noted that for all the example
RSS feed applications available, they all tend to deal with single feeds
whereas my application managed multiple feeds and allows you to drill
down into individual articles rendered within a WebView as opposed to
simply loading up the article in an external browser.

Working with XML on Android
http://www.ibm.com/developerworks/xml/library/x-android/

Simple Tutorial: Passing ArrayList accross Activities
http://www.anddev.org/simple_tutorial_passing_arraylist_across_activities-t9996.html