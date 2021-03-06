#pragma once

#include "window.h"

#include "mesh.h"
#include "wavefront.h"  // pour charger un objet au format .obj
#include "orbiter.h"

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include <stdio.h>
#include <vector>
#include <materials.h>
#include <cmath>
#include <runner/include/Pipeline.h>

class Pipeline;

class Utility {
	Utility() {};
public:
	/**
	* String value of a color.
	*/
	static std::string toString_Color(Color& c);



	static Vector perpendicular_Vector_Triangle(const Vector& a, const Vector& b, const Vector& c);



	static float vertical_angle_triangle(const Vector& a, const Vector& b, const Vector& c);



	/**
	 * Create a Vector from the difference of 2 points
	 */
	static Vector getVector(const Point& from, const Point& to);



	/**
	 * return the angle between the Vectors v1 and v2
	 */
	static float getAngleBetweenVectors(const Vector& v1, const Vector& v2);



	/**
	 * return the rotation XYZ as a Vector of the 2 points
	 */
	static Vector GetAnglesBetween2Points(const Point& from, const Point& to);



	/*
	* return an intermediate point between 2 points
	* r: [0.0, 1.0]
	*/
	static Point interPoint(Point& from, Point& to, float r) {
		return Point(from + r * (to - from));
	}



	/**
	 * Get a list of points that are the result of the smoothing of the list of points in param.
	 */
	static std::vector<Point> subdivisionPoint(std::vector<Point>& pointInit, int iteration);



	/**
	 * Draw a line with a list of points
	 */
	static void drawLine(Mesh& line, std::vector<Point>& listPoint);



	static void buildPerpendicularVect(std::vector<Point>& listPoint, std::vector<Vector>& v, const Vector& init);



	/**
	 * Draw a line with with a Vector parallele to the line
	 */
	static void drawLineWithVec(Mesh& line, const std::vector<Point>& listPoint, const std::vector<Vector>& v);



	/**
	* Build and draw a pipe.
	*/
	static void buildPipe(Mesh& quad, std::vector<Point>& listPoint, std::vector<Vector>& v, float sizePipe);



	/*
	*Random value between -1 and 1
	*/
	static float randf();
	static float randomf();



	/**
	 * Random float.
	 *
	 * \param LO lower part
	 * \param HI higher part
	 * \return
	 */
	static float randf(const float LO, const float HI);



	/**
	 * Get a point that rotate around another point.
	 *
	 * \param center center
	 * \param size space between the center ans the point
	 * \param axis
	 * \param v
	 * \param angle
	 * \return
	 */
	static Point rotAround(const Point& center, float size, const Vector& axis, const Vector& v, float angle);



	static float GetT(const float t, const float alpha, const Point& p0, const Point& p1);



	static float lerp(float a, float b, float t);



	/**
	 * Compute centripetal Catmull???Rom spline.
     * https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
	 *
	 * \param p0 point before
	 * \param p1 point start
	 * \param p2 point end
	 * \param p3 point after
	 * \param t position of the point between start and end ( value between 0 and 1 )
	 * \param alpha strangth of the rotation ( value between 0 and 1 )
	 * \return
	 */
	static Point CatMullRom(const Point& p0, const Point& p1, const Point& p2, const Point& p3, float t, float alpha = .5f);



	/**
	 * Get model matrix for object on the pipe.
	 *
	 * \param pipe pointer to the pipe
	 * \param position int position on the pipe
	 * \param heightOnPipe height at which the object will be
	 * \param rotation angle at which the object will rotate around the pipe
	 * \return
	 */
	static Transform modelOnPipe(Pipeline* pipe, const float position, const float heightOnPipe, const float rotation);



	/**
	 * Lookat for object (without .inverse() :p).
	 *
	 * \param from position of the object
	 * \param to position the object lookat
	 * \param up vector up
	 * \return
	 */
	static Transform Lookat(const Point& from, const Point& to, const Vector& up);
};