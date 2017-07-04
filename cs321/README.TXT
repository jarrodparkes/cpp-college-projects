========================
SECOND ASSIGNMENT
========================

Jarrod Parkes
CS 321 - Introduction to Object-Oriented Programming with Java
Second Assignment

Included .docx files:
1. Assignment 1 Report - the hard copy for assignment one for reference
2. Assignment 2 Report - the hard copy for THIS ASSIGNMENT

Included .java files:
1. Table.java - the implementation of the Table class
2. Database.java - the implementation of the Database class (a collection of Tables)
3. DBMenu.java - the implementation of the menu that operates Table(s) and the database
4. InvalidDimensionsException.java - for out of bounds exceptions dealing with indices
5. InvalidInputException.java - for unexpected or abnormal inputs
6. NoTableException.java - for calls to table functions when a table does not exist
7. Main.java - the driver of the program to allow testing

To run the project inside of NetBeans 6.9.1:
- Open the NetBeans 6.9.1 IDE with the associated .java files
- Select the Main.java file as the active source file
- Click the "run" button to compile and run the program

JavaDocs:
- Open the project in NetBeans and click Run->Generate JavaDocs

Documentation:
- Test cases, implementation specifications, and javaDocs
  are provided in the attached report
- The SecondAssigment.java files also have comments above 
  functions declarations and implementations that describe
  functionality, etc.

------------------------------------------------------------------------------------

When you build an Java application project that has a main class, the IDE
automatically copies all of the JAR
files on the projects classpath to your projects dist/lib folder. The IDE
also adds each of the JAR files to the Class-Path element in the application
JAR files manifest file (MANIFEST.MF).

To run the project from the command line, go to the dist folder and
type the following:

java -jar "SecondAssignment.jar" 

To distribute this project, zip up the dist folder (including the lib folder)
and distribute the ZIP file.

Notes:

* If two JAR files on the project classpath have the same name, only the first
JAR file is copied to the lib folder.
* Only JAR files are copied to the lib folder.
If the classpath contains other types of files or folders, none of the
classpath elements are copied to the lib folder. In such a case,
you need to copy the classpath elements to the lib folder manually after the build.
* If a library on the projects classpath also has a Class-Path element
specified in the manifest,the content of the Class-Path element has to be on
the projects runtime path.
* To set a main class in a standard Java project, right-click the project node
in the Projects window and choose Properties. Then click Run and enter the
class name in the Main Class field. Alternatively, you can manually type the
class name in the manifest Main-Class element.
