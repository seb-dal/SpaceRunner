# MIF27 Projet: Runner

## Contribution
 - DALVERNY Sébastien


## Install And Compile Project
Put the runner directory into gkit2light directory.  
Then:   
 - add `include "runner"` into premake4.lua of gkit2light and then use premake.  
   
Use your IDE to compile the project.  


## Play
- use 'q' or left keys to rotate to the left and 'd' or right keys to rotate to th right.  
- you start with 3 health points and you loss one each time you touch one of the Red Obstacle.  
- you can gain new Health points up to 5 Health points by collecting 100 bonus Box.  
- the Goal is to have the hightest score possible.  
    * `1` point per ms alive.  
    * `250` points for collecting 1 Bonus Box.  
    * `200` points for each 20 ms close to an Obstacle.  
    * `-1000` points when hitting an Obstacle.  
    * `100 000` points if you manage to collecting 100 Bonus Box will having 5 health points.  
    
    
# Have Fun  
