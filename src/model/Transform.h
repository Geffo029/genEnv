#pragma once

#include <memory>



namespace gen {


	class Transform {
	
	private:
		bool empty;
		float location[3];
		float rotation[4];
		float scale[3];
		// Transform();
	
	public:
		// Transform(Transform&&);
		Transform(bool, float, float, float, float, float, float, float, float, float, float);
		void newFrom(Transform&&);
		void copyFrom(std::unique_ptr<Transform>);
		void setLocation(float, float, float);
		void setRotation(float, float, float, float);
		void setScale(float, float, float);
		float* getLocation();
		float* getRotation();
		float* getScale();
		bool isEmpty();
		~Transform();

		static std::unique_ptr<Transform> newTransform();
		static std::unique_ptr<Transform> newTransform(float, float, float, float, float, float, float, float, float, float);
		static Transform emptyTransform();
	
	};
	

}