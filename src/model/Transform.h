#pragma once

#include <memory>



namespace gen {


	class Transform {
	
	private:
		// bool empty;
		float location[3];
		float rotation[4];
		float scale[3];
		// float loc_x, loc_y, loc_z;
		// float rot_x, rot_y, rot_z, rot_w;
		// float sca_x, sca_y, sca_z;
	
	public:
		// Transform(Transform&&);
		Transform(float, float, float, float, float, float, float, float, float, float);
		void newFrom(Transform&&);
		void copyFrom(std::unique_ptr<Transform>);
		void setLocation(float, float, float);
		void setRotation(float, float, float, float);
		void setScale(float, float, float);
		float* getLocation();
		float* getRotation();
		float* getScale();
		~Transform();

		static std::unique_ptr<Transform> newTransform();
		static std::unique_ptr<Transform> newTransform(float, float, float, float, float, float, float, float, float, float);
		static Transform emptyTransform();
	
	};
	

}