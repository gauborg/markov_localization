// Initialize prior probabilities
/*

To help develop an intuition for this filter and prepare for later coding exercises, let's walk through the process of initializing our prior belief state.
That is, what values should our initial belief state take for each possible position? Let's say we have a 1D map extending from 0 to 25 meters.
We have landmarks at x = 5.0, 10.0, and 20.0 meters, with position standard deviation of 1.0 meter.
If we know that our car's initial position is at one of these three landmarks, how should we define our initial belief state?
Since we know that we are parked next to a landmark, we can set our probability of being next to a landmark as 1.0.
Accounting for a position precision of +/- 1.0 meters, this places our car at an initial position in the range [4, 6] (5 +/- 1), [9, 11] (10 +/- 1), or [19, 21] (20 +/- 1).
All other positions, not within 1.0 meter of a landmark, are initialized to 0.
We normalize these values to a total probability of 1.0 by dividing by the total number of positions that are potentially occupied.
In this case, that is 9 positions, 3 for each landmark (the landmark position and one position on either side).
This gives us a value of 1.11E-01 for positions +/- 1 from our landmarks (1.0/9). So, our initial belief state is:

{0, 0, 0, 1.11E-01, 1.11E-01, 1.11E-01, 0, 0, 1.11E-01, 1.11E-01, 1.11E-01, 0, 0, 0, 0, 0, 0, 0, 1.11E-01, 1.11E-01, 1.11E-01, 0, 0, 0, 0}

To reinforce this concept, let's practice with a quiz - 

map size: 25 meters
landmark positions: {5, 10, 25}
position standard deviation: 1.0 meters

*/


#include <iostream>
#include <vector>

using std::vector;

// initialize priors assuming vehicle at landmark +/- 1.0 meters position stdev
vector<float> initialize_priors(int map_size, vector<float> landmark_positions,
                                float position_stdev);

int main() {
  // set standard deviation of position
  float position_stdev = 1.0f;

  // set map horizon distance in meters 
  int map_size = 25;

  // initialize landmarks
  vector<float> landmark_positions {5, 10, 20};
  //std::cout<<landmark_positions;

  // initialize priors
  vector<float> priors = initialize_priors(map_size, landmark_positions,
                                           position_stdev);
                                           
  // print values to stdout 
  for (int p = 0; p < priors.size(); ++p) {
    std::cout << priors[p] << std::endl;
  }

  return 0;
}

// TODO: Complete the initialize_priors function
vector<float> initialize_priors(int map_size, vector<float> landmark_positions,
                                float position_stdev) {

  // initialize priors assuming vehicle at landmark +/- 1.0 meters position stdev

  // set all priors to 0.0
  vector<float> priors(map_size, 0.0);
  
  float no_positions;
  // std::cout<<landmark_positions.size()<<std::endl;
  no_positions = (landmark_positions.size())*((2*position_stdev)+1);
  // std::cout<<no_positions<<std::endl;
  float prob = 1 / no_positions;
  
  // TODO: YOUR CODE HERE
  // set each landmark positon +/-1 to 1.0/9.0 (9 possible postions)
  float norm_term = landmark_positions.size() * (position_stdev * 2 + 1);
  for (int i=0; i < landmark_positions.size(); ++i) {
    for (float j=1; j <= position_stdev; ++j) {
      priors.at(int(j+landmark_positions[i]+map_size)%map_size) += 1.0/norm_term;
      priors.at(int(-j+landmark_positions[i]+map_size)%map_size) += 1.0/norm_term;
    }
    priors.at(landmark_positions[i]) += 1.0/norm_term;
  }

  return priors;
}
