#pragma once

#include <vector>
#include "mesh.h"
#include <math.h>
#include "Utility.h"

class RoadBot {
private:
	float rot, step;

	Point current_pos, goal_pos;
	Vector current_dir;// XY, XZ, YZ

	Point next() {
		Point next(current_dir * step);
		Vector goal_dir = GetAnglesBetween2Points(current_pos, goal_pos);
        Vector next_dir = GetAnglesBetween2Points(current_pos, next);

		Vector diff = goal_dir - next_dir;
		if (length(diff) != 0) {

			if (std::abs(diff.x) <= M_PI) {
				if (goal_dir.x < next_dir.x) {
					current_dir.x += std::min(rot, std::abs(diff.x));
				}
				else {
					current_dir.x -= std::min(rot, std::abs(diff.x));
				}
			}
			else {
				if (goal_dir.x < next_dir.x) {
					current_dir.x -= std::min(rot, std::abs(diff.x));
				}
				else {
					current_dir.x += std::min(rot, std::abs(diff.x));
				}
			}

			if (std::abs(diff.y) <= M_PI) {
				if (goal_dir.y < next_dir.y) {
					current_dir.y += std::min(rot, std::abs(diff.y));
				}
				else {
					current_dir.y -= std::min(rot, std::abs(diff.y));
				}
			}
			else {
				if (goal_dir.y < next_dir.y) {
					current_dir.y -= std::min(rot, std::abs(diff.y));
				}
				else {
					current_dir.y += std::min(rot, std::abs(diff.y));
				}
			}

			if (std::abs(diff.z) <= M_PI) {
				if (goal_dir.z < next_dir.z) {
					current_dir.z += std::min(rot, std::abs(diff.z));
				}
				else {
					current_dir.z -= std::min(rot, std::abs(diff.z));
				}
			}
			else {
				if (goal_dir.z < next_dir.z) {
					current_dir.z -= std::min(rot, std::abs(diff.z));
				}
				else {
					current_dir.z += std::min(rot, std::abs(diff.z));
				}
			}
		}

		current_pos = current_pos + current_dir * step;

		return current_pos;
	}

public:
	RoadBot(float rotationBot, float stepBot, Point pos_init, Vector dir_init) :
		rot(rotationBot), step(stepBot), current_pos(pos_init), current_dir(dir_init)
	{}

	void setNewGoal(Point goal) {
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
			if (listP.size() > 5000)// avoid infinite loop memory allocation (RIP la RAM/PC)
				return listP;
		}
		listP.emplace_back(goal_pos);
		current_pos = goal_pos;

		return listP;
	}
};

