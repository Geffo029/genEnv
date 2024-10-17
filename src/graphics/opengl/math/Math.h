#pragma once
#include <ostream>



namespace gen {
	

	class Mat4 {
	
	private:
		float *values;
		
		static Mat4 translationMatrix(float[]);
		static Mat4 rotationMatrix(float, float[]);
		static Mat4 rotationMatrix(float[]);
		static Mat4 scaleMatrix(float scale[]);
	
	public:
		static const int NUM_ROWS = 4;
		static const int NUM_COLS = 4;
		
		Mat4();
		~Mat4();
		void set(int, int, float);
		float get(int, int) const;
		float* toArray() const;
		void print() const;
		
		static Mat4 multiply(Mat4 mat1, Mat4 mat2);
		static Mat4 modelMatrix(float[], float[], float[]);
		static Mat4 viewMatrix(float[], float[]);
		static Mat4 projectionMatrix_perspective(float, float, float, float);
		static Mat4 identity();
		static Mat4 emptyMatrix();
		friend std::ostream& operator << ( std::ostream &os, const Mat4 &mat);
	};
	
	
	struct Vec4 {
		float x, y, z, w;
	};

} // namespace gen
