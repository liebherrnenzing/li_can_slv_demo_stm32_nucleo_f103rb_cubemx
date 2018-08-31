## Example for STM32F1 Nucleo Eval-Board #

This is a basic example which shows how to use the li_can_slv stack on a NUCLEOF103RB board. The example was developed for a custom in-house baseboard but it can also be used on a normal NUCLEOF103RB board. As you can see in the project folder we have used CubeMX to generate the basic hardware layer.

### Hardware needed 

*   NucleoF103RB Development Board
*	A CAN Bus Break-out Board like tihis one http://copperhilltech.com/can-bus-breakout-board-5-vdc. Following pins are used for CAN.

	| Pin | Name   |
	|-----|:------:|
	| PB8 | CAN_RX |
	| PB9 | CAN_TX |

*  The example also uses this serial pins for some debugging output.
  
  	| Pin  | Name      |
	|------|:---------:|
	| PA9  | USART1_TX |
	| PA10 | USART1_RX |
  

### How to start with the software? ###

First of all it is necessary to install some basic tools like python, cmake and gcc. We also recommend to install eclipse because otherwise someone can not really debugging in a comfortable way. So follow the basic steps on this webpage to setup a GNU MCU Eclipse Toolchain. https://gnu-mcu-eclipse.github.io/install/

##### Clone the Repository

Clone the repository with ``git clone recursive`` because the projects uses submodules. You must use SSH because the submodules used in this example uses SSh URL's. So as an example use. 

``git clone git@github.com:liebherrnenzing/li_can_slv.git --recursive``


##### Install the needed Tools
* First install a GNU MCU Eclipse Toolchain
* Install cmake >= 2.8
* Install python 3.6.x, I recommend to use a python virtualenv because then you can install the libs needed in an easy way. So use a shell like windows cmd and navigate to the root of the project. Activate the virtual environment you have created via ``workon py36_invoke`` After that install the libs via ``pip install -r requirements.txt`` If this dose not work you do not have installed all the virtualenv tools the right way. 
* Change the used program paths in two files ``invoke.py`` and ``build_settings.cmake``.

##### Compile the project

At this point it should be possible to use invoke to build the project. Use the following commands for that:

1. Generate the Make for the cmake out of source build:

``inv configure``

2. Build the project. The output is in the "Debug" folder. 

``inv all``

3. Now you can flash you board with your favorit flash tool. We use the ST-Link Utility for that.


As a short form you can also use:

``inv clean_all configure all``

If you do not like the python way you can also build it by hand use this as a starting point.

Use `` mkdir Debug`` then ``cd Debug`` into the Debug folder. After that generate the makefile with:

``cmake.exe -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DTOOLCHAIN_PREFIX="c:/Program Files (x86)/GNU Tools ARM Embedded/4.9 2015q1" -G"MinGW Makefiles" -C ../build_settings.cmake -DCMAKE_BUILD_TYPE=Debug .. ``

Now make the program use the make.exe from the build tools:

``"c:\\Program Files\\GNU ARM Eclipse\\Build Tools\\2.6-201507152002\\bin\\make.exe" all`` 

##### Import into Eclipse

At this point it is possible to import the project into the GNU MCU Eclipse Toolchain you have installed at the beginning. But you must modify the Build Command. So navigate to properties and change the path at C/C++ Build, Builder Settings, Build command.

