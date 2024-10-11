#include "Math.h"
#include <cmath>
#include <iostream>
#include <ostream>


using namespace gen;

const double PI = 3.141592653589793;
const double RADIAN_TO_DEGREE = 180.0 / PI;
const double DEGREE_TO_RADIAN = PI / 180.0;


Mat4::Mat4()
{
	values = new float[NUM_ROWS*NUM_COLS];
}

Mat4::~Mat4()
{}

void Mat4::set(int row, int col, float value)
{
	values[col*NUM_COLS + row] = value;
}

float Mat4::get(int row, int col) const
{
	return values[col*NUM_COLS + row];
}

float* Mat4::toArray() const
{
	return values;
}

void Mat4::print() const
{
	std::cout << "[" << std::endl;
	for (int row = 0; row < Mat4::NUM_ROWS; row++) {
		std::cout << "[";
		for (int col = 0; col < Mat4::NUM_COLS; col++) {
			std::cout << get(row, col) << ", ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]" << std::endl;
}

Mat4 Mat4::multiply(Mat4 mat1, Mat4 mat2)
{
	Mat4 res;
	for (int row = 0; row < NUM_ROWS; row++) {
		for (int col = 0; col < NUM_COLS; col++) {
			res.set(row, col, 
				mat1.get(row, 0) * mat2.get(0, col) +
				mat1.get(row, 1) * mat2.get(1, col) +
				mat1.get(row, 2) * mat2.get(2, col) +
				mat1.get(row, 3) * mat2.get(3, col)
			);
		}
	}
	return res;
}

Mat4 Mat4::translationMatrix(float translation[])
{
	Mat4 mat = identity();
	mat.set(0, 3, translation[0]);
	mat.set(1, 3, translation[1]);
	mat.set(2, 3, translation[2]);
	return mat;
}

Mat4 Mat4::rotationMatrix(float rotation, float axis[])
{
	float x = axis[0];
	float y = axis[1];
	float z = axis[2];
	float cos = (float) std::cos(rotation*DEGREE_TO_RADIAN);
	float sin = (float) std::sin(rotation*DEGREE_TO_RADIAN);
	Mat4 mat = identity();
	mat.set(0, 0, cos + x*x * (1-cos));
	mat.set(0, 1, x * y * (1-cos) - z * sin);
	mat.set(0, 2, x * z * (1-cos) + y * sin);
	mat.set(1, 0, y * x * (1-cos) + z * sin);
	mat.set(1, 1, cos + y*y * (1-cos));
	mat.set(1, 2, y * z * (1-cos) - x * sin);
	mat.set(2, 0, z * x * (1-cos) - y * sin);
	mat.set(2, 1, z * y * (1-cos) + x * sin);
	mat.set(2, 2, cos + z*z * (1-cos));
	return mat;
}

Mat4 Mat4::rotationMatrix(float rotation[])
{  //rotation: α, β, γ
	Mat4 mat = identity();
	float 
		sinA = (float) std::sin(rotation[0]*DEGREE_TO_RADIAN),
		cosA = (float) std::cos(rotation[0]*DEGREE_TO_RADIAN),
		sinB = (float) std::sin(rotation[1]*DEGREE_TO_RADIAN),
		cosB = (float) std::cos(rotation[1]*DEGREE_TO_RADIAN),
		sinG = (float) std::sin(rotation[2]*DEGREE_TO_RADIAN),
		cosG = (float) std::cos(rotation[2]*DEGREE_TO_RADIAN);
	mat.set(0, 0,   cosB*cosG);
	mat.set(0, 1,   sinA*sinB*cosG - cosA*sinG);
	mat.set(0, 2,   cosA*sinB*cosG + sinA*sinG);
	mat.set(1, 0,   cosB*sinG);
	mat.set(1, 1,   sinA*sinB*sinG + cosA*cosG);
	mat.set(1, 2,   cosA*sinB*sinG - sinA*cosG);
	mat.set(2, 0,   -sinB);
	mat.set(2, 1,   sinA*cosB);
	mat.set(2, 2,   cosA*cosB);
	return mat;
}

Mat4 Mat4::scaleMatrix(float scale[])
{
	Mat4 mat = identity();
	mat.set(0, 0, scale[0]);
	mat.set(1, 1, scale[1]);
	mat.set(2, 2, scale[2]);
	return mat;
}

Mat4 Mat4::modelMatrix(float translation[], float rotation[], float scale[])
{
	float rightHandLocation[] {translation[0], translation[1], -translation[2]};
	
	Mat4 translationMat = translationMatrix(rightHandLocation);
	Mat4 rotationMat = rotationMatrix(rotation);
	Mat4 scaleMat = scaleMatrix(scale);
	
	// Mat4 modelMat = multiply(rotationMat, scaleMat);
	// modelMat = multiply(translationMat, modelMat);
	Mat4 modelMat = multiply(translationMat, multiply(rotationMat, scaleMat));
	
	return modelMat;
}

Mat4 Mat4::viewMatrix(float camTranslation[], float camRotation[])
{
	float rightHandLocation[] {camTranslation[0], camTranslation[1], -camTranslation[2]};	//OCIO QUI
	Mat4 camTranslationMat = translationMatrix(new float[] {-rightHandLocation[0], -rightHandLocation[1], -rightHandLocation[2]} );	//e SE LA Z NON FOSSE DA NEGARE??
	// float[] camXRotationMat = rotationMatrix(camRotation[0], new float[] {1, 0, 0});
	// float[] camYRotationMat = rotationMatrix(camRotation[1], new float[] {0, 1, 0});
	// float[] camZRotationMat = rotationMatrix(camRotation[2], new float[] {0, 0, 1});
	Mat4 camRotationMat = rotationMatrix(camRotation);
	// return multiply(new float[][] {camXRotationMat, camYRotationMat, camZRotationMat, camTranslationMat});
	return multiply(camRotationMat, camTranslationMat);
}


Mat4 Mat4::projectionMatrix_perspective(float near, float far, float FOV, float aspectRatio)
{
	// public static Mat4 projectionMatrix_perspective(float near, float far, float width, float height, float aspectRatio) {
	Mat4 projectionMatrix = Mat4::emptyMatrix();
	
	/* https://www.youtube.com/watch?v=U0_ONQQ5ZNM  oppure */
	/* https://www.songho.ca/opengl/gl_projectionmatrix.html */
	// float tan = (float) Math.tan(Math.toRadians(FOV/2)); /* tan=0.70 if FOV=70 */
	float tan =  std::tan((FOV/2)*DEGREE_TO_RADIAN); /* tan=0.70 if FOV=70 */
	float bottom = near * tan; /* bottom=0.070 if near=0.1 */
	float right = bottom * aspectRatio; /* right=0.093 if aspectRation=4/3 */
	// float right = width / 2;
	// float bottom = height / 2;
	projectionMatrix.set(0, 0, near / right);
	projectionMatrix.set(1, 1, near / bottom);
	// projectionMatrix.set(2, 2, far / (far-near));
	// projectionMatrix.set(2, 3, -far*near / (far-near));
	// projectionMatrix.set(3, 2, 1);
	projectionMatrix.set(2, 2, -(far+near) / (far-near));
	projectionMatrix.set(2, 3, -2*far*near / (far-near));
	projectionMatrix.set(3, 2, -1);

	return projectionMatrix;
}

Mat4 Mat4::identity()
{
	Mat4 mat = emptyMatrix();
	for (int row = 0; row < NUM_ROWS; row++) 
		for (int col = 0; col < NUM_COLS; col++)
			if (row == col) mat.set(row, col, 1);
	return mat; 
}

Mat4 Mat4::emptyMatrix()
{
	Mat4 mat;
	for (int row = 0; row < NUM_ROWS; row++) 
		for (int col = 0; col < NUM_COLS; col++)
			mat.set(row, col, 0);
	return mat; 
}



std::ostream& operator << (std::ostream &os, const Mat4 &mat)
{
	os << "[";
	for (int row = 0; row < Mat4::NUM_ROWS; row++) {
		os << "[";
		for (int col = 0; col < Mat4::NUM_COLS; col++) {
			os << mat.get(row, col) << ", ";
		}
		os << "]" << std::endl;
	}
	os << "]";
    return (os << std::endl);
}