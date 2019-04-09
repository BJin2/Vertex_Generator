#include "DrawableObject.hpp"


GLuint* DrawableObject::getVAO()
{
	return VAO;
}

DrawableObject::DrawableObject(int numCorner, Type type, TextureID id)
{
	this->id = id;
	num_index = new int(0);

	switch (type)
	{
	case Type::Cone:
		//VAO = VertexGenerator::CreateCone(numCorner, id, num_index);
		break;
	case Type::Plane:
		//VAO = VertexGenerator::CreatePlane(numCorner, id, num_index);
		break;
	case Type::Star:
		//VAO = VertexGenerator::CreateStar(numCorner, id, num_index);
		break;
	case Type::Column:
	default:
		VAO = VertexGenerator::CreateColumn(numCorner, id, num_index);
		break;
	}
}