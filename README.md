This is proof of concept code for a particle based weathering system.

Firstyly clone the source code from github. This can be done by navigating to the directory you want the code to
be stored in on the command line (terminal). Once here use the command:

git clone git@github.com:md349/POC2.git

This should clone the whole repository to the directory you selected. This method requires a ssh key to be set up
between your computer and github. An alternative is to download the code as a zip file.

Once the code has downloaded it can be run. There are two ways to run this code. It can be compiled from within
Qt creator or from the command line. To open in Qt creator, double click the .pro file. You can also use the
command "qtcreator [filename.pro] &" on a Bournemouth University linux machine. Once it is loaded into Qt creator
the project must be configured. To run the code in Qt creator you must first run qmake, in Build menu. Then run
clean all, in Build menu. Then build all, in Build menu. Once all these have completed you can press the run
button or ctrl R.

The preferred compiler is clang++ but gcc should work. 

To compile via the command line using clang++:
"clang++ -Wall -o [executableName] main.cpp"
Using gcc :
"gcc -Wall -o [executableName] main.cpp"

The main.cpp file can be found in the src directory. Once it has compiled, navigate to where the executable file
has been created. To run use ./executableName

This project has a number of dependencies. It depends on the shader files provided and NGL. NGL depends on boost.
Therefore to run this project you must ensure that boost and NGL are install and the shader files are included
with the rest of the source code.

To install boost: the source files can be downloaded from the boost website and installed in a location of your
choice.

On a mac it may be easier to install boost with the aid of package managers like homebrew. NGL must be installed
in the home directory. To install NGL navigate to your home directory and pull NGL from github using: 
"git clone git@github.com/NCCA/NGL.git"

To get these working with the project NGL needs to be built. To do this open the NGL.pro file in Qt Creator.
Ensure NGL is pointing to the install location of boost by ensuring "unix:INCLUDEPATH+= " points to boost (or the
equivalent for your operating system)Now run qmake and build NGL as before. 

As well as NGL being installed the project also needs to know where boost is. To ensure it will work, in the
POC2.pro file make sure the "INCLUDEPATH" is pointing to boost. Now a working instance of NGL is installed we
have to tell the project where to find the library. In Qt Creator Projects tab. In the Build tab ensure the build
directory points to your NGL installation. In the Run tab add 
"DYLD_LIBRARY_PATH = [file path to NGL libdirectory]". 
Run qmake and build the project again. When it builds you can press Run or ctrl R and the program will run.

When it runs the project will assign the particles to their starting positions, as stated in the design report.
Spheres are drawn to represent each γ-ton. After the scene is drawn the γ-tons propagate towards the origin. When
they intersect with the origin or the origin plane (this depends on the type of emission) they are drawn again.
After this they stochastically select whether they reflect, bounce or settle. This is select using NGL::Random
and is not drawn. Their decision is output as text as well as their starting position and their position when
they hit the origin, or origin plane.

I hope you like the early γ-tons. 