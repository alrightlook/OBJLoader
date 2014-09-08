#include <string>
#include <vector>
#include "mtlLoader.h"
using namespace std;
struct face
{
	unsigned int v1, v2, v3;
	unsigned int vt1, vt2, vt3;
	unsigned int vn1, vn2, vn3;
	string useMaterialName;
};
class obj3dmodel
{
	private:
		struct Vector
		{
			double x;
			double y;
			double z;
		};

		struct TexCoord
		{
			double u;
			double v;
		};

		struct vertex
		{
			double x;
			double y;
			double z;
		};

	private:
		void ComposeFace(string vertex1, string vertex2, string vertex3, face* face);
	private:
		std::vector<vertex> m_Vertexs;
		std::vector<face>   m_Faces;
		std::vector<TexCoord> m_TexVertexs;
		std::vector<Vector> m_NormalVertexs;

		mtlLoader m_mtlLoader;
	public:
		void Rotate(double ang, double x, double y, double z);
		obj3dmodel();
		~obj3dmodel();
	public:
		void Draw();
		void Parse(std::string filename);
		static void StringSplit(string srcstring, const char* token, vector<string>* outvec);
};
