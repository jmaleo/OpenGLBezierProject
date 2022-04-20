#ifndef	BEZIERCURVE_H
#define BEZIERCURVE_H

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Class that represents a Bezier curve 
class BezierCurve
{
public:
	BezierCurve(float n, vector<glm::vec3> points, bool withDistance = false) {
		this->withDistance = withDistance;
		this->points = points;
		this->init(n);
	}
	BezierCurve(float n, vector<glm::vec2> points, bool withDistance = false) {
		this->withDistance = withDistance;
		this->points = addZaxis(points);
		this->init(n);
	}
	
	vector<glm::vec3> getCurve() {
		return this->curve;
	}

	vector<unsigned int> getIndices() {
		return indices;
	}

	void setControlPoints(vector<glm::vec3> points, float offSet) {
		this->points = points;
		this->init(offSet);
	}

	void deleteCurve() {
		this->curve.clear();
		this->indices.clear();
	}

	void changeCurve(float n) {
		if (this->withDistance) {
			this->curve = this->generateCurveWithDistance(n);
		}
		else {
			this->offSet = 1.0f / n;
			this->curve = this->generateCurve(this->offSet, n);
		}
		this->indices = this->generateIndices();
	}

private:
	float offSet;
	vector<glm::vec3> points;
	size_t nbPoints;
	vector<glm::vec3> curve;
	vector<unsigned int> indices;
	bool withDistance;

	void init(float n) {
		this->nbPoints = this->points.size();
		if (this -> withDistance) {
			this->curve = this->generateCurveWithDistance(n);
		}
		else {
			this->offSet = 1.0f / n;
			this->curve = this->generateCurve(this->offSet, (int)n);
		}
		this->indices = this->generateIndices();
	}

	//Sets to 0.0f the z axis of a vec2 array
	vector<glm::vec3> addZaxis(vector<glm::vec2> points) {
		vector<glm::vec3> points3 = vector<glm::vec3>();
		for (int i = 0; i < points.size(); i++) {
			
			points3.push_back(glm::vec3(points[i].x, points[i].y, 0.0f));
		}
		return points3;
	}

	// Returns the point of the curve at a given t
	glm::vec3 getPoint(float t, int start, int stop) {
		if (start == stop)
			return this->points.at(start);
		glm::vec3 left = getPoint(t, start, stop - 1);
		glm::vec3 right = getPoint(t, start + 1, stop);
		return left * (1 - t) + right * t;
	}


	// Applies getBezierPoint to each point of the curve, at each t to create the curve
	vector<glm::vec3> generateCurve(float offSet, int nbPointOnCurve) {
		vector<glm::vec3> curve;
		for (float t = 0; t <= 1.0f; t += offSet) {
			curve.push_back(this->getPoint(t, 0, (int)(this->nbPoints - 1)));
		}
		if (curve.size() <= nbPointOnCurve)
			curve.push_back(points.at(points.size() - 1));
		return curve;
	}

	// Computes the distance between two glm::vec3 points
	float distance(glm::vec3 p1, glm::vec3 p2) {
		return (float)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	}

	//Returns a vector of indices that represents the curve with segment of same distance
	vector<glm::vec3> generateCurveWithDistance(float distance) {
		vector<glm::vec3> curveTemp = generateCurve(1.0f/1000, 1000);
		vector<glm::vec3> curveWithDistance = vector<glm::vec3>();
		int last = 0;
		float distanceTemp = 0.0f;
		curveWithDistance.push_back(curveTemp.at(0));
		for (int i = 0; i < curveTemp.size(); i++) {
			distanceTemp = this->distance(curveWithDistance.at(last), curveTemp.at(i));
			if (distanceTemp >= distance) {
				curveWithDistance.push_back(curveTemp.at(i));
				last++;
			}
		}
		if (distanceTemp < distance)
			curveWithDistance.push_back(curveTemp.at(curveTemp.size() - 1));
		return curveWithDistance;
	}

	// Returns the indices arrays of each lines of Bezier Curve
	vector<unsigned int> generateIndices() {
		vector<unsigned int> indices;
		for (int i = 0; i < (int)this->curve.size(); i++) {
			indices.push_back(i);
			//indices.push_back(i + 1);
		}
		return indices;
	}
};
#endif //