# Procedural 2D Dungeon Generation

## Overview ##
The Dungeon Generation Algorithm takes inspiration from probability theory to introduce an element of unpredictability and complexity into your dungeon environments. By leveraging probabilistic principles, I have crafted a tool that goes beyond traditional methods, offering a dynamic and ever-changing canvas for game worlds.

My project has been created with the C++ Win32 Engine developed by my teacher at University of Applied Science Howest.
The algorithm is inspired by Tyrant's technique, this strategic selection maintains both aesthetic coherence and equal probability distribution for a balanced and elegant dungeon generation. Also the RNG algorithm as a method of generating numerical values that are unpredictable and lacking in any sort of pattern.

I am also using a small visual techique to show that all the room and corridors in the dungeon are walkable by adding enter and exit stairs to my visual representation.

## Key Features ##

-Probabilistic Room Placement: Utilize probability distributions to determine where rooms are likely to appear within the dungeon, creating diverse and unpredictable spatial arrangements.

-Adaptive Corridor Generation: Apply probability-based decisions to the formation of corridors, introducing organic connections between rooms with varying likelihoods.

-Feature-Rich Dungeons: Employ probability to generate dungeon features. For now there are only rooms and corridors, but also some hidded paths or treasure rooms can be added to the dungeon.

-Flexible Room Characteristics: Use probability distributions to influence the size and shape of rooms, resulting in visually engaging layouts with a mix of large and small spaces.

-Grid-Based Activation: Implement probability-based activation of tiles or cells in grid-based systems.

## Final Result ##

https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/dc00be95-935d-4f12-954e-cca6da6e3463

## The algorithm ##

Overview
In this algorithm, a "feature" refers to any type of map component, such as a large room, small room, corridor, circular arena, vault, and more.

1.Fill the whole map with solid earth

2.Dig out a single room in the centre of the map

3.Pick a wall of any room

4.Decide upon a new feature to build

5.See if there is room to add the new feature through the chosen wall

6.If yes, continue. If no, go back to step 3

7.Add the feature through the chosen wall

8.Go back to step 3, until the dungeon is complete

9.Add the enter and exit stairs at random points in map

# Step by step explanation #

# Step 0 #
I have added zero step to my explanation to show my useful file structure. I have added enums with types of tiles and types of directions into different file for convenience.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/6450fb17-c919-406f-8f70-3895e6481e79)

# Step 1-2 #
In the first and second steps I am filling the map using FillRect function and choosing randomly a place to put the first room.

![FirstRoom](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/1e0f80d9-0ea5-4c5b-9d64-0393bbc053ae)

# Step 3 #
Rather than randomly selecting squares for new features, our algorithm follows a deliberate approach. Algorithm searches for the next place to fill with walkable tile.

a) If current cell is not a floor of a corridor, we can make feature here.

b) If cell above is floor or corridor we will build a feature from the northern wall of the existing room.

c) If cell to the right is floor or corridor we will build a feature from the western wall of the existing room.

d) If cell to the left is floor or corridor we will build a feature from the eastern wall of the existing room.

e) If cell below is floor or corridor we will build a feature from the southern wall of the existing room.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/0f680bdb-0c3f-419b-a4c7-7c3859b37752)

# Step 4 #
Let's decide which feature to build. It is just the random probability between 0 and 100. We choose which feature to build just comparing this probability with weights of probabilities of different features.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/ac52897e-22d1-4f0c-9ad3-642cc10bc11f)

# Step 5 #
Then we need to check if the area which is occupied by the feature is unused. This step is done before the drawing part and this part of algorith is shown below. I am checking if all the room's cells are unused and then I build a feature.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/679c4377-4cca-45ec-b640-c661508718dd)

# Step 6 #
Then we decides whether or not to add the feature. If the area under consideration contains anything other than solid earth already, then the routine loops back to step 3.

# Step 7-8 #
Algorithm just loops back to build more rooms. The exact number of times that you want to do this will depend on map size and various other factors.
   
![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/ef5da565-501b-4d65-9147-eac485b12679)

# Step 9 #
When all the features are added we colorize the last two unused tiles as enter and exit cells to show that all rooms and corridors are walkable.
    
![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/345a39a6-bd42-4276-8997-dcdb3d6c8aa2)

## UI ##

**Max features input field**: Input field that will determine how many features will be implemented, including rooms and corridors. 

**Max chance rooms input field** : Input field which determines what is the chance that the algorithm will draw a room. 

**Max chance corridors** : Also just a probability which determaines what is the chance that the algorithm will draw a corridor. It is not an input field, it is calculated 100 - maxChanceRooms

**Generate Dungeon Button** : If button is pressed, the new dungeon with new random seed is generated.

Also I provide the keys to play with the algorithm:

**P Key** : Pause  the proccess

**Left arrow** : If the process is paused, we can walk to the previous step of the algorithm with left arrow key

**Right arrow** : If the process is paused, we can walk to the next step of the algorithm with right arrow key

**Up arrow** : We can increase the speed of the algorithm

**Down Arrow** : We can decrease the speed of the algorithm

## First versions of algorithm ##

I have really enjoyed working on this algorithm. It was the first time I encounter the task like this so I have started with simpler versions of this algorithm. I would like also to show this.

This is the first and fast implementation. Imagine you have a grid like a big game board, and you want to make a path on it. The GetRandomDirection function helps you decide which way to go—up, down, left, or right.

Here's how it works:

a)Find the Center: You figure out where the center of your game board is.

b)Calculate Weights: You use a special formula to decide how likely it is to go in each direction based on how far you are from the center. Closer directions get higher chances.

c)Pick a Direction: Now, you pick a direction randomly, but it's more likely to be the one with the higher chance.

The MakePath function uses this direction to move around the game board. It starts somewhere, and for each step, it randomly chooses a direction and moves that way. As it moves, it changes the color of the cells it passes through to show the path.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/7336e500-a0f5-40d0-810b-72be9ede03b8)


Then I have added more interesting logic but this time I have't implemented any visual logic, so the dungeon looked like this. The algorithm used here almost the same as the one i have presented above but without visual representation.

![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/cc87239d-4283-4411-8816-1c8d9de83140)

## Conclusion ##
Expanding the scope of the project is feasible, as it could be transformed into a 3D dungeon generator compatible with a 3D game engine. This enhancement would empower game designers to craft complex dungeons spanning multiple levels.

To sum up, by undergoing further refinement and optimization, the 2D Dungeon Generator has the potential to metamorphose into an even more formidable tool for game designers, amplifying its effectiveness and versatility in shaping immersive game environments.


## Resources ##

https://www.roguebasin.com/index.php/Dungeon-Building_Algorithm
https://www.roguebasin.com/index.php/C%2B%2B_Example_of_Dungeon-Building_Algorithm
https://www.roguebasin.com/index.php/Random_number_generator
/https://www.cs.cmu.edu/~112/notes/student-tp-guides/Mazes.pdf
