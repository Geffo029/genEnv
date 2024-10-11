#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>



namespace gen {


	// class ModelManager {
	// private:
	// 	static Model renderQueue[100];
	// 	static unsigned int lastFreeIndex = 0;
	// public:
	// 	static void createModel(Transform, Mesh);
	// };


	
	class Model
	{
		// friend class ModelManager;
		// friend class ComponentManager;
	
	private:
		bool empty;
		int index;
		Transform transform;
		Mesh mesh;
		Texture texture;
		
		static Model renderQueue[5];
		static unsigned int lastFreeIndex;
		Model();
		// Model(Transform&&, Mesh&&, unsigned int);

	public:
		void move(float, float, float);
		void rotate(float, float, float, float);
		void rescale(float, float, float);
		void addTransform(std::unique_ptr<Transform>);
		void addMesh(std::unique_ptr<Mesh>);
		void addTexture(std::unique_ptr<Texture>);
		void absorb(std::unique_ptr<Model>);
		bool isEmpty();
		Transform* getTransform();
		Mesh* getMesh();
		Texture* getTexture();
		~Model();

		static Model* newModel();
		static Model* newModel(Transform&&, Mesh&&);
		static Model* newModel(std::unique_ptr<Transform>, std::unique_ptr<Mesh>);
		static Model* modelsQueue();
		static unsigned int modelsCount();

		// static Model* partialModel(std::unique_ptr<Transform>);
		// static Model* partialModel(std::unique_ptr<Mesh>);

	};


}