#pragma once
#include "Resources.h"
#include <fbxsdk.h>
#include <unordered_map>
#include "RenderHeader.h"

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\X32\\debug\\libfbxsdk-md.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\X32\\release\\libfbxsdk-md.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\X64\\debug\\libfbxsdk-md.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\X64\\release\\libfbxsdk-md.lib")
#endif
#endif


class Fbx : public Resources
{

public:
	enum LOADMODE
	{
		CONVERT,
		FBX,
	};

	class FbxKeyFrame
	{
	public:
		Vector4 S; // ũ
		Matrix matTransform;
		double		dTime;
		Vector4 Q; // ȸ�� (���ʹϿ�)
		Vector4 T; // ��
	};

	class FbxBoneKeyFrame
	{
	public:
		int		iBoneIndex;
		std::vector<FbxKeyFrame>	KeyFrame;
	};


	class FbxWeight 
	{
	public:
		int		iIndex;
		double	dWeight;
	};


	class FbxMaterialData
	{
	public:
		Vector4				Dif;
		Vector4				Amb;
		Vector4				Spc;
		Vector4				Emv;
		float				SpecularPower;
		float				TransparencyFactor;
		float				Shininess;
		std::wstring		DifTex;
		std::wstring		BumpTex;
		std::wstring		SpcTex;
	};


	class FbxMeshData 
	{
	public:
		std::vector<Vector4>	vecPos;
		std::vector<Vector4>	vecUV;
		std::vector<Vector4>	vecNormal;
		std::vector<Vector4>	vecTangent;
		std::vector<Vector4>	vecBinormal;
		std::vector<Vector4>	vecBlendWeight; // ���� ����ġ ���� �ִϸ��̼��� ���� ��ŭ ������ �޴���
		std::vector<Vector4>	vecBlendIndex;  // ���� � ���� ������ 
		std::vector<std::vector<UINT>>	vecIndices;
		std::unordered_map<int, std::vector<FbxWeight>>	mapWeights;
		bool				bBump;
		bool				bAnimation;

		FbxMeshData()
		{
			bBump = false;
			bAnimation = false;
		}
	};

	class FbxAniData 
	{
	public:
		std::wstring Name;
		FbxTime StartTime; // �ִϸ��̼� ���۽ð�
		FbxTime EndTime; // �ִϸ��̼� 
		FbxLongLong TimeStartCount; // ���߿��� ����������
		FbxLongLong TimeEndCount; // ���߿��� ������ ������
		FbxLongLong TimeLength; // �� ������ ����
		FbxTime::EMode TimeMode;
		std::vector<FbxBoneKeyFrame>	BoneKeyFrame;

	public:
		FbxAniData() {}
		~FbxAniData() {}
	};

	class FbxBoneData 
	{
	public:
		std::wstring	Name;
		int				iDepth;
		int				iIndex;
		int				iParentIndex;
		Matrix		matOffset;
		Matrix		matBone;

		~FbxBoneData() 
		{
			int a = 0;
		}

	};


private:
	static void FbxInit();

	// ���� ��ü�� ���ϰ� ���Ƴ��� ������ �����͸� ������ ������� ó������� �Ѵ�.
	// �̳༮ ���ӽ����̽��� ������ ���̴�.
	fbxsdk::FbxManager* m_Mgr;
	fbxsdk::FbxIOSettings* m_Ios;
	fbxsdk::FbxScene* m_Scene;
	fbxsdk::FbxImporter* m_Imp;
	fbxsdk::FbxAxisSystem eLocalSpace;


	std::vector<DrawIndex> m_DrawData;
	std::vector<FbxMeshData*> m_MeshData;
	std::vector<FbxBoneData*> m_BoneData;
	std::vector<std::vector<FbxMaterialData*>>	m_MaterialData; // ����� ������ŭ ���� ���̴�.
	std::vector<FbxAniData*> m_AniData;
	std::map<std::wstring, FbxBoneData*> m_BoneDataToName;

public:
	//FbxBoneData* FindBone(const wchar_t* _Name);

	FbxBoneData* FindBone(const wchar_t* _Name);

	std::vector<std::vector<FbxMaterialData*>>& MaterialData()
	{
		return m_MaterialData;
	}

	std::vector<FbxMeshData*>& MeshData()
	{
		return m_MeshData;
	}

	std::vector<FbxAniData*>& AniData()
	{
		return m_AniData;
	}

	std::vector<FbxBoneData*>& BoneData() 
	{
		return m_BoneData;
	}

public:
	bool Load(LOADMODE _Mode);
	bool Load(LOADMODE _Mode, const wchar_t* _BumpName);
	void ConvertToSave(const wchar_t* _FileName);
	void FbxToEngineRes();
	void FbxToEngineRes(const wchar_t* _BumpName);
	int FrameCount(int _AniData);

private:
	bool AniCheck();

private:
	Matrix FbxMatToHMat(const FbxAMatrix& _Mat);
	Vector4 FbxVecToHVec(const FbxVector4& _Vec);
	Vector4 FbxQToHVec4(const FbxQuaternion& _Q);

	void LoadBone(fbxsdk::FbxNode* _Node, int iDepth = 0, int iIndex = 0, int _iParentIndex = -1);

	std::wstring GetMaterialTexture(FbxSurfaceMaterial * pMtrl, const char * pPropertyName);
	double GetMaterialFactor(FbxSurfaceMaterial * pMtrl, const char * pPropertyName);
	Vector4 GetMaterialColor(FbxSurfaceMaterial * pMtrl, const char * pPropertyName, const char * pPropertyFactorName);
	void LoadMaterial(FbxSurfaceMaterial * pMtrl);
	void Trangulate(fbxsdk::FbxNode* _Node);

	void LoadMesh(fbxsdk::FbxNode* _Node);

	void LoadMeshData(fbxsdk::FbxMesh* _Mesh);
	void LoadOffsetMatrix(FbxCluster * _Cluster, const FbxAMatrix& _matTransform, int _iBoneIndex, Fbx::FbxMeshData* _Container);
	void LoadWeightAndIndex(FbxCluster * pCluster, int iBoneIndex, FbxMeshData* pContainer);
	void LoadAnimation(FbxMesh * pMesh, FbxMeshData* _pContainer);
	void LoadTimeTransform(FbxNode * pNode,	FbxCluster * pCluster, const FbxAMatrix& matTransform, int iBoneIndex);
	void ChangeWeightAndIndices(FbxMeshData* _Container);

	void LoadNormal(FbxMesh * pMesh, FbxMeshData* pContainer, int iVtxID, int iControlIndex);
	void LoadUV(FbxMesh * pMesh, FbxMeshData* pContainer, int iUVID, int iControlIndex);
	void LoadTangent(FbxMesh * pMesh, FbxMeshData* pContainer, int iVtxID, int iControlIndex);
	void LoadBinormal(FbxMesh * pMesh, FbxMeshData* pContainer, int iVtxID, int iControlIndex);

	void Release();

	void ConvertDataLoad();




public:
	Fbx();
	~Fbx();
};

