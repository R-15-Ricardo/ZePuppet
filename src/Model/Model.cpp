#include "Model.hpp"

#include <iostream>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

//------------------- ModelNode definitions -------------------
ModelNode::ModelNode(const std::string& name, Ellipsoid section)
{
	this->partId = name;
	this->shape = section;
	this->endEffector = true;
}

//------------------- Model definitions -------------------
Model::Model(Ellipsoid primitive)
{
	ModelNode OnlyNode("head", primitive);
	this->head = OnlyNode;
}

Model::Model(const std::string& id, Ellipsoid primitive)
{
	ModelNode HeadNode(id, primitive);
	this->head = HeadNode;
}

void Model::addNode(const std::string& after, ModelNode node)
{
	std::stack<ModelNode*> NodeStack;
	NodeStack.push(&(this->head));

	while (!NodeStack.empty())
	{
		ModelNode* now = NodeStack.top();
		NodeStack.pop();

		if (now->partId == after)
		{
			now->children.push_back(node);
			std::cout<<"[Model::addNode()] successfuly added "<<node.partId<<" to "<<after<<"."<<std::endl;
			return;
		}

		for (ModelNode& child : now->children)
		{
			NodeStack.push(&(child));
		}
	}

	std::cout<<"[Model::addNode()] Parent ID not found!!"<<std::endl;
}

void Model::updateNode(const std::string& nodeId, NodeOperation op, glm::vec3 data)
{
	std::stack<ModelNode*> NodeStack;
	NodeStack.push(&(this->head));

	while (!NodeStack.empty())
	{
		ModelNode* now = NodeStack.top();
		NodeStack.pop();

		if (now->partId == nodeId)
		{
			switch (op)
			{
				case NodeOperation::frameOrientate:
					now->shape.frameOrientation = data;
					break;
				
				case NodeOperation::frameScale:
					now->shape.frameScale = data;
					break;

				case NodeOperation::frameTranslate:
					now->shape.framePosition = data;
					break;

				case NodeOperation::objectOrientate:
					now->shape.objectOrientation = data;
					break;

				case NodeOperation::objectScale:
					now->shape.objectScale = data;
					break;
				
				case NodeOperation::objectTranslate:
					now->shape.objectPosition = data;
					break;

				default:
					std::cout<<"[Model::addNode()] Ivalid Operation!"<<std::endl;
					break;
			}
			//std::cout<<"[Model::addNode()] successfuly updated "<<nodeId<<"."<<std::endl;
			return;
		}

		for (ModelNode& child : now->children)
		{
			NodeStack.push(&(child));
		}
	}

	std::cout<<"[Model::addNode()] Object ID not found!!"<<std::endl;
	std::cout<<"                   No Nodes were updated"<<std::endl;
}

void Model::draw(Renderer renderer, VertexArray& va, IndexBuffer& ib, Shader& shader)
{
	std::stack<ModelNode> NodeStack;
	std::stack<glm::mat4> FrameStack;

	NodeStack.push(this->head);
	FrameStack.push(glm::mat4(1.0f));
	
	while(!NodeStack.empty())
	{
		ModelNode nowNode = NodeStack.top();
		glm::mat4 parentFrame = FrameStack.top();
		NodeStack.pop();
		FrameStack.pop();

		glm::mat4 A = glm::mat4(1.0f); 
		A *= glm::translate(nowNode.shape.framePosition);

		float yaw, pitch, roll;
		yaw = glm::radians(nowNode.shape.frameOrientation.y);
		pitch = glm::radians(nowNode.shape.frameOrientation.x);
		roll = glm::radians(nowNode.shape.frameOrientation.z);

		A *= glm::eulerAngleYXZ(yaw,pitch,roll);
		A *= glm::scale(nowNode.shape.frameScale);

		glm::mat4 objectFrame = parentFrame*A;
		
		glm::mat4 B = glm::mat4(1.0f);
		B *= glm::translate(nowNode.shape.objectPosition);

		yaw = nowNode.shape.objectOrientation.y;
		pitch = nowNode.shape.objectOrientation.x;
		roll = nowNode.shape.objectOrientation.z;

		B *= glm::eulerAngleXYZ(yaw,pitch,roll);
		B *= glm::scale(nowNode.shape.objectScale);

		glm::mat4 nowFrame = parentFrame*A;
		glm::mat4 modelMatrix = nowFrame*B;

		//std::cout<<"Drawing \""<<nowNode.partId<<"\" "<<std::endl;

		shader.Bind();
		shader.SetUniformMat4f("f_Model", modelMatrix);
		shader.SetUniform4f("u_ObjectColor", nowNode.shape.color);

		renderer.Draw(va,ib,shader);

		for (ModelNode child : nowNode.children)
		{
			NodeStack.push(child);
			FrameStack.push(nowFrame);
		}
	}
}

