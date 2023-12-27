# Procedural 2D Dungeon Generation

## Overview ##
The Dungeon Generation Algorithm takes inspiration from probability theory to introduce an element of unpredictability and complexity into your dungeon environments. By leveraging probabilistic principles, I have crafted a tool that goes beyond traditional methods, offering a dynamic and ever-changing canvas for game worlds.

My project has been created with the C++ Win32 Engine developed by my teacher at University of Applied Science Howest.

I am also using a small visual techique to show that all the room and corridors in the dungeon are walkable by adding enter and exit points to my visual representation.

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

9.Add the enter and exit at random points in map

# Step by step explanation #

0. I have added zero step to my explanation to explain my useful file structure. 
![image](https://github.com/cinnaamonka/GenerateDungeon/assets/107621519/93698857-f383-4485-a03d-899c744a5067)



