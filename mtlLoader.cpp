#include "mtlLoader.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "TextureManager.h"
#include <gl/gl.h>

int mtlLoader::m_sTextureID(1);

mtlLoader::mtlLoader()
{
}

mtlLoader::~mtlLoader()
{
}

void mtlLoader::Parse(string filename)
{
	std::string s;
	ifstream fin(filename.c_str());
	if(!fin) {
		std::cout<<"Cannot open the file"<<std::endl;
		return;
	}
	while( !fin.eof())
	{
		if(strcmp(s.c_str(), "newmtl") != 0) {
			fin>>s;
		}
		if(strcmp(s.c_str(), "newmtl") == 0) {
			Material material;
			string materialname;
			fin>>materialname;
			material.MaterialName = materialname;
			std::cout<<"The mertial name is:" <<materialname<<endl;
			while( fin>> s && strcmp( s.c_str(), "newmtl") != 0) {
				if(strcmp(s.c_str(), "Ka") == 0) {
					fin>>material.KA[0]>>material.KA[1]>>material.KA[2];
					std::cout<<material.KA[0]<<material.KA[1]<<material.KA[2]<<std::endl;
				}
				else if( strcmp(s.c_str(), "Kd") == 0) {
					fin>>material.KD[0]>>material.KD[1]>>material.KD[2];
					std::cout<<material.KD[0]<<material.KD[1]<<material.KD[2]<<std::endl;
				}
				else if( strcmp(s.c_str(), "map_Ka") == 0) {
					fin>>material.map_Ka;
					std::cout<<material.map_Ka<<std::endl;
					bool res = TextureManager::Inst()->LoadTexture(material.map_Ka.c_str(), m_sTextureID, GL_RGBA);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					material.TextureID = m_sTextureID;
				}
				else if( strcmp(s.c_str(), "map_Kd") == 0) {
					fin>>material.map_Kd;
					std::cout<<material.map_Kd<<std::endl;
					bool res = TextureManager::Inst()->LoadTexture(material.map_Kd.c_str(), m_sTextureID, GL_RGBA);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					material.TextureID = m_sTextureID;
					m_sTextureID ++;
				}
			}
			m_mapMaterials.insert(make_pair(materialname, material));
		}
		

	}

}
