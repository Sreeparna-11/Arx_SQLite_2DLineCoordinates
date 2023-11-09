# Arx_SQLite_2DLineCoordinates
ARX application integrated with SQLite to store and use 2D Line coordinates
The ARX application can be used to create a new data base table with two columns, one for X-coordinate and one for Y-coordinate. Each row will be used to store the 2D coordinates of a point. 
There are three commands defined:
1. CreateLineCoord - for creating the table in database and adding data to it. The CREATE TABLE and INSERT query have been implemented here.
2. GetLineCoord - for fetching data from the table and storing it into necessary data structures for further use. The SELECT query has been implemented here.
3. DrawWithLineCoord - for using the fetched data from the table and using the values to draw a 2D line in AutoCAD.

Points to Note to create a similar project:
Step 1:
Download the latest C source code <https://www.sqlite.org/download.html> of SQLite as an amalgamation from its website.

Step 2:
Create a new project with "ARX/DBX Project for AutoCAD" template. Add shell.c and sqlite3.c to Source Files in the project.

Step 3:
Set Project->Properties->C/C++->Code Generation->Smaller Type Check to No

Step 4:
Set Properties->C/C++->Pre Compiled Header->Pre Compiled Header to NOT USING
