#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cmath>

std::string fileDir = "./inOut/01";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

// #define in inputFile
// #define out outputFile
#define in std::cin
#define out std::cout

#define PI 3.14159265

double calcReqVelocity(double angle, int x) {
    angle = angle * PI / 180;
    return sqrt((9.81*pow(x, 2))/(2*pow(cos(angle), 2)*x*tan(angle)));
}

double calcYforX(double angle, double velocity, int x) {
    angle = angle * PI / 180;
    return x*tan(angle) - (9.81*pow(x, 2))/(2*pow(velocity, 2)*pow(cos(angle), 2));
}

struct obstacle {
    std::pair<int, int> bottomLeft;
    std::pair<int, int> topRight;
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    int numThrows;
    in >> numThrows;

    for (int i = 0; i < numThrows; i++) {
        int obstacleNum, dist;
        in >> obstacleNum >> dist;
        
        vector<obstacle> obstacles;

        for (int j = 0; j < obstacleNum; j++) {
            obstacle temp;
            in >> temp.bottomLeft.first >> temp.bottomLeft.second >> temp.topRight.first >> temp.topRight.second;
            obstacles.push_back(temp);
        }

        double angle = 45;
        double increment = 0.001;
        int increments = 0;

        double validAngle1 = 0;
        double validAngle2 = 0;

        while (true) {
            double velocity = calcReqVelocity(angle, dist);
            double vertexY = calcYforX(angle, velocity, dist/2);
            bool hit = false;
            
            for (int j = 0; j < obstacleNum; j++) {

                double leftY = calcYforX(angle, velocity, obstacles[j].bottomLeft.first);
                double rightY = calcYforX(angle, velocity, obstacles[j].topRight.first);

                // out << angle << " " << leftY << " " << rightY << " " << vertexY << " " << obstacles[j].bottomLeft.first <<
                //     " " << obstacles[j].bottomLeft.second << " " << 
                //     obstacles[j].topRight.first << " " << obstacles[j].topRight.second << endl;

                if (leftY < obstacles[j].topRight.second) {
                    if (rightY > obstacles[j].bottomLeft.second) {
                        hit = true;
                        break;
                    }
                    else if (vertexY > obstacles[j].bottomLeft.second && dist/2 > obstacles[j].bottomLeft.first && dist/2 < obstacles[j].topRight.first) {
                        hit = true;
                        break;
                    }
                }
                if (leftY > obstacles[j].bottomLeft.second && rightY < obstacles[j].topRight.second) {
                    hit = true;
                    break;
                }
            }
            
            // if an obstacle was hit
            //change the angle by 1, whilst staying the closet to 45 (44,46,43,47,42,48...)
            if (hit) {
                if (angle < 45) {
                    angle += 2*increments*increment;
                }
                else if (angle > 45) {
                    //if a valid throw was found for <45 but not >45
                    if (validAngle1 != 0) break; ///////////////////////////////////////////////////
                    angle -= (2*increments*increment+increment);
                    increments++;
                }
                else {
                    increments++;
                    angle -= increment;
                }
            }
            //A valid throw was found
            //if under 45, also check for a valid throw above 45 (because they will be of equal distance to 45)
            else {
                if (angle < 45) {
                    validAngle1 = angle;
                    angle += (2*increments*increment+increment);
                    increments++;
                }
                else if (angle > 45) {
                    validAngle2 = angle;
                    break; /////////////////////////////////////////////
                }
                else {
                    validAngle1 = angle;
                    break; ///////////////////////////////////////////////
                }
            }
        }
        while (true) {
            if (validAngle1 == 45 || validAngle1 == 0) break;
            //revert an increment
            if (increment < 0.0001) break;
            validAngle1 += increment;
            increment /= 10;
            // cout << increment << endl;
            //progress with a smaller increment
            validAngle1 -= increment;
            while (true) {
                double velocity = calcReqVelocity(validAngle1, dist);
                double vertexY = calcYforX(validAngle1, velocity, dist/2);
                bool hit = false;
                
                for (int j = 0; j < obstacleNum; j++) {
                    double leftY = calcYforX(validAngle1, velocity, obstacles[j].bottomLeft.first);
                    double rightY = calcYforX(validAngle1, velocity, obstacles[j].topRight.first);

                    // out << validAngle1 << " " << leftY << " " << rightY << " " << vertexY << " " << obstacles[j].bottomLeft.first <<
                    // " " << obstacles[j].bottomLeft.second << " " << 
                    // obstacles[j].topRight.first << " " << obstacles[j].topRight.second << endl;

                    if (leftY < obstacles[j].topRight.second) {
                        if (rightY > obstacles[j].bottomLeft.second) {
                            hit = true;
                            break;
                        }
                        else if (vertexY > obstacles[j].bottomLeft.second && dist/2 > obstacles[j].bottomLeft.first && dist/2 < obstacles[j].topRight.first) {
                            hit = true;
                            break;
                        }
                    }
                    if (leftY > obstacles[j].bottomLeft.second && rightY < obstacles[j].topRight.second) {
                        hit = true;
                        break;
                    }
                }
                if (hit) {
                    validAngle1 -= increment;
                }
                else {
                    break;
                }
            }
        }

        if (validAngle2 != 0) {
            increment = 0.0005;
            while (true) {
                //revert an increment
                if (increment < 0.0001) break;
                validAngle2 -= increment;
                increment /= 10;
                //progress with a smaller increment
                validAngle2 += increment;
                while (true) {
                    double velocity = calcReqVelocity(validAngle2, dist);
                    double vertexY = calcYforX(validAngle2, velocity, dist/2);
                    bool hit = false;
                    
                    for (int j = 0; j < obstacleNum; j++) {
                        double leftY = calcYforX(validAngle2, velocity, obstacles[j].bottomLeft.first);
                        double rightY = calcYforX(validAngle2, velocity, obstacles[j].topRight.first);

                    //     out << validAngle2 << " " << leftY << " " << rightY << " " << vertexY << " " << obstacles[j].bottomLeft.first <<
                    // " " << obstacles[j].bottomLeft.second << " " << 
                    // obstacles[j].topRight.first << " " << obstacles[j].topRight.second << endl;

                        if (leftY < obstacles[j].topRight.second) {
                            if (rightY > obstacles[j].bottomLeft.second) {
                                hit = true;
                                break;
                            }
                            else if (vertexY > obstacles[j].bottomLeft.second && dist/2 > obstacles[j].bottomLeft.first && dist/2 < obstacles[j].topRight.first) {
                                hit = true;
                                break;
                            }
                        }
                        if (leftY > obstacles[j].bottomLeft.second && rightY < obstacles[j].topRight.second) {
                            hit = true;
                            break;
                        }
                    }
                    if (hit) {
                        validAngle2 += increment;
                    }
                    else {
                        break;
                    }
                }
            } 
        }

        if (abs(45-validAngle1) < abs(45-validAngle2)) {
            out << validAngle1 << " " << calcReqVelocity(validAngle1, dist) << endl;
        }
        else {
            out << validAngle2 << " " << calcReqVelocity(validAngle2, dist) << endl;
        }

    }
}