#pragma once
#include <string>
#include <vector>
#include <stack>

#include "../GLAux/Renderer.hpp"
#include "../Prim/Ellipsoid.hpp"

class ModelNode {
	public:
		ModelNode() {};
		ModelNode(const std::string& name, Ellipsoid section);

		std::string partId;
		Ellipsoid shape;
		std::vector<ModelNode> children;
		bool endEffector;
};


class Model {
	public:
		enum NodeOperation {
			frameScale, frameTranslate, frameOrientate,
			objectScale, objectTranslate, objectOrientate
		};

		Model(Ellipsoid primitive);
		Model(const std::string& id, Ellipsoid primitive);

		ModelNode getHead() {
			return head;
		}

		void addNode(const std::string& after, ModelNode node);
		void updateNode(const std::string& nodeId, NodeOperation op, glm::vec3 data);
		void draw(Renderer renderer, VertexArray& va, IndexBuffer& ib, Shader& shader);
	private:
		ModelNode head;
};

Model ZePuppet ();