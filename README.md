# miko
Miko assignment

//////////////////////////////////////////////////
In the program the following assumtions are made
///////////////////////////////////////////////////////
for the ease of progarmming the map boundaries are considered between (-10,-10) and (10,10) instead of (-1,-1) & (1,1)
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




![visualization](https://user-images.githubusercontent.com/109422653/179357275-d6a1e3da-745a-41de-9e77-9a3bc992e408.png)
