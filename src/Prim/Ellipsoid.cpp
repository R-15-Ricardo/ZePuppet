#include "Ellipsoid.hpp"

#include <iostream>
#include <cmath>
#include <vector>

std::pair<int,int> genS2Mesh(double radius, int precision, float*& vertices, unsigned int*& indices)
{
	int cuts = precision/2;
	vertices = new float [(cuts + 1) * (precision + 1) * 3]; 
	float theta, phi;
	for (int i = 0; i<=cuts; i++)
	{
		theta = M_PI / (precision/2) * i;
		for (int j = 0; j<=precision; j++)
		{
			phi = 2 * M_PI/precision * j;
			float x,y,z;
			x = radius*sin(theta)*cos(phi);
			z = radius*sin(theta)*sin(phi);
			y = radius*cos(theta);

			int indexPosition = 3*(i*(precision + 1) + j);
			//std::cout<<"Pt("<<i<<","<<j<<") : "<<indexPosition<<std::endl;

			vertices[indexPosition] = x;
			vertices[indexPosition + 1] = y;
			vertices[indexPosition + 2] = z;
		}
	}

	std::vector<unsigned int> indexVec;
	int position;
	for (int i = 0; i<=cuts; i++)
	{
		for (int j = 0; j<precision; j++)
		{
			position = i*(precision + 1) + j;
			indexVec.push_back(position);
			position = (i+1)*(precision + 1) + j;
			indexVec.push_back(position);
			position = i*(precision + 1) + (j+1);
			indexVec.push_back(position);

			position = i*(precision + 1) + (j+1);
			indexVec.push_back(position);
			position = (i+1)*(precision + 1) + j;
			indexVec.push_back(position);
			position = (i+1)*(precision + 1) + (j+1);
			indexVec.push_back(position);

		}
	}

	indices = new unsigned int [indexVec.size()];
	int i = 0;
	for (unsigned int p: indexVec)
		indices[i++] = p;

	return std::pair<int,int>((cuts + 1) * (precision + 1), indexVec.size());
}