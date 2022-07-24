#include <iostream>
#include <cmath>
using namespace std;
#include <vector>
#include <algorithm>

#include <iterator> 
#include <map> 

// struct ObstacleCenters
// {
//     int x, y;
// };
struct Points
{
    int x, y;
};

// int a,b,c,x,y,dist;

bool checkCollision(int line[], Points& center, int& radius)
{
    
    int a,b,c,x,y,dist;
    a = line[0];
    b = line[1];
    c = line[2];
    x = center.x;
    y = center.y;
    dist = ((abs(a * x + b * y + c)) /
            sqrt(a * a + b * b));
    if (radius > dist)
        return true;
    return false; 

}


float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}



int main()
{
// vector<ObstacleCenters> ocs = {{0,0},{-3, 5},{4, 6},{6, -7},{-8, -7}};
vector<int> moving_cumulative_distance_list;
vector<int> distance_between_poses;
int moving_cumulative_distance;
map<string, Points> data_structure;


int radius[] = { 1, 2, 2, 1, 2};
vector<Points> obstacleCenters ={{0,0},{-3, 5},{4, 6},{6, -7},{-8, -7}};

vector<Points> obstacles;
Points initialPose{-10,-10};
int x,y,r;
vector<Points>poses;
srand((unsigned int)time(NULL));


/////////////////////////populateObstacles/////////////
// for (auto i : obstacleCenters)
//     // obstacles.push_back(i);
//     cout<<i<<endl;
// cout << '\n'; 
    
for (int i = 0; i <obstacleCenters.size() ; i++) {
    int x = obstacleCenters[i].x;
    int y = obstacleCenters[i].y;
    int r = radius[i];
    
    for (int j = 0; j < (r+1); j++) {
        obstacles.push_back({x + j, y});
        obstacles.push_back({x - j, y});
        
        obstacles.push_back({x, y + j});
        obstacles.push_back({x, y - j});
        
        obstacles.push_back({x + r, y + j});
        obstacles.push_back({x + r, y - j});
        obstacles.push_back({x - r, y + j});
        obstacles.push_back({x - r, y - j});

        obstacles.push_back({x - j, y + r});
        obstacles.push_back({x + j, y + r});
        obstacles.push_back({x + j, y - r});
        obstacles.push_back({x - j, y - r});

        obstacles.push_back({x + j, y + j});
        obstacles.push_back({x - j, y - j});
        obstacles.push_back({x + j, y - j});
        obstacles.push_back({x - j, y + r});
    }
    
    
  } 
    
// cout<<"size of obstacles "<<obstacles.size() <<endl; 
// for (auto i : obstacles)

//     cout <<" ox:"<< i.x <<" oy:"<<i.y<<endl;   

    
int count=0;
      
//  /////////////////////////update robot pose/////////////
vector<Points> outPoses;

for (int i = 0; i < 10; i++) {
  vector<Points> possibleStates;
  int stepSize = 1;
  Points updatedState;
  int line[3];

  vector<Points> possibleStatesTemp;
  vector<Points> obstaclesTemp;
  int a,b,c;
  
  //int updatedState = 0;
  for (int i = -10; i < 11; i++) {
     for (int j = -10; j < 11; j++) {
        // if i,j is prenent in obstacles
            auto pred = [i,j](const Points & item) {
            return item.x == i,item.y == j;
            };
             //cout<<(std::find_if(std::begin(obstacles), std::end(obstacles), pred) != std::end(obstacles))<<endl;
            if (std::find_if(std::begin(obstacles), std::end(obstacles), pred) != std::end(obstacles)){
                possibleStates.push_back({i,j});
            }
            
         }
         
     }  
//   for (auto i : possibleStates)
//      cout <<"x:"<< i.x <<"y:"<<i.y<<endl;  
   possibleStatesTemp = possibleStates;
   obstaclesTemp = obstacles;   
   //cout << obstacles.size()<<endl;
   for (auto i : obstacles){
       if (distance(i.x , i.y, initialPose.x, initialPose.y) > stepSize)
       {
       obstaclesTemp.erase(std::remove_if(obstaclesTemp.begin(), obstaclesTemp.end(), [&](Points const & item) {
            return item.x == i.x, item.y == i.y;
        }),obstaclesTemp.end());
           
       }
   }
    //  cout <<"size of possibleStates before:  "<< possibleStates.size() <<endl; 
   
  for (auto i : possibleStatesTemp){
      if (distance(i.x , i.y, initialPose.x, initialPose.y) > stepSize)
      {
      possibleStates.erase(std::remove_if(possibleStates.begin(), possibleStates.end(), [&](Points const & item) {
            return item.x == i.x,item.y == i.y;
        }),possibleStates.end());
           
      }
  }
   
    //  cout <<"size of possibleStates after:  "<< possibleStates.size() <<endl; 

   possibleStatesTemp = possibleStates;
   for (auto i : possibleStatesTemp){
       for (auto j : obstaclesTemp){
    //  cout <<"x:"<< i.x <<"y:"<<i.y<<endl; 
    //  cout <<"x:"<< j.x <<"y:"<<j.y<<endl; 
       
       
       if (i.x == j.x , i.y ==j.y )
       {
        possibleStates.erase(std::remove_if(possibleStates.begin(), possibleStates.end(), [&](Points const & item) {
            return item.x == i.x && item.y == i.y;
        }),possibleStates.end());
        
        break;   
       }
       }
   }

//   for (auto i : possibleStates)                  ///no element in possibleStates?
//      cout <<"x:"<< i.x <<"y:"<<i.y<<endl; 


   possibleStatesTemp = possibleStates;
   ///////////////////////////
   for (auto i : possibleStatesTemp){
       if (i.x == initialPose.x || i.y ==initialPose.y )
       {
           break;
       }   
       else {    

       if ((i.x != initialPose.x) && (i.y != initialPose.y)) 
       {
        a = initialPose.y - i.y;
        b = i.x  - initialPose.x; 
        c = a*(i.x) + b*(i.y);
        int line[] = {a,b,c};    
        
        int z=0;   
        for (auto j : obstacleCenters){
        if (distance(j.x,j.y,initialPose.x,initialPose.y) < stepSize){
            
            if (checkCollision(line, j, radius[z]))  {
       
                possibleStates.erase(std::remove_if(possibleStates.begin(), possibleStates.end(), [&](Points const & item) {
                    return item.x == i.x,item.y == i.y;
                }),possibleStates.end());
        
                break; 
   
            }
        z=z+1;
          }    
        }
       }

        }


      
    }
   
//   possibleStates = list(possibleStates)?

   updatedState = possibleStates[rand() % possibleStates.size()];
//   cout <<"x:"<< updatedState.x <<"y:"<<updatedState.y<<endl;  

   initialPose = updatedState;
   outPoses.push_back(updatedState);
  }
 for (auto i : outPoses)
    cout <<"x:"<< i.x <<"y:"<<i.y<<endl;     
 poses = outPoses;
 
 
 
 
 moving_cumulative_distance = 0;
 
 for (int i=0; i<poses.size();i++)
 {
     int d = distance(poses[i].x , poses[i].y, poses[i+1].x , poses[i+1].y);
     distance_between_poses.push_back(d); 
     
     moving_cumulative_distance = moving_cumulative_distance + distance(poses[i].x , poses[i].y, poses[i+1].x , poses[i+1].y);
     moving_cumulative_distance_list.push_back(moving_cumulative_distance);
     

 }
 
 
//  moving_cumulative_distance[0];
 
// int f =0; 
// for (auto i : poses)
//     //  data_structure = {{"waypoint", i}, {"parent", i},{"moving_cumulative_distance", moving_cumulative_distance_list[f]}};
//      data_structure = {{"waypoint", i}, {"parent", i}};

//      f = f + 1;
return 0;
}



























