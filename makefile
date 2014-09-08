SDLTest:main.cpp obj3dmodel.cpp mtlLoader.cpp TextureManager.cpp
	g++ -g main.cpp obj3dmodel.cpp mtlLoader.cpp TextureManager.cpp -o SDLTest  -lmingw32 -lSDL2main -lSDL2 -static-libgcc -static-libstdc++ -lopengl32 -lglu32 -lFreeImage
clean:
	rm -fr *.o *.exe *~
