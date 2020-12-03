
# Jerry Knoch Transit Simulation


![](bus_sim_demo.gif)


### Introduction
 The system that we have designed and built is meant to replicate the
 real-world scenarios involved with using public transportation, and
 in particular for this program, a public bus. The system simulates the
 the four major 'players' involved in this real-world scenario which are
 buses, routes, stops, and passengers. Our simulation uses the University 
 of Minnesota's transit routes, but we have the ability for the user to 
 provide the program with their own routes and stops. We shall begin the 
 process of describing how to get started with the program and how to input 
 your own information to be used by the simulator. 

### Getting Started
One of the main assumptions for using this application is that the user has
access to a CSELABS computer provided by the University of Minnesota. This is
to the web graphics being native to the CSELABS machines. This can be accomplished 
by either logging into a CSELABS machine in person on campus. Otherwise, the 
user may access a CSELABS machine by using VOLE or SSH which are essentially 
accessing a CSELABS computer through the internet on their own computer. Once
the user has accessed one of these machines we can begin the process of downloading
the program onto your computer.

We will be using what is called the command line, or terminal to run the
simulation. So, by using the application finder, we can type "terminal" into
the finder to open the terminal. With the terminal open, you should be able
 to see that the terminal displays something similar to: 

 		user099@csel-vole-09:/home/user099

The user099@csel-vole-09 is telling us the name of the user accessing the machine.
The information after the ':' is listing the folder hierarchy. So in our example, the root,
or base folder is /home/ and up one folder level from that is user099, which
we are currently in. The commands needed to navigate through
the directories/folders can be condensed down to:


 		1) "cd <directory_name>" : the "cd" command is used to change directories.

 		2) "ls" : the "ls" command is used to display the files and folders located
    	    in the current directory/folder.
 

We can use the "ls" command to see what directories we can switch into and 
then use the "cd <directory_name>" to actually move into those directories.
These two commands are the fundamental commands for navigating through the 
folder directories successfully. Note: say that you are in a folder, but you
want to go back one level in the directory, the command is "cd ..". This 
command will take you back to the previous directory. For example, we are
in the /user099 directory and we want to go back one level to the /home 
directory. The way to achieve this is by using "cd .." and the terminal 
would change from "user099@csel-vole-09:/home/user099 $ " to
"user099@csel-vole-09:/home $ ". Then to go back up to the user099 
directory, we would use "cd user099" which would get us back to the 
original terminal output of "user099@csel-vole-09:/home/user099 $ ".
The last command needed is the "mkdir <directory_name>" which we will
use to create a new folder/directory in which we will clone the program
into.
 
Where you create the directory to clone the repository is up to you.
navigate to the directory of your choosing by using the "cd" and "ls"
commands. Once you are in the desired directory, use the "mkdir" command
along with a name for the new folder/directory. Now, "cd" into the
directory that you just made and use the command:

 		git clone https://github.com/KnochJ/bus-sim.git

This command will clone the project from github onto your local machine.
Now you can navigate through the project folders and see the contents that
are inside.

With the repository successfully cloned, we can begin discussing how to 
actually build and run the simulator. The first thing we need to do is
build the files necessary for executed the program. This is achieved by
the "make" command. It is important the we run this command from the source
directory of the project. Wherever you decided to make your directory via
the "mkdir <name>" command, you should then us the command "cd bus-sim".
The name "bus-sim" corresponds to the repository where the program 
is located. So once you change directories into the repository we will again
use the command "cd project" to switch into the project directory and finally
"cd src" to change into the source files of the program.
 
Now that we are ready to make the files necessary to run the simulation, we can discuss
the different options that the program offers. The first option for running the simulator
is by using the visualizer simulator, which utilizes graphics to display information. 
The current implementation uses the University of Minnesota map and routes.The second way
to run the simulator is by providing the simulator a configuration file that basically
allows you to custom-build the stops and routes you want to use. 
 
So, the first step in running these simulators is to run the "make" command from the 
/project/src directory. We have three different options when making and executing:
 			
 1)	Making just the visualizer simulator:
			
			<port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.

			Navigate to base project directory(project/)
			Make and start server:
			
			$ cd src
			$ make vis_sim
			$ cd ..
			$./build/bin/vis_sim <port_number>
			
			You must run by doing ./build/bin/vis_sim <port_number>.
			
 	NOTE: You cannot cd to bin/ and run ./vis_sim <port_number>

			Navigate to the following address on your browser (Firefox/Chrome):
			
			http://127.0.0.1:<port_number>/web_graphics/project.html



After inputting these commands into the command line you should see a prompt like this:


 		Usage: ./build/bin/ExampleServer <port number>
 		Using default config file: config.txt
 		starting server...

