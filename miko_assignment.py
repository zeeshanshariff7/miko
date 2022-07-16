import matplotlib.pyplot as plt
import math
import random

fig, ax = plt.subplots()
##global cumulative_distance = 0
def populateObstacles(obstacleCenters, obsRadius, obstacles):
    obs1 = plt.Circle(obstacleCenters[0], obsRadius[0], color='r', fill=False)
    obs2 = plt.Circle(obstacleCenters[1], obsRadius[1], color='r', fill=False)
    obs3 = plt.Circle(obstacleCenters[2], obsRadius[2], color='r', fill=False)
    obs4 = plt.Circle(obstacleCenters[3], obsRadius[3], color='r', fill=False)
    obs5 = plt.Circle(obstacleCenters[4], obsRadius[4], color='r', fill=False)

    ax.add_patch(obs1)
    ax.add_patch(obs2)
    ax.add_patch(obs3)
    ax.add_patch(obs4)
    ax.add_patch(obs5)

    for i in obstacleCenters:
        obstacles.append(i)
    
    for i in range(len(obstacleCenters)):
        x = obstacleCenters[i][0]
        y = obstacleCenters[i][1]
        r = obsRadius[i]
        for j in range(r+1):
            obstacles.append((x + j, y))
            obstacles.append((x - j, y))

            obstacles.append((x, y + j))
            obstacles.append((x, y - j))

            obstacles.append((x + r, y + j))
            obstacles.append((x + r, y - j))
            obstacles.append((x - r, y + j))
            obstacles.append((x - r, y - j))

            obstacles.append((x - j, y + r))
            obstacles.append((x + j, y + r))
            obstacles.append((x + j, y - r))
            obstacles.append((x - j, y - r))

            #obstacles.append((x - j, y + j))
            #obstacles.append((x - j, y + j))

            obstacles.append((x + j, y + j))
            obstacles.append((x - j, y - j))
            obstacles.append((x + j, y - j))
            obstacles.append((x - j, y + j))   
                 

def getLineCoefs(p1, p2):
    if p1[0] != p2[0] and p1[1] != p2[1]:
        a = p2[1] - p1[1]
        b = p1[0] - p2[0]
        c = a*(p1[0]) + b*(p1[1])
        return [a,b,c]
    return 0

def checkCollision(line, center, radius):
    a = line[0]
    b = line[1]
    c = line[2]
    x = center[0]
    y = center[1]
    dist = ((abs(a * x + b * y + c)) /
            math.sqrt(a * a + b * b))
    if radius > dist:
        return True
    return False

#def plotRobot(pos):
#    robotRadius = 0.2
#    robot = plt.Circle(pos, robotRadius, color='blue', fill=True)
#    ax.add_patch(robot)

def getDistance(p1, p2):
    return math.dist(p1, p2)

def updateRobotPose(obstacleCenters, obsRadius, obstacles, initialPose):
    outPoses = []
    for m in range(10):
        plt.scatter(initialPose[0], initialPose[1], c='b')
        possibleStates = []
        stepSize = 5
        updatedState = 0
        for i in range(-10, 11, 1):
            for j in range(-10, 11, 1):
                if (i,j) not in obstacles:
                    possibleStates.append((i,j))
        
        possibleStates = set(possibleStates)
        obstacles = set(obstacles)
        possibleStatesTemp = possibleStates.copy()
        obstaclesTemp = obstacles.copy()

        for i in obstacles:
            if getDistance(i, initialPose) > stepSize:
                obstaclesTemp.remove(i)
        
        for i in possibleStatesTemp:
            if getDistance(i, initialPose) != stepSize:
                possibleStates.remove(i)

        possibleStatesTemp = possibleStates.copy()
        for i in possibleStatesTemp:
            for j in obstaclesTemp:
                if i[0] == j[0] or i[1] == j[1]:
                    possibleStates.remove(i)
                    break
        
        possibleStatesTemp = possibleStates.copy()
        for i in possibleStatesTemp:
            if i[0] == initialPose[0] or i[1] == initialPose[1]:
                break
            else:
                line = getLineCoefs(i, initialPose)
                for j in range(len(obstacleCenters)):
                    if getDistance(obstacleCenters[j], initialPose) < stepSize:
                        if checkCollision(line, obstacleCenters[j], obsRadius[j]):
                            possibleStates.remove(i)
                            break
        possibleStates = list(possibleStates)
        updatedState = random.choice(possibleStates)
        initialPose = updatedState
        ##cumulative_distance = cumulative_distance + getDistance(updatedState, initialPose)

        outPoses.append(updatedState)
    return outPoses

if __name__ == "__main__":
    obstacleCenters = [(0,0), (-3, 5), (4, 6), (6, -7), (-8, -7)]
    obsRadius = [1, 2, 2, 1, 2]
    obstacles = []
    moving_cumulative_distance_list = []
    populateObstacles(obstacleCenters, obsRadius, obstacles)
    initialPose = (-10, -10)
    poses = updateRobotPose(obstacleCenters, obsRadius, obstacles, initialPose)
    print(poses)
    distance_between_poses = [getDistance(poses[i+1],poses[i]) for i in range(len(poses)-1)]
    print(distance_between_poses)
    print(sum(distance_between_poses))
    
    moving_cumulative_distance = 0
 
    for i in range(0, len(poses)-1):
        moving_cumulative_distance = moving_cumulative_distance + getDistance(poses[i+1],poses[i]) 
        ##print("moving_cumulative_distance: ", moving_cumulative_distance)
        moving_cumulative_distance_list.append(moving_cumulative_distance)
        ##print("moving_cumulative_distance_list: ", moving_cumulative_distance_list)


    for i in range(0, len(poses)-1):
        ##print("waypoint:",i,poses[i],"parent:",poses[i-1],"moving_cumulative_distance",moving_cumulative_distance_list[i])

        data_structure ={"waypoint": poses[i], "parent": poses[i-1],"moving_cumulative_distance": moving_cumulative_distance_list[i]}
        print (data_structure)
    for i in poses:
        
        plt.scatter(i[0], i[1], c='blue')
    ax.plot()
    plt.show()
