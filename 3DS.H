#ifndef _3DS_H
#define _3DS_H
//#include <gl\GL.h>
//#include <gl\GLU.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <gl\gl.h>										
#include <gl\glu.h>										
#include <gl\glaux.h>
#include <crtdbg.h>
#pragma comment(lib, "glaux.lib")
using namespace std;

//  ������(Primary Chunk)��λ���ļ��Ŀ�ʼ
#define PRIMARY       0x4D4D

//  ����(Main Chunks)
#define OBJECTINFO    0x3D3D				// �������İ汾��
#define VERSION       0x0002				// .3ds�ļ��İ汾
#define EDITKEYFRAME  0xB000				// ���йؼ�֡��Ϣ��ͷ��

//  ����Ĵμ�����(��������Ĳ��ʺͶ���
#define MATERIAL	  0xAFFF				// ����������Ϣ
#define OBJECT		  0x4000				// ���������桢�������Ϣ

//  ���ʵĴμ�����
#define MATNAME       0xA000				// �����������
#define MATDIFFUSE    0xA020				// ����/���ʵ���ɫ
#define MATMAP        0xA200				// �²��ʵ�ͷ��
#define MATMAPFILE    0xA300				// �����������ļ���

#define OBJECT_MESH   0x4100				// �µ��������

//  OBJECT_MESH�Ĵμ�����
#define OBJECT_VERTICES     0x4110			// ���󶥵�
#define OBJECT_FACES		0x4120			// �������
#define OBJECT_MATERIAL		0x4130			// ����Ĳ���
#define OBJECT_UV			0x4140			// �����UV��������
#define SCREEN_WIDTH 400								
#define SCREEN_HEIGHT 300								
#define SCREEN_DEPTH 16									


#define MAX_TEXTURES 100								// ����������Ŀ

// ����3D����࣬���ڱ���ģ���еĶ���
class CVector3 
{
public:
	float x, y, z;
};

// ����2D���࣬���ڱ���ģ�͵�UV��������
class CVector2 
{
public:
	float x, y;
};

//  ��Ľṹ����
struct tFace
{
	int vertIndex[3];			// ��������
	int coordIndex[3];			// ������������
};

//  ������Ϣ�ṹ��
struct tMaterialInfo
{
	char  strName[255];			// ��������
	char  strFile[255];			// �����������ӳ�䣬���ʾ�����ļ�����
	BYTE  color[3];				// �����RGB��ɫ
	int   texureId;				// ����ID
	float uTile;				// u �ظ�
	float vTile;				// v �ظ�
	float uOffset;			    // u ����ƫ��
	float vOffset;				// v ����ƫ��
} ;

//  ������Ϣ�ṹ��
struct t3DObject 
{
	int  numOfVerts;			// ģ���ж������Ŀ
	int  numOfFaces;			// ģ���������Ŀ
	int  numTexVertex;			// ģ���������������Ŀ
	int  materialID;			// ����ID
	bool bHasTexture;			// �Ƿ��������ӳ��
	char strName[255];			// ���������
	CVector3  *pVerts;			// ����Ķ���
	CVector3  *pNormals;		// ����ķ�����
	CVector2  *pTexVerts;		// ����UV����
	tFace *pFaces;				// ���������Ϣ
};

//  ģ����Ϣ�ṹ��
struct t3DModel 
{
	t3DModel()
	{
		numOfObjects=0;
		numOfMaterials=0;
	}

	int numOfObjects;					// ģ���ж������Ŀ
	int numOfMaterials;					// ģ���в��ʵ���Ŀ
	vector<tMaterialInfo> pMaterials;	// ����������Ϣ
	vector<t3DObject> pObject;			// ģ���ж���������Ϣ
};
struct tIndices 
{							
	unsigned short a, b, c, bVisible;	
};

// �������Ϣ�Ľṹ
struct tChunk
{
	unsigned short int ID;					// ���ID		
	unsigned int length;					// ��ĳ���
	unsigned int bytesRead;					// ��Ҫ���Ŀ����ݵ��ֽ���
};

// CLoad3DS�ദ�����е�װ�����
class CLoad3DS
{
public:
	CLoad3DS();								// ��ʼ�����ݳ�Ա
	// װ��3ds�ļ���ģ�ͽṹ��
	bool Import3DS(t3DModel *pModel, const char *strFileName);

private:
	// ��һ���ַ���
	int GetString(char *);
	// ����һ����
	void ReadChunk(tChunk *);
	// ����һ����
	void ProcessNextChunk(t3DModel *pModel, tChunk *);
	// ����һ�������
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);
	// ����һ�����ʿ�
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);
	// ��������ɫ��RGBֵ
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk);
	// ������Ķ���
	void ReadVertices(t3DObject *pObject, tChunk *);
	// �����������Ϣ
	void ReadVertexIndices(t3DObject *pObject, tChunk *);
	// ���������������
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);
	// ���������Ĳ�������
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk);
	// ������󶥵�ķ�����
	void ComputeNormals(t3DModel *pModel);
	// �ر��ļ����ͷ��ڴ�ռ�
	void CleanUp();
	// �ļ�ָ��
	FILE *m_FilePointer;

	tChunk *m_CurrentChunk;
	tChunk *m_TempChunk;
};




#endif