Once you have opened the correct URL with the port number you chose, there are options displayed 
on the left-hand-side of the screen. The number of steps is listed and you can use the sliding bar
to increase or decrease the length of the simulation. The sliding bar below that corresponds to 
how many time updates happen before a bus is generated on the screen. You can increase or decrease
the frequency using the sliding bar. Once you have determined those values, you can simply click the
"Start" button and the simulation will run with a graphical representation. You can use your mouse to
scroll over the stops and buses to see how many passengers are either waiting, or riding the bus.
 


 2) 	Making just the configuration simulator:

			Navigate to base project directory(project/)
			
			$ cd src
			$ make config_sim
			$ cd ..
			$./build/bin/config_sim

 
The configuration simulator comes allows some flexibility in how it  is run. You can use 
the command listed above: $./build/bin/config_sim, to simply use the default configuration
text file that is located in the /project/config. But, you also have the option of using your
own text file by instead of running the last command above, you can instead run:

			$./build/bin/config_sim <config_filename>

Where the <config_filename> is the specific filename you provide. Lastly, the configuration file allows
the user to input the number of rounds which corresponds to how long they want the simulation to last.
The default setting is 25 rounds, but can be manually inputted by running the command:
 
 			$./build/bin/config_sim <config_filename> <number_rounds>


Where <number_rounds> corresponds to how long you want the simulation to run for.


To utilize your own configuration files with your own data, you can look to an example located in the 
/projects/config directory. Inside the config directory there exists and file name "config.txt".
The information in this file is describing an inbound and an outbound route and the stops that reside
along these routes. Looking at the default configuration file:


			ROUTE_GENERAL, Campus Connector

			Stop Name, Long, Lat, Pass Gen Prob
 
			ROUTE, East Bound

			STOP, Blegen Hall, 44.972392, -93.243774, .15
			STOP, Coffman, 44.973580, -93.235071, .3
			STOP, Oak Street at University Avenue, 44.975392, -93.226632, .025
			STOP, Transitway at 23rd Avenue SE, 44.975837, -93.222174, .05
			STOP, Transitway at Commonwealth Avenue, 44.980753, -93.180669, .05
			STOP, State Fairgrounds Lot S-108, 44.983375, -93.178810, .01
			STOP, Buford at Gortner Avenue, 44.984540, -93.181692, .01
			STOP, St. Paul Student Center, 44.984630, -93.186352, 0

			ROUTE, West Bound

			STOP, St. Paul Student Center, 44.984630, -93.186352, .35
			STOP, Buford at Gortner Avenue, 44.984482, -93.181657, .05
			STOP, State Fairgrounds Lot S-108, 44.983703, -93.178846, .01
			STOP, Transitway at Commonwealth Avenue, 44.980663, -93.180808, .01
			STOP, Thompson Center & 23rd Avenue SE, 44.976397, -93.221801, .025
			STOP, Ridder Arena, 44.978058, -93.229176, .05
			STOP, Pleasant Street at Jones-Eddy Circle, 44.978366, -93.236038, .1
			STOP, Bruininks Hall, 44.974549, -93.236927, .3
			STOP, Blegen Hall, 44.972638, -93.243591, 0

 
You may use this as a guide to create your own routes with stops. The first line describes name for the
route. The next line describes the attributes of a stop, which consists of: a name, longitude and latitude
coordinate, and probability to generate a passenger. Listed below the line that says ROUTE, East Bound are 
all the corresponding stops on the outbound route for the campus connector. Below those stops are the inbound
route for the campus connector. You must be sure to provide all the attributes for a stop otherwise the 
simulation may give default values to these attributes. The format for the stop should always be as follows:

			STOP, name_of_stop, longitude, latitude, passenger_probability

 

 3) 	Making BOTH config_sim and vis_sim at once:

			Navigate to base project directory(project/)

			make

	In this case, both files have been built and you can use either of the commands
 	listed in options 1 and 2 above to run either the visualizer or configuration simulator. 

			$./build/bin/vis_sim <port_number>
		
 			or

			$./build/bin/config_sim <config_file> <number_of_rounds>

 
If at any time you wish to use a different configuration file, you must cleanup the previous build of the
simulation. This can be done by navigating back to the project folder (/project) and typing the command:

			make clean
 
This command will clear the previous build and you can go back to the steps listed for making the configuration
simulator in part 2) and use a different configuration file.
 


### Developer Guide Introduction
The four major objects in the system are Passengers, Routes, Stops, and 
Buses. Much of the design for this system stems from the question of who 
will be responsible for loading and unloading passengers, and in what order
do all of the objects need to be updated? The way time is kept during the 
simulation is that there is a time step that keeps track of how long the
simulation has been running and updating. At every time step, there is a
cascading effect of updating each of the four objects. This needs to be kept 
track of since we will get undesirable results if we have multiple passenger
updates happening in a single timestep. The simulation currently has two versions
that can be run. First the configuration simulator which takes in a user defined 
.txt file which describes a custom made route. An example of the default config.txt
file can be found above in the user guide, or in th /project/config directory.
 

The program was developed independently of the graphical representation of
the simulator. This allows us to focus on developing the core classes that 
make up the system and ensure that they are reasonably complete and correct.
The graphical representation of the simulator utilizes our program and we 
are not concerned with how the visualizer simulator achieves this. We allow 
the ability for the program to be run either through the visualizer simulator,
or by using the configuration simulator.

