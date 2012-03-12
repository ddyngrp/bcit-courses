Create a new Win32 project in Visual Studio 2005 or above.  Add the C ﬁles, headers, 
and resource ﬁles to the project. 

From the Project menu, select Properties.  Under Conﬁguration Properties, click the 
General tab.  Change the Character Set to 'Not Set'.  Expand the Linker tab and click 
the Command Line option.  Add the following to the list: 

* WS2_32.lib 
* winmm.lib 

You should now be able to compile the project. 
