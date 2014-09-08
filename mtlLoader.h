#ifndef MTLLOADER_HEADER
#define MTLLOADER_HEADER
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Material
{
	int TextureID;
	string MaterialName;
	float KA[3];
	float KD[3];
	string map_Ka;
	string map_Kd;
};

class mtlLoader
{
	public:
		mtlLoader();
		~mtlLoader();
	public:
		void Parse(string filename);
	public:
		map<string, Material> m_mapMaterials;
	private:
		static int m_sTextureID;
};
#endif