### Setup
Repository URL: https://github.com/KnochJ/bus-sim
After creating a directory and cloning the repository, a UML diagram
associated with the design can be found in the project/docs/ directory.
Using this as an aid while reading through this guide can assist in understanding
the flow of the system.

The two versions of the simulation that can be built are described in the 
user guide. A quick-start for building these files can be done making from 
the source(/src) directory. While we need to build from here, we need to run
the executables from the project directory otherwise the configuration
simulator does not have access to the /config directory. As such, the web based 
graphics also need to be executed from the project folder. The user guide has
an in-depth description of what needs to be included when executing the simulation.

## Object Design

 
### Passengers 
The passenger class is a simple class that forms a base for the design in
the system. Passengers will belong to the objects that they are currently 
in. This means that if a passenger is riding a bus, it belongs to a bus. 
Stops are the other object that have passengers. The passenger class does
not have any references to the other objects. As updates are made to, 
the passengers have attributes to keep track of how long they have been
waiting at a stop, riding a bus, and a total wait time in the simulation.


### Stops
Stops are the class that make up a route. A stop knows about passengers since
a passenger will be generated by the PassengerGenerator and be placed at the 
stop. When a Stop is called by its Route to update, the Stop will call update 
on the passengers it knows about. The Stop aids the Bus in unloading passengers,
but this is described in greater detail in the Bus section.
   

### Route
A Route is composed of an outgoing route and an incoming route. A Route 
is an aggregation of stops. Route has a list of stops and also a
corresponding list of distances between those stops. This is all the route
needs to know about. After the Route has updated its stop, the last responsibility
of the class is to call PassengerGenerator to create passengers and add them to
the Route's stops. 


### Bus
The way that the Bus class was designed, the Bus knows about the other three
classes: Passenger,Stops, and Routes. It makes sense for a Bus to know about
its route and the passengers riding it. The decision to have Bus also know 
about Stop was due to the way loading and unloading was going to be handled.
Buses have the responsibility for loading and unloading passengers. The Bus 
is aided by the Stop in loading passengers, but this is due to the way the 
bus gets a Stop pointer which then allows it to call Stop to load passengers
by passing the Bus itself to Stop. This allows the Stop to then iterate through
its passenger list and one-by-one give the Bus its passengers. Unloading for the 
Bus is much simpler since we once again, use the Stop pointer to determine if
passengers on the bus need to get off at the given Stop. When a passenger is 
unloaded, they are simply removed from the Bus' passenger list. For our purposes,
this works since once a passenger unloads, we don't have to keep track of it
anymore.

### Data Structs
Utilized by the visualizer simulator are the data structs that contain information
about the Bus, Route, and Stop objects. This is the entry point for the visualizer
to gain access to the information about the objects and project their data with
a graphical representation. Buses populate the bus struct with their information
such as their name and the number of passengers currently riding. Routes take 
care of populating the route structs as well as the stop structs.
Specific information about the passengers is not required currently. 

### System Ordering
The system starts with the Simulator which has the Local_Simulator to start
the simulation and begin creating the Stops, PassengerGenerators, and Routes.
Once the local_simulator begins Updating the Buses will be created. The 
Local_Simulator then begins to update the buses and the routes. When a bus
is updated the ordering is that they will move, unload passengers, load 
passengers, and then update the passengers still belonging to them. After the
bus has been called to update and in turn, the passengers belonging to the bus,
the Routes are then called to update. The Route makes calls to the Stops that it
is made up of and lastly, the passengers belonging to the Stop are updated. Keeping 
this flow ordering in mind is important as the updates cascade down to the passengers
at the very bottom. Care is taken to not accidentally increment a passenger more than
once during a timestep by keeping this flow ordering in mind.
 

### Extending/Adapting
The system was designed in mind to have high cohesion and low coupling. For the most part,
many objects in the system can be altered with minimal cascading results. One aspect of the 
system that may difficulties being altered is how buses and stops load and unload passengers.
More than likely there exists a more efficient way to unload and load and in particular, the way 
passengers are handled after they are unloaded. Currently, they are simply deleted and not kept
track of. In an ideal scenario, we would keep track of them, since the same passenger could come
back after some time and reappear at the stop and return to their original point of embarking. Or, 
maybe someone is running errands and will have multiple bus rides during a simulation. If those types 
of scenarios are to be implemented, then that issue must be handled. If one were to refactor large 
portions of the system, the main point to keep intact is that routes are made up of stops. Other 
options for handling the loading and unloading of the passengers could be taken on by a new class 
such as a PassengerUnloader and PassengerLoader. This could relax the responsibilities placed on the
bus class and allow further depth of the simulation such as keeping track of fuel, or amount of money
collected by passengers riding a bus. There are many options for a developer to expand upon the current 
system.



 @copyright 2019 3081 Staff, All rights reserved.