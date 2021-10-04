IMGUIOBJ = 

all: ZePuppet

ZePuppet: main.o Renderer.o Vertex.o Shader.o Ellipsoid.o Camera.o Model.o Controller.o
	 g++ main.o Renderer.o Vertex.o Shader.o Ellipsoid.o Camera.o Model.o Controller.o $(SRCS) -o ZePuppet -lglfw -lGL -lGLEW; rm main.o Renderer.o Vertex.o Shader.o Ellipsoid.o Camera.o Model.o Controller.o

# --------------- GLAux includes --------------- 
Renderer.o: GLAux/Renderer.cpp
	g++ -c GLAux/Renderer.cpp

Vertex.o: GLAux/Vertex.cpp
	g++ -c GLAux/Vertex.cpp

Shader.o: GLAux/Shader.cpp
	g++ -c GLAux/Shader.cpp

# --------------- Prim includes --------------- 
Ellipsoid.o: Prim/Ellipsoid.cpp
	g++  -I ../ -c Prim/Ellipsoid.cpp

Camera.o: Prim/Camera.cpp
	g++  -I ../ -c Prim/Camera.cpp

# --------------- Model includes --------------- 
Model.o: Model/Model.cpp
	g++  -I ../ -c Model/Model.cpp

#
Controller.o: CharacterController/Controller.cpp
	g++ -I ../ -c CharacterController/Controller.cpp

# --------------- ImGUI includes --------------- 

SRCS := $(wildcard imgui/*.o)

# --------------- Main file --------------- 
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf main.o Renderer.o Vertex.o Shader.o Ellipsoid.o Camera.o Model.o

clear:
	rm -rf main.o Renderer.o Vertex.o Shader.o Ellipsoid.o Camera.o Model.o main