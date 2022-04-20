#ifndef	BEZIERSURFACE_H
#define	BEZIERSURFACE_H

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Class that represents a Bezier curve 
class BezierSurface
{
public:
	BezierSurface(vector<vector<glm::vec3>> points, glm::vec3 surfaceColor) {
		this->points = points;
		this->init();
		this->surfaceColor = surfaceColor;
	}

	vector<vector<glm::vec3>> getCurve() {
		return this->curve;
	}

	void deleteSurface() {
		this->curve.clear();
	}
	
	glm::vec3 getSurfaceColor() {
		return this->surfaceColor;
	}

	void setControlPoints(vector<vector<glm::vec3>> controlPoints) {
		this->points = controlPoints;
		this->curve.clear();
		this->init();
	}
	

private:
	float offSet;
	vector<vector<glm::vec3>> points;
	vector<vector<glm::vec3>> curve;
	glm::vec3 surfaceColor;

	void init() {
		this->offSet = 1.0f / 100;
		this->curve = this->computeBezier(this->offSet);
		cout << "Curve generated" << endl;
	}
	int factorial(int n) {
		int r = 1;
		for (int i = n; i > 0; i--) {
			r *= i;
		}
		return r;
	}

	// Function that compute BernStein algorithm 
	float bernstein(int i, int n, float t) {
		double r = (double)factorial(n) / (double)(factorial(i) * factorial(n - i));
		r *= pow(t, i);
		r *= pow(1 - t, n - i);
		return (float)r;
	}

	vector<vector<glm::vec3>> computeBezier(float offSet) {
		vector<vector<glm::vec3>> bez;
		for (float u = 0.0f; u <= 1.0f; u += offSet) {
			vector<glm::vec3> row;
			for (float v = 0.0f; v <= 1.0f; v += offSet) {
				glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);
				for (int m = 0; m < points.size(); m++) {
					for (int n = 0; n < points.at(m).size(); n++) {
						float bm = bernstein(m, (int)points.size()-1, u);
						float bn = bernstein(n, (int)points.at(m).size()-1, v);
						float b = bm * bn;
						point += b * points.at(m).at(n);
					}
				}
				row.push_back(point);
			}
			bez.push_back(row);
		}
		return bez;
	}

};
#endif //