Model ZePuppet ()
{
	Ellipsoid torso;
	torso.framePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	torso.objectScale = glm::vec3(1.0f, 2.0f, 0.5f);

		Ellipsoid shoulders;
		shoulders.framePosition = glm::vec3(0.0f, 2.0f, 0.0f);
		shoulders.objectScale = glm::vec3(2.0f, 0.5f, 0.5f);
		shoulders.objectPosition = glm::vec3(0.0f, 0.5f, 0.0f);

			Ellipsoid neck;
			neck.framePosition = glm::vec3(0.0f, 1.0f, 0.0f); 
			neck.objectScale = glm::vec3(0.25f, 0.5f, 0.25f);
			neck.objectPosition = glm::vec3(0.0f, 0.5f, 0.0f);

				Ellipsoid head;
				head.framePosition = glm::vec3(0.0f, 1.0f, 0.0f); 
				head.objectScale = glm::vec3(1.25f, 1.25f, 1.25f); 
				head.objectPosition = glm::vec3(0.0f, 1.25f, 0.0f); 

					Ellipsoid nose;
					nose.framePosition = glm::vec3(0.0f, 1.25f, 1.25f); 
					nose.objectScale = glm::vec3(0.15f, 0.15f, 0.15f);


			Ellipsoid rightArm;
			rightArm.framePosition = glm::vec3(-2.0f, 0.5f, 0.0f); 
			rightArm.objectScale = glm::vec3(0.5f, 1.5f, 0.5f);
			rightArm.objectPosition = glm::vec3(0.0f, -1.5f, 0.0f);

				Ellipsoid rightForearm;
				rightForearm.framePosition = glm::vec3(0.0f, -3.0f, 0.0f); 
				rightForearm.objectScale = glm::vec3(0.5f, 1.5f, 0.5f);
				rightForearm.objectPosition = glm::vec3(0.0f, -1.5f, 0.0f);

			Ellipsoid leftArm;
			leftArm.framePosition = glm::vec3(2.0f, 0.5f, 0.0f); 
			leftArm.objectScale = glm::vec3(0.5f, 1.5f, 0.5f);
			leftArm.objectPosition = glm::vec3(0.0f, -1.5f, 0.0f);

				Ellipsoid leftForearm;
				leftForearm.framePosition = glm::vec3(0.0f, -3.0f, 0.0f);  
				leftForearm.objectScale = glm::vec3(0.5f, 1.5f, 0.5f);
				leftForearm.objectPosition = glm::vec3(0.0f, -1.5f, 0.0f);
		
		Ellipsoid hips;
		hips.framePosition = glm::vec3(0.0f, -2.0f, 0.0f); 
		hips.objectScale = glm::vec3(1.0f, 0.5f, 0.5f);
		hips.objectPosition = glm::vec3(0.0f, -0.5f, 0.0f);

			Ellipsoid rightUpperLeg;
			rightUpperLeg.framePosition = glm::vec3(-1.0f, -0.5f, 0.0f); 
			rightUpperLeg.objectScale = glm::vec3(0.5f, 1.75f, 0.5f);
			rightUpperLeg.objectPosition = glm::vec3(0.0f, -1.75f, 0.0f);

				Ellipsoid rightLowerLeg;
				rightLowerLeg.framePosition = glm::vec3(0.0f, -3.5f, 0.0f); 
				rightLowerLeg.objectScale = glm::vec3(0.5f, 1.25f, 0.5f);
				rightLowerLeg.objectPosition = glm::vec3(0.0f, -1.25f, 0.0f);

					Ellipsoid rightFoot;
					rightFoot.framePosition = glm::vec3(0.0f, -2.5f, 0.0f); 
					rightFoot.frameOrientation = glm::vec3(-90.0f, 0.0f,0.0f);
					rightFoot.objectScale = glm::vec3(0.25f, 0.75f, 0.25f);
					rightFoot.objectPosition = glm::vec3(0.0f, -0.75f, 0.0f);

			Ellipsoid leftUpperLeg;
			leftUpperLeg.framePosition = glm::vec3(1.0f, -0.5f, 0.0f); 
			leftUpperLeg.objectScale = glm::vec3(0.5f, 1.75f, 0.5f);
			leftUpperLeg.objectPosition = glm::vec3(0.0f, -1.75f, 0.0f);

				Ellipsoid leftLowerLeg;
				leftLowerLeg.framePosition = glm::vec3(0.0f, -3.5f, 0.0f); 
				leftLowerLeg.objectScale = glm::vec3(0.5f, 1.25f, 0.5f);
				leftLowerLeg.objectPosition = glm::vec3(0.0f, -1.25f, 0.0f);

					Ellipsoid leftFoot;
					leftFoot.framePosition = glm::vec3(0.0f, -2.5f, 0.0f); 
					leftFoot.frameOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
					leftFoot.objectScale = glm::vec3(0.25f, 0.75f, 0.25f);
					leftFoot.objectPosition = glm::vec3(0.0f, -0.75f, 0.0f);

	Model model("torso", torso);
		model.addNode("torso", ModelNode("shoulders", shoulders));
			model.addNode("shoulders", ModelNode("rightArm", rightArm));
				model.addNode("rightArm", ModelNode("rightForearm", rightForearm));
			model.addNode("shoulders", ModelNode("leftArm", leftArm));
				model.addNode("leftArm", ModelNode("leftForearm", leftForearm));
			model.addNode("shoulders", ModelNode("neck", neck));
				model.addNode("neck", ModelNode("head", head));
					model.addNode("head", ModelNode("nose", nose));

		model.addNode("torso", ModelNode("hips", hips));
			model.addNode("hips", ModelNode("rightUpperLeg", rightUpperLeg));
				model.addNode("rightUpperLeg", ModelNode("rightLowerLeg", rightLowerLeg));
					model.addNode("rightLowerLeg", ModelNode("rightFoot", rightFoot));
			model.addNode("hips", ModelNode("leftUpperLeg", leftUpperLeg));
				model.addNode("leftUpperLeg", ModelNode("leftLowerLeg", leftLowerLeg));
					model.addNode("leftLowerLeg", ModelNode("leftFoot", leftFoot));

	return model;
}


