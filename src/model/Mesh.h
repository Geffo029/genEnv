#pragma once

#include "VAO.h"
#include <memory>



namespace gen {


	class Mesh {
	
	private:
		bool empty; 
		unsigned int ID;
		unsigned int verticesCount;
		// VAO openGL_vao;
		
		// Mesh();
	
	public:
		// Mesh(Mesh&&);
		Mesh(bool, unsigned int, unsigned int);
		void newFrom(Mesh&&);
		void copyFrom(std::unique_ptr<Mesh>);
		unsigned int getID();
		unsigned int getVericesCount();
		bool isEmpty();
		~Mesh();

		
		static std::unique_ptr<Mesh> newMesh(VAO*);
		static Mesh emptyMesh();
	
	};
	

}
