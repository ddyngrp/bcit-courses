DataComm Assignment 2 (VT100 Emulator)

Steffen Norgren
A00683006

Doug Penner
A00658271


Compiling:
- Create a new project with existing source in Visual Studio.
 - Pic the "src" folder as location of existing source.
- Set the character encoding for the project to "not set"
- Compile

Running:
- Run the "Terminal.exe" file from the "exe" folder
 - Due to library issues, it is strongly recommended to recompile the application from source (see above)

Bugs:
- Caret dissapears afters chaging fonts
- Scrolling regions not yet implemented
 - Scrolling works if you scroll by an entire screen at a time due to the server simply redrawing the screen

Troubles:
- Microsoft has an unbelievably small amount of documentation available regarding event driven serial communcations.
