#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "GroupNode.h"

class TransformNode : public GroupNode
{
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	//float angle; //added
	//float xan, yan, zan;

	static glm::mat4 transformMatrix;

public:
	TransformNode(const std::string& name) : GroupNode(name)
	{
		type = nt_TransformNode;
		translation = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
		//angle = 0;
	}

	void SetTranslation(const glm::vec3& tr)
	{
		translation = tr;
	}

	void SetScale(const glm::vec3& sc)
	{
		scale = sc;
	}

	/*void SetRotation(float an, const glm::vec3& ro)  //added
	{
		rotation = ro;
		angle = an;
	}*/

	void SetRotation(float xangle, float yangle, float zangle) {
		rotation.x = xangle;
		rotation.y = yangle;
		rotation.z = zangle;
	}


	void Traverse()
	{
		//push
		glm::mat4 matCopy = transformMatrix;

	//	matCopy = glm::rotate(matCopy, angle, rotation); //added
		transformMatrix = glm::translate(transformMatrix, translation);
		transformMatrix = glm::scale(transformMatrix, scale);
		/*float tmp_angle = glm::radians(angle);
		if (tmp_angle != 0)
		{
			transformMatrix = glm::rotate(transformMatrix, tmp_angle, rotation); //added
			//angle = 0;
		}*/
		if (rotation.x != 0) {
			float tmp_angle = glm::radians(rotation.x);
			transformMatrix = glm::rotate(transformMatrix, tmp_angle,glm::vec3(1.0f,0.0f,0.0f));
		}
		if (rotation.y != 0) {
			float tmp_angle = glm::radians(rotation.y);
			transformMatrix = glm::rotate(transformMatrix, tmp_angle, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (rotation.z != 0) {
			float tmp_angle = glm::radians(rotation.z);
			transformMatrix = glm::rotate(transformMatrix, tmp_angle, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			children[i]->Traverse();
		}

		//pop
		transformMatrix = matCopy;
	}

	static const glm::mat4 GetTransformMatrix()
	{
		return transformMatrix;
	}

	void SetTransformMatrix(glm::mat4 curr)
	{

		transformMatrix = curr;
	}

};