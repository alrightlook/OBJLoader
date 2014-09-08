#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "obj3dmodel.h"
#include <SDL_opengl.h>
#include "mtlLoader.h"
#include "TextureManager.h"

using namespace std;
obj3dmodel::obj3dmodel()
{
}

obj3dmodel::~obj3dmodel()
{
}

void obj3dmodel::StringSplit(string srcstring, const char* token, vector<string>* outvec)
{
	//cout<<srcstring<<endl;
	if(outvec->size() != 0)
	{
		outvec->clear();
	}
	char* srcchar = new char[srcstring.size() + 1];
	strcpy(srcchar, srcstring.c_str());
	char* p = NULL;
	p = strtok(srcchar ,token);
	while(p)
	{
		outvec->push_back(p);
		p = strtok (NULL, token);
	}
	delete srcchar;

}

void obj3dmodel::ComposeFace(string vertex1, string vertex2, string vertex3, face* face)
{
	vector<string> outvec;
	StringSplit(vertex1, "/", &outvec);
/*	for (int i = 0; i < outvec.size(); i++)
	{
		cout<<outvec.at(i)<<endl;
	}
	*/
	face->v1 = atoi(outvec.at(0).c_str());
	face->vt1 = atoi(outvec.at(1).c_str());
	face->vn1 = atoi(outvec.at(2).c_str());

	StringSplit(vertex2, "/", &outvec);
	face->v2 = atoi(outvec.at(0).c_str());
	face->vt2 = atoi(outvec.at(1).c_str());
	face->vn2 = atoi(outvec.at(2).c_str());

	StringSplit(vertex3, "/", &outvec);
	face->v3 = atoi(outvec.at(0).c_str());
	face->vt3 = atoi(outvec.at(1).c_str());
	face->vn3 = atoi(outvec.at(2).c_str());
}
void obj3dmodel::Parse(std::string filename)
{
	std::string s;
	ifstream fin(filename.c_str()); 
	if(!fin) {
		cout<<"Can not open the file"<<endl;
		return ;
	}
	std::string useMtl;
	while (fin>>s)
	{
		//cout<<"the s is:"<<s<<endl;
		if(strcmp (s.c_str(), "v")== 0)
		{
			string x, y, z;
			vertex v;
			fin>>x>>y>>z;
			v.x = atof(x.c_str()); 
			v.y = atof(y.c_str());
			v.z = atof(z.c_str());
			//cout<<"v:"<<v.x<<" "<<v.y<<" "<<v.z<<endl;
			this->m_Vertexs.push_back(v);
		}
		else if (strcmp (s.c_str(), "vt")==0)
		{
			vertex v;
			TexCoord tc;
			string x, y, z;
			fin>>x>>y>>z;
			v.x = atof(x.c_str()); 
			v.y = atof(y.c_str());
			v.z = atof(z.c_str());
			tc.u = v.x; 
			tc.v = v.y;
			//cout<<"VT:"<<v.x<<v.y<<v.z<<endl;
			this->m_TexVertexs.push_back(tc);
		} 
		else if (strcmp(s.c_str(), "vn")== 0)
		{
			Vector v;
			fin>>v.x>>v.y>>v.z;
			//cout<<"VN:"<<v.x<<v.y<<v.z<<endl;
			this->m_NormalVertexs.push_back(v);
		}
		else if (strcmp( s.c_str() ,"f")==0)
		{
			face f;
			f.useMaterialName = useMtl;
			string vertex1, vertex2, vertex3;
			fin>>vertex1>>vertex2>>vertex3;
			ComposeFace(vertex1, vertex2, vertex3, &f);
			//cout<<"f:"<<f.v1<<f.v2<<f.v3<<endl;
			this->m_Faces.push_back(f);
					
		}
		else if(strcmp(s.c_str(), "mtllib") == 0) {
			mtlLoader mtlloader;
			string mtlfile;
			fin>>mtlfile;
			cout<<"The mtl file is "<< mtlfile<<endl;
			mtlloader.Parse(mtlfile);
			m_mtlLoader = mtlloader;
		}
		else if(strcmp(s.c_str(), "usemtl") == 0 ) {
			fin>>useMtl;
		}
	}
	cout<<"Total v account:"<<m_Vertexs.size()<<endl;
	cout<<"Total vt account:"<<m_TexVertexs.size()<<endl;
	cout<<"Total vn account:"<<m_NormalVertexs.size()<<endl;
	cout<<"Total faces account:"<<m_Faces.size()<<endl;
	
}

void obj3dmodel::Rotate(double ang, double x, double y, double z)
{
	glRotatef(ang, x, y, z);
}
void obj3dmodel::Draw()
{
	glBegin(GL_TRIANGLES);
	int nLastTextureID = -1;
	for (int i = 0 ; i < m_Faces.size(); i++)
	{
		Material mat = m_mtlLoader.m_mapMaterials.find(m_Faces.at(i).useMaterialName)->second;
		nLastTextureID = mat.TextureID;
		if (nLastTextureID == 1) 
		{
			//std::cout<<"haha"<<std::endl;
		}
		TextureManager::Inst()->BindTexture(nLastTextureID);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat.KA);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat.KD);
		vertex v1 = m_Vertexs.at(m_Faces.at(i).v1 - 1);
		vertex v2 = m_Vertexs.at(m_Faces.at(i).v2 - 1);
		vertex v3 = m_Vertexs.at(m_Faces.at(i).v3 - 1);

		Vector vn1 = m_NormalVertexs.at(m_Faces.at(i).vn1 -1);
		Vector vn2 = m_NormalVertexs.at(m_Faces.at(i).vn2 -1);
		Vector vn3 = m_NormalVertexs.at(m_Faces.at(i).vn3 -1);

		TexCoord tc1 = m_TexVertexs.at(m_Faces.at(i).vt1 -1);
		TexCoord tc2 = m_TexVertexs.at(m_Faces.at(i).vt2 -1);
		TexCoord tc3 = m_TexVertexs.at(m_Faces.at(i).vt3 -1);

		glNormal3f(vn1.x, vn1.y, vn1.z);
		glTexCoord2f(tc1.u, tc1.v);
		glVertex3f(v1.x, v1.y, v1.z);

		//glNormal3f(vn2.x, vn2.y, vn2.z);
		glTexCoord2f(tc2.u, tc2.v);
		glVertex3f(v2.x, v2.y, v2.z);

		//glNormal3f(vn3.x, vn3.y, vn3.z);
		glTexCoord2f(tc3.u, tc3.v);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glEnd();

}
