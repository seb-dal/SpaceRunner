#pragma once

#include <vector>
#include "mesh.h"
#include <math.h>
#include "Utility.h"

using namespace std;

class RoadBot {
private:
	float rot, step;

	Point current_pos, goal_pos;
	Vector current_dir;// XY, XZ, YZ

	float r(Vector& diff, Vector& goal_dir, Vector& next_dir, int i) {
		if (std::abs(diff(i)) <= M_PI) {
			if (goal_dir(i) < next_dir(i)) {
				return (std::min(rot, std::abs(diff(i))));
			}
			else {
				return -(std::min(rot, std::abs(diff(i))));
			}
		}
		else {
			if (goal_dir(i) < next_dir(i)) {
				return  -(std::min(rot, std::abs(diff(i))));
			}
			else {
				return  (std::min(rot, std::abs(diff(i))));
			}
		}

	}


	Point next() {
		Point next_pos(current_pos + Utility::cos(current_dir) * step);
		Vector goal_dir = Utility::GetAnglesBetween2Points(current_pos, goal_pos);
		Vector next_dir = Utility::GetAnglesBetween2Points(current_pos, next_pos);

		//cout << "current_pos:" << current_pos << " next_pos:" << next_pos << " goal_pos:" << goal_pos << endl;
		//cout << "current_dir:" << current_dir << " next_dir:" << next_dir << " goal_dir:" << goal_dir << endl;

		Vector diff = goal_dir - next_dir;
		if (length(diff) > 1) {
			for (int i = 0; i < 3; i++)
				current_dir(i) += r(diff, goal_dir, next_dir, i);
		}

		current_pos = current_pos + Utility::cos(current_dir) * step;
		//cout << "POST current_dir:" << current_dir << endl << endl;
		return current_pos;
	}

public:
	RoadBot(float rotationBot, float stepBot, Point& pos_init, Vector& dir_init) :
		rot(rotationBot), step(stepBot), current_pos(pos_init), current_dir(dir_init)
	{}

	void setNewGoal(Point& goal) {
		goal_pos = goal;
	}

	bool goal() {
		return (
			std::abs(goal_pos.x - current_pos.x)
			+ std::abs(goal_pos.y - current_pos.y)
			+ std::abs(goal_pos.z - current_pos.z)
			) < step;
	}

	std::vector<Point> getAllPointsToGoal() {
		std::vector<Point> listP;
		listP.emplace_back(current_pos);
		while (!goal()) {

			listP.emplace_back(next());
			if (listP.size() > 800)// avoid infinite loop memory allocation (RIP la RAM/PC)
				return listP;
		}
		listP.emplace_back(goal_pos);
		current_pos = goal_pos;

		return listP;
	}

	std::vector<Point> getAllPointsToGoals(std::vector<Point>& list) {
		std::vector<Point> listP;
		for (Point& p : list) {
			setNewGoal(p);
			std::vector<Point> listPInter = getAllPointsToGoal();
			listP.insert(listP.end(), listPInter.begin(), listPInter.end());
		}
		return listP;
	}
};

