#include "Controller.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

void ShowCharacterController (Model& Character)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Character Controller", NULL, window_flags);     
	ImGui::SetWindowPos(ImVec2(0, 0));  
	ImGui::SetWindowSize(ImVec2(350, 720));


	static glm::vec3 torsoPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	static glm::vec3 torsoOrientation = glm::vec3(0.0f);

		static glm::vec3 shouldersOrientation = glm::vec3(0.0f);

			static glm::vec3 rightArmOrientation = glm::vec3(0.0f);
				static glm::vec3 rightForearmOrientation = glm::vec3(0.0f);

			static glm::vec3 leftArmOrientation = glm::vec3(0.0f);
				static glm::vec3 leftForearmOrientation = glm::vec3(0.0f);

			static glm::vec3 neckOrientation = glm::vec3(0.0f);
				static glm::vec3 headOrientarion = glm::vec3(0.0f);

		static glm::vec3 hipOrientation = glm::vec3(0.0f);

			static glm::vec3 rightUpperLegOrientation = glm::vec3(0.0f);
				static glm::vec3 rightLowerLegOrientation = glm::vec3(0.0f);
					static glm::vec3 rightFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);

			static glm::vec3 leftUpperLegOrientation = glm::vec3(0.0f);
				static glm::vec3 leftLowerLegOrientation = glm::vec3(0.0f);
					static glm::vec3 leftFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);


	Character.getHead();
	bool torso_open = ImGui::TreeNode("Torso");
	if (torso_open)
	{
		ImGui::Text("Position:");
		ImGui::Text("x");
		ImGui::SliderFloat("##torso.x", &torsoPosition.x, -20.0f, 20.0f);
		ImGui::Text("Y");
		ImGui::SliderFloat("##torso.y", &torsoPosition.y, -20.0f, 20.0f);
		ImGui::Text("Z");
		ImGui::SliderFloat("##torso.z", &torsoPosition.z, -20.0f, 20.0f);
		ImGui::Text("Orientation:");
		ImGui::Text("Yaw");
		ImGui::SliderFloat("##torso.yaw", &torsoOrientation.y, -360.0f, 360.0f);
		ImGui::Text("Pitch");
		ImGui::SliderFloat("##torso.pitch", &torsoOrientation.x, -180.0f, 180.0f);
		ImGui::Text("Roll");
		ImGui::SliderFloat("##torso.roll", &torsoOrientation.z, -360.0f, 360.0f);

		ImGui::Separator();
		ImGui::Text("Children:");
		bool shoulders_open = ImGui::TreeNode("Shoulders");
		if (shoulders_open)
		{
			
			ImGui::Text("Orientation:");
			ImGui::Text("Yaw");
			ImGui::SliderFloat("##shoulders.yaw", &shouldersOrientation.y, -20.0f, 20.0f);
			ImGui::Text("Pitch");
			ImGui::SliderFloat("##shoulders.pitch", &shouldersOrientation.x, -15.0f, 15.0f);
			ImGui::Text("Roll");
			ImGui::SliderFloat("##shoulders.roll", &shouldersOrientation.z, -10.0f, 10.0f);
			ImGui::Separator();
			ImGui::Text("Children:");
			bool neck_open = ImGui::TreeNode("Neck");
			if (neck_open)
			{
				ImGui::Text("Orientation:");
				ImGui::Text("Yaw");
				ImGui::SliderFloat("##neck.yaw", &neckOrientation.y, -90.0f, 90.0f);
				ImGui::Text("Pitch");
				ImGui::SliderFloat("##neck.pitch", &neckOrientation.x, -45.0f, 90.0f);
				ImGui::Separator();
				ImGui::Text("Children:");
				bool head_open = ImGui::TreeNode("head");
				if (head_open)
				{
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			bool rightArm_open = ImGui::TreeNode("Right arm");
			if (rightArm_open)
			{
				ImGui::Text("Orientation:");
				ImGui::Text("Pitch");
				ImGui::SliderFloat("##rightArm.pitch", &rightArmOrientation.x, 45.0f, -180.0f);
				ImGui::Text("Roll");
				ImGui::SliderFloat("##rightArm.roll", &rightArmOrientation.z, -90.0f, 0.0f);
				ImGui::Separator();
				ImGui::Text("Children:");
				bool rightForearm_open = ImGui::TreeNode("Right forearm");
				if (rightForearm_open)
				{
					ImGui::Text("Orientation:");
					ImGui::Text("Yaw");
					ImGui::SliderFloat("##rightForearm.yaw", &rightForearmOrientation.y, -90.0f, 90.0f);
					ImGui::Text("Pitch");
					ImGui::SliderFloat("##rightForearm.pitch", &rightForearmOrientation.x, -90.0f, 0.0f);
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			bool leftArm_open = ImGui::TreeNode("Left arm");
			if (leftArm_open)
			{
				ImGui::Text("Orientation:");
				ImGui::Text("Pitch");
				ImGui::SliderFloat("##leftArm.pitch", &leftArmOrientation.x, 45.0f, -180.0f);
				ImGui::Text("Roll");
				ImGui::SliderFloat("##leftArm.roll", &leftArmOrientation.z, 0.0f, 90.0f);
				ImGui::Separator();
				ImGui::Text("Children:");
				bool leftForearm_open = ImGui::TreeNode("Left forearm");
				if (leftForearm_open)
				{
					ImGui::Text("Orientation:");
					ImGui::Text("Yaw");
					ImGui::SliderFloat("##leftForearm.yaw", &leftForearmOrientation.y, -90.0f, 90.0f);
					ImGui::Text("Pitch");
					ImGui::SliderFloat("##leftForearm.pitch", &leftForearmOrientation.x, -90.0f, 0.0f);
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
		bool hips_open = ImGui::TreeNode("Hips");
		if (hips_open)
		{
			ImGui::Text("Orientation:");
			ImGui::Text("Yaw");
			ImGui::SliderFloat("##shoulders.yaw", &hipOrientation.y, -10.0f, 10.0f);
			ImGui::Separator();
			ImGui::Text("Children:");
			bool rightUpperLeg_open = ImGui::TreeNode("Right upper leg");
			if (rightUpperLeg_open)
			{
				ImGui::Text("Orientation:");
				ImGui::Text("Yaw");
				ImGui::SliderFloat("##rightUpperLeg.yaw", &rightUpperLegOrientation.y, -45.0f, 90.0f);
				ImGui::Text("Pitch");
				ImGui::SliderFloat("##rightUpperLeg.pitch", &rightUpperLegOrientation.x, -90.0f, 45.0f);
				ImGui::Text("Roll");
				ImGui::SliderFloat("##rightUpperLeg.roll", &rightUpperLegOrientation.z, -90.0f, 25.0f);
				ImGui::Separator();
				ImGui::Text("Children:");
				bool rightLowerLeg_open = ImGui::TreeNode("Right lower leg");
				if (rightLowerLeg_open)
				{
					ImGui::Text("Orientation:");
					ImGui::Text("Pitch");
					ImGui::SliderFloat("##rightLowerLeg.pitch", &rightLowerLegOrientation.x, 0.0f, 145.0f);
					ImGui::Separator();
					ImGui::Text("Children:");
					bool rightFoot_open = ImGui::TreeNode("Right foot");
					if (rightFoot_open)
					{
						ImGui::Text("Orientation:");
						ImGui::Text("Pitch");
						ImGui::SliderFloat("##rightFoot.pitch", &rightFootOrientation.x, -90.0f, 0.0f);
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();

			}
			bool leftUpperLeg_open = ImGui::TreeNode("Left upper leg");
			if (leftUpperLeg_open)
			{
				ImGui::Text("Orientation:");
				ImGui::Text("Yaw");
				ImGui::SliderFloat("##leftUpperLeg.yaw", &leftUpperLegOrientation.y, -90.0f, 45.0f);
				ImGui::Text("Pitch");
				ImGui::SliderFloat("##leftUpperLeg.pitch", &leftUpperLegOrientation.x, -90.0f, 45.0f);
				ImGui::Text("Roll");
				ImGui::SliderFloat("##leftUpperLeg.roll", &leftUpperLegOrientation.z, -25.0f, 90.0f);
				ImGui::Separator();
				ImGui::Text("Children:");
				bool leftLowerLeg_open = ImGui::TreeNode("Left lower leg");
				if (leftLowerLeg_open)
				{
					ImGui::Text("Orientation:");
					ImGui::Text("Pitch");
					ImGui::SliderFloat("##leftLowerLeg.pitch", &leftLowerLegOrientation.x, 0.0f, 145.0f);
					ImGui::Separator();
					ImGui::Text("Children:");
					bool leftFoot_open = ImGui::TreeNode("Left foot");
					if(leftFoot_open)
					{
						ImGui::Text("Orientation:");
						ImGui::Text("Pitch");
						ImGui::SliderFloat("##leftFoot.pitch", &leftFootOrientation.x, -90.0f, 0.0f);
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();

	}

	if (ImGui::Button("RESET"))
	{
		torsoPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		torsoOrientation = glm::vec3(0.0f);
		shouldersOrientation = glm::vec3(0.0f);
		rightArmOrientation = glm::vec3(0.0f);
		rightForearmOrientation = glm::vec3(0.0f);
		leftArmOrientation = glm::vec3(0.0f);
		leftForearmOrientation = glm::vec3(0.0f);
		neckOrientation = glm::vec3(0.0f);
		headOrientarion = glm::vec3(0.0f);
		hipOrientation = glm::vec3(0.0f);
		rightUpperLegOrientation = glm::vec3(0.0f);
		rightLowerLegOrientation = glm::vec3(0.0f);
		rightFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
		leftUpperLegOrientation = glm::vec3(0.0f);
		leftLowerLegOrientation = glm::vec3(0.0f);
		leftFootOrientation = glm::vec3(-90.0f, 0.0f, 0.0f);
	}

	Character.updateNode("torso", Model::NodeOperation::frameTranslate, torsoPosition);
	Character.updateNode("torso", Model::NodeOperation::frameOrientate, torsoOrientation);
		Character.updateNode("shoulders", Model::NodeOperation::frameOrientate, shouldersOrientation);
			Character.updateNode("neck", Model::NodeOperation::frameOrientate, neckOrientation);
			Character.updateNode("rightArm", Model::NodeOperation::frameOrientate, rightArmOrientation);
				Character.updateNode("rightForearm", Model::NodeOperation::frameOrientate, rightForearmOrientation);
			Character.updateNode("leftArm", Model::NodeOperation::frameOrientate, leftArmOrientation);
				Character.updateNode("leftForearm", Model::NodeOperation::frameOrientate, leftForearmOrientation);

		Character.updateNode("hips", Model::NodeOperation::frameOrientate, hipOrientation);
			Character.updateNode("rightUpperLeg", Model::NodeOperation::frameOrientate, rightUpperLegOrientation);
				Character.updateNode("rightLowerLeg", Model::NodeOperation::frameOrientate, rightLowerLegOrientation);
					Character.updateNode("rightFoot", Model::NodeOperation::frameOrientate, rightFootOrientation);
			Character.updateNode("leftUpperLeg", Model::NodeOperation::frameOrientate, leftUpperLegOrientation);
				Character.updateNode("leftLowerLeg", Model::NodeOperation::frameOrientate, leftLowerLegOrientation);
					Character.updateNode("leftFoot", Model::NodeOperation::frameOrientate, leftFootOrientation);

	ImGui::End();
}