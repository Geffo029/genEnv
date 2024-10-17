#pragma once

#include "VAO.h"
#include <memory>



namespace gen {


	class Mesh {
	
	private:
		// bool empty; 
		unsigned int ID;
		unsigned int verticesCount;
		// VAO openGL_vao;
		
		// Mesh();
	
	public:
		// Mesh(Mesh&&);
		Mesh(unsigned int, unsigned int);
		void newFrom(Mesh&&);
		void copyFrom(std::unique_ptr<Mesh>);
		unsigned int getID();
		unsigned int getVerticesCount();
		~Mesh();

		
		static std::unique_ptr<Mesh> newMesh(VAO*);
		static Mesh emptyMesh();
	
	};
	

}
