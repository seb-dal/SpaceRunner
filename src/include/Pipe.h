#pragma once
#include <vector>
#include "mesh.h"
#include "Circule.h"


class Pipe {
	unsigned int N;
	std::vector<Circule*> listSegmentCircule;

public:
	Pipe(unsigned int N) {
		this->N = N;
	}

	~Pipe() {
		for (int i = 0; i < listSegmentCircule.size(); i++) {
			delete listSegmentCircule[i];
		}
		listSegmentCircule.clear();
	}

	void removeFirst() {
		delete listSegmentCircule[0];
		listSegmentCircule.erase(listSegmentCircule.begin());
	}

	void drawPipe(Mesh& obj, int material) {
		if (listSegmentCircule.size() > 0) {
			Circule* c1 = NULL; Circule* c2 = NULL;
			for (size_t i = 0; i < listSegmentCircule.size(); i++) {
				if (c2 != NULL) {
					c1 = c2;
					c2 = listSegmentCircule[i];
					for (int p = 0; p < N; p++) {
						obj.material(material);
						obj.vertex(*c1->listPoints[p]);
						obj.vertex(*c2->listPoints[p]);
					}
				}
				else {
					// get the first circle in the start
					c2 = listSegmentCircule[i];
				}
			}
		}
	}

	void addCircule(const Point& center, float size, const Vector& axis, const Vector& v) {
		listSegmentCircule.push_back(new Circule(N, center, size, axis, v));
	}
};
