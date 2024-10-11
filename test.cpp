#include <iostream>


class Transform {
private:
    float location[3];
    float rotation[4];
    float scale[3];
public:
    Transform() {
        std::cout << "Costruttore di Transform" << std::endl;
        location[0] = 0; location[1] = 0; location[2] = 0;
        rotation[0] = 0; rotation[1] = 0; rotation[2] = 0; rotation[3] = 1;
        scale[0] = 1; scale[1] = 1; scale[2] = 1;
    }
    Transform(const Transform &other) {
        std::cout << "Copiatore di Transform" << std::endl;
        location[0] = other.location[0]; location[1] = other.location[1]; location[2] = other.location[2];
        rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = other.rotation[2]; rotation[3] = other.rotation[3];
        scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
    }
    Transform(Transform &&other) {
        std::cout << "Spostatore di Transform" << std::endl;
        location[0] = other.location[0]; location[1] = other.location[1]; location[2] = other.location[2];
        rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = other.rotation[2]; rotation[3] = other.rotation[3];
        scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
    }
    void sposta(Transform &&other) {
        std::cout << "sposta di Transform" << std::endl;
        location[0] = other.location[0]; location[1] = other.location[1]; location[2] = other.location[2];
        rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = other.rotation[2]; rotation[3] = other.rotation[3];
        scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
    }
    ~Transform() {
        std::cout << "Distruttore di Transform" << std::endl;
    }
};

class Mesh {
private:
    int ID;
    int verticesCount;
    Mesh() {
        std::cout << "Costruttore di Mesh" << std::endl;
        ID = 1;
        verticesCount = 10;
    }
    Mesh(const Mesh &other) {
        std::cout << "Copiatore di Mesh" << std::endl;
        ID = other.ID;
        verticesCount = other.verticesCount;
    }
    Mesh(Mesh &&other) {
        std::cout << "Spostatore di Mesh" << std::endl;
        ID = other.ID;
        verticesCount = other.verticesCount;
    }
public:
    void sposta(Mesh &&other) {
        std::cout << "sposta di Mesh" << std::endl;
        ID = other.ID;
        verticesCount = other.verticesCount;
    }
    ~Mesh() {
        std::cout << "Distruttore di Mesh" << std::endl;
    }
};

class Model {
private:	
    static Model array[10];
	Transform transform;
	Mesh mesh;
    Model() : transform(), mesh() {}
	Model(Transform &&transform, Mesh &&mesh) 
		    : transform(std::move(transform)), mesh((Mesh&&)mesh) {
        // this->transform.sposta(std::move(transform));
    }
public:

    static Model* createModel(Transform &&transform, Mesh &&mesh) {
        // return new Model(std::move(transform), std::move(mesh));
        array[0].transform.sposta(std::move(transform));
        array[0].mesh.sposta(std::move(mesh));
        return &array[0];
    }
};
Model Model::array[10];


int main(int argc, char const *argv[]) {

    Transform *transform = new Transform();
    Mesh *mesh = new Mesh();
    // Model *model = new Model(std::move(*transform), (Mesh&&)mesh);
    Model *model = Model::createModel(std::move(*transform), (Mesh&&)(*mesh));

    // model->transform.scale[0] = 10;

    // std::cout << "model->transform.scale[0]: " << model->transform.scale[0] << std::endl;
    // std::cout << "transform->scale[0]: " << transform->scale[0] << std::endl;
 
    // std::cout << "&model->transform:\t" << &(model->transform) << std::endl;
    // std::cout << "&model->mesh:\t\t" << &(model->mesh) << std::endl;
    // std::cout << "transform:\t\t" << transform << std::endl;
    // std::cout << "mesh:\t\t\t" << mesh << std::endl;


	return 0;
}
