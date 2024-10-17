#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>



namespace gen {


	// struct Model
	// {
	// 	Transform transform;
	// 	Mesh mesh;
	// 	Texture texture;
	// };


	// extern Model enabledModels[5];
	// extern Model disabledModels[5];


	class Model
	{
		
	private:
		static Model disabledModels[5];
		static unsigned int lastFreeIndex;

	protected:
		Transform transform;
		Mesh mesh;
		// Texture texture;
		
		// static Model models[5];
		// static Model texturedModels[5];
		
		Model();
		
	public:
		void move(float, float, float);
		void rotate(float, float, float, float);
		void rescale(float, float, float);
		void addTransform(std::unique_ptr<Transform>);
		void addMesh(std::unique_ptr<Mesh>);
		// void addTexture(std::unique_ptr<Texture>);
		void absorb(std::unique_ptr<Model>);
		Transform* getTransform();
		Mesh* getMesh();
		// Texture* getTexture();
		~Model();

		// static Model* newModel();
		// static Model* newModel(Transform&&, Mesh&&);
		// static Model* newModel(std::unique_ptr<Transform>, std::unique_ptr<Mesh>);
		// static Model* getModelsArray();
		// static Model* getTexturedModelsArray();
		// static unsigned int modelsCount();

	};


}