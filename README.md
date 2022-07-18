# miko
Miko assignment

//////////////////////////////////////////////////
In the program the following assumtions are made
///////////////////////////////////////////////////////
1. for the ease of progarmming the map boundaries are considered between (-10,-10) and (10,10) instead of (-1,-1) & (1,1)
2. the robot will run for 10 steps to explore the environment(increasing the number of steps will converge to explore of entire space )
each time the script generates a new path.
///////////////////////////////////////////////////////////////////////
*functions used
///////////////////////////////////////////////////////////////////////
1.populateObstacles : populates the obstacles list in and around the obstacleCenters with respect to obsRadius


2. getLineCoefs      : to get the line coefiecient

3. checkCollision     : checks for collision with the obstacles

4. getDistance      : to get distance between 2 points

5. updateRobotPose   : 

i.It collects  possibleStates from which are not in populated obstacles list

ii. Then eliminates obstacles and poses w.r.t step size

iii. then it checks for possibleStates by avoiding obstacles within the step size  and update new robot pose

////////////////////////////////////////////////////////////////////////////////////////////////////

cumulative distance is stored in moving_cumulative_distance_list
dictionarry is used as a dsta structure to wapoint, parent and cumulative distance for each waypoint
/////////////////////////////////////////////////////////////////////////

This plot shows the sequnce of waypoint generated and the terminal prints out the wapoint, its parent and the cumulative distance for eac waypoint

![visualization](https://user-images.githubusercontent.com/109422653/179357275-d6a1e3da-745a-41de-9e77-9a3bc992e408.png)


