#include <Graphics\Inc\Graphics.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <iostream>

using namespace SWGE;
using namespace Graphics;

void Pause()
{
	std::cout << "Press <Enter> to continue...\n";
	std::cin.ignore();
	std::cin.get();
}

namespace
{
	Model nsModel;
	AnimationModel nsAnimModel;
	BoneAnimation nsBoneAnim;

	bool hasBones{ false };
}

#define VerifyOrThrow(condition, message)\
if((condition))\
{\
	throw std::exception(message);\
}

struct Params
{
	Params()
		: inputFileName(nullptr)
		, outputFileName(nullptr)
	{}
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
};

void PrintHelp()
{
	printf(
		"== ModelService Help ==\n"
		"\n"
		"Usage:\n"
		"\n"
		"	ModelService.exe <InputFile> <OutputFile>\n"
		"\n"
	);
}

Params ParseArg(int argc, char*argv[])
{
	//VerifyOrThrow((argc < 3), "Invalid number of arguments.");
	Params params;
	//params.inputFileName = argv[argc - 2];
	//params.outputFileName = argv[argc - 1];
	return params;
}

Math::Matrix4 Convert(aiMatrix4x4 aiM)
{
	Math::Matrix4 m;

	m._11 = aiM.a1; m._12 = aiM.a2; m._13 = aiM.a3; m._14 = aiM.a4;
	m._21 = aiM.b1; m._22 = aiM.b2; m._23 = aiM.b3; m._24 = aiM.b4;
	m._31 = aiM.c1; m._32 = aiM.c2; m._33 = aiM.c3; m._34 = aiM.c4;
	m._41 = aiM.d1; m._42 = aiM.d2; m._43 = aiM.d3; m._44 = aiM.d4;

	return m;
}

Bone* BuildSkeleton(aiNode& node, Bone* parent)
{
	Bone* bone = nullptr;
	auto iter = nsAnimModel.mBoneIndexMap.find(node.mName.C_Str());
	if(iter == nsAnimModel.mBoneIndexMap.end())
	{
		const uint32_t boneIndex = static_cast<uint32_t>(nsAnimModel.mBones.size());
		
		// We need to add a new bone
		bone = new Bone();
		bone->mIndex = boneIndex;
		bone->offsetTransform = Math::Matrix4::Identity();
	
		if(node.mName.length > 0)
		{
			bone->name = node.mName.C_Str();
		}
		else
		{
			char buffer[128];
			sprintf_s(buffer, std::size(buffer), "unamed_%u", boneIndex);
			printf("Warning: Bone %u has no name, renamed to %s\n", boneIndex, buffer);
			bone->name = buffer;
		}
	
		nsAnimModel.mBones.push_back(bone);
		nsAnimModel.mBoneIndexMap.insert(std::make_pair(bone->name, bone->mIndex));
	}
	else
	{
		bone = nsAnimModel.mBones[iter->second];
	}
	/*
	nsAnimModel.mBones.push_back(bone);
	nsAnimModel.mBoneIndexMap.try_emplace(bone->name, bone->mIndex);*/
	bone->transform = Convert(node.mTransformation);
	bone->parent = parent;
	
	for(uint32_t i = 0; i < node.mNumChildren; ++i)
	{
		Bone* child = child = BuildSkeleton(*(node.mChildren[i]), bone);
		bone->children.emplace_back(child);
	}
	return bone;

}


uint32_t GetBoneIndex(aiBone* bone, int i)
{
	auto iter = nsAnimModel.mBoneIndexMap.find(bone->mName.C_Str());
	if(iter != nsAnimModel.mBoneIndexMap.end())
	{
		return iter->second;
	}

	Bone* newBone = new Bone();
	newBone->name = bone->mName.C_Str();
	newBone->mIndex = static_cast<int>(nsAnimModel.mBones.size());
	newBone->offsetTransform = Convert(bone->mOffsetMatrix);

	nsAnimModel.mBones.push_back(newBone);
	nsAnimModel.mBoneIndexMap.insert(std::make_pair(newBone->name, newBone->mIndex));

	return newBone->mIndex;
}

void ImportModel(const Params& params)
{
	//Create an instance of the Importer Class

	Assimp::Importer importer;

	//And have it read the given file with some example of postprocessing
	// Usuall - if speed is not the most important aspect f

	const uint32_t flags =
		aiProcessPreset_TargetRealtime_Quality |
		aiProcess_ConvertToLeftHanded;

	const aiScene* scene = importer.ReadFile(/*params.inputFileName*/"B:/Visual_Studio_Projects/SWGE/Assets/Models/AnimationDemo/NorthernSoulSpin_ASCII.fbx", flags);

	//if the import failed, report it
	VerifyOrThrow(scene == nullptr, importer.GetErrorString());

	//FILE* file = nullptr;
	//auto error = fopen_s(&file, params.outputFileName, "bw");

	// Read Mesh Data
	if (scene->HasMeshes())
	{
		std::cout << "Reading Mesh Data...\n";

		nsModel.mMesh.resize(scene->mNumMeshes);
		nsModel.mMaterialIndex.resize(scene->mNumMeshes);

		nsAnimModel.mSkinMesh.resize(scene->mNumMeshes);
		nsAnimModel.mMaterialIndex.resize(scene->mNumMeshes);

		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			const aiMesh* inputMesh = scene->mMeshes[meshIndex];
			auto vertices = std::make_unique<SWGE::Graphics::Vertex[]>(inputMesh->mNumVertices);
			auto boneVertices = std::make_unique<SWGE::Graphics::BoneVertex[]>(inputMesh->mNumVertices);

			std::cout << "Reading Positions...\n";
			//Position
			for (uint32_t i = 0; i < inputMesh->mNumVertices; i++)
			{
				if (inputMesh->HasBones())
				{
					hasBones = true;
					auto& boneVertex = boneVertices[i];
					boneVertex.position.x = inputMesh->mVertices[i].x;
					boneVertex.position.y = inputMesh->mVertices[i].y;
					boneVertex.position.z = inputMesh->mVertices[i].z;
				}
				else
				{
					auto& vertex = vertices[i];
					vertex.position.x = inputMesh->mVertices[i].x;
					vertex.position.y = inputMesh->mVertices[i].y;
					vertex.position.z = inputMesh->mVertices[i].z;
				}
			}

			std::cout << "Reading Normals...\n";
			for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
			{
				if (hasBones)
				{
					auto& boneVertex = boneVertices[i];
					boneVertex.normal.x = inputMesh->mNormals[i].x;
					boneVertex.normal.y = inputMesh->mNormals[i].y;
					boneVertex.normal.z = inputMesh->mNormals[i].z;
				}
				else
				{
					auto& vertex = vertices[i];
					vertex.normal.x = inputMesh->mNormals[i].x;
					vertex.normal.y = inputMesh->mNormals[i].y;
					vertex.normal.z = inputMesh->mNormals[i].z;
				}
			}
			std::cout << "Reading Tangents...\n";
			for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
			{
				if (hasBones)
				{
					auto& boneVertex = boneVertices[i];
					boneVertex.tangent.x = inputMesh->mTangents[i].x;
					boneVertex.tangent.y = inputMesh->mTangents[i].y;
					boneVertex.tangent.z = inputMesh->mTangents[i].z;
				}
				else
				{
				auto& vertex = vertices[i];
				vertex.tangent.x = inputMesh->mTangents[i].x;
				vertex.tangent.y = inputMesh->mTangents[i].y;
				vertex.tangent.z = inputMesh->mTangents[i].z;
				}
			}
			if (inputMesh->HasTextureCoords(0))
			{
				std::cout << "Reading Texture Coordinates...\n";
				for (uint32_t i = 0; i < inputMesh->mNumVertices; ++i)
				{
					if (hasBones)
					{
						auto& boneVertex = boneVertices[i];
						boneVertex.UV.x = inputMesh->mTextureCoords[0][i].x;
						boneVertex.UV.y = inputMesh->mTextureCoords[0][i].y;
					}
					else
					{
					auto& vertex = vertices[i];
					vertex.UV.x = inputMesh->mTextureCoords[0][i].x;
					vertex.UV.y = inputMesh->mTextureCoords[0][i].y;
					}
				}
			}

			std::cout << "Reading Indicies...\n";

			auto indices = std::make_unique<uint32_t[]>(inputMesh->mNumFaces * 3);

			for (uint32_t face = 0, index = 0; face < inputMesh->mNumFaces; ++face, index += 3)
			{
				indices[index] = inputMesh->mFaces[face].mIndices[0];
				indices[index + 1] = inputMesh->mFaces[face].mIndices[1];
				indices[index + 2] = inputMesh->mFaces[face].mIndices[2];
			}

			nsModel.mMaterialIndex[meshIndex] = inputMesh->mMaterialIndex;
			nsModel.mMesh[meshIndex].Allocate(inputMesh->mNumVertices, inputMesh->mNumFaces * 3);

			nsAnimModel.mMaterialIndex[meshIndex] = inputMesh->mMaterialIndex;
			nsAnimModel.mSkinMesh[meshIndex].Allocate(inputMesh->mNumVertices, inputMesh->mNumFaces * 3);
			// loop through nsModel.Mesh[meshIndex] 
			for (size_t i = 0; i < inputMesh->mNumVertices; i++)
			{
				if (hasBones)
				{
					nsAnimModel.mSkinMesh[meshIndex].GetVertex(i) = boneVertices[i];
				}
				else
				{
					nsModel.mMesh[meshIndex].GetVertex(i) = vertices[i];
				}
			}
			for (size_t i = 0; i < inputMesh->mNumFaces * 3; i++)
			{
				if (hasBones)
				{
					nsAnimModel.mSkinMesh[meshIndex].GetIndex(i) = indices[i];
				}
				else
				{
					nsModel.mMesh[meshIndex].GetIndex(i) = indices[i];
				}
			}

			//Bones
			if (inputMesh->HasBones())
			{
				std::cout << "Reading Bones...\n";
				for (uint32_t i = 0; i < inputMesh->mNumBones; i++)
				{
					aiBone* inputBone = inputMesh->mBones[i];
					uint32_t boneIndex = GetBoneIndex(inputBone, i);
					for (uint32_t j = 0; j < inputBone->mNumWeights; j++)
					{
						const aiVertexWeight& aiVertexWeight = inputBone->mWeights[j];
						nsAnimModel.mBoneWeights.push_back(aiVertexWeight.mWeight);
						nsAnimModel.mBoneVertexID.push_back(aiVertexWeight.mVertexId);
					}
				}
			}
		}
	}

	//Read Material data
	if (scene->HasMaterials())
	{
		std::cout << "Reading Materials...\n";

		nsModel.mMaterial.resize(scene->mNumMaterials); 
		nsAnimModel.mMaterial.resize(scene->mNumMaterials);
		for (uint32_t matIndex = 0; matIndex < scene->mNumMaterials; ++matIndex)
		{
			const aiMaterial* inputMaterial = scene->mMaterials[matIndex];
			aiString inputPath;

			aiColor3D ambient(0.0f, 0.0f, 0.0f);
			aiColor3D diffuse(0.0f, 0.0f, 0.0f);
			aiColor3D specular(0.0f, 0.0f, 0.0f);
			aiColor3D emissive(0.0f, 0.0f, 0.0f);
			float power = 0.0f;

			inputMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			inputMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			inputMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
			inputMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			inputMaterial->Get(AI_MATKEY_SHININESS, power);
			if (hasBones)
			{
				nsAnimModel.mMaterial[matIndex].ambient = { ambient.r, ambient.g, ambient.b, 1 };
				nsAnimModel.mMaterial[matIndex].diffuse = { diffuse.r, diffuse.g, diffuse.b, 1 };
				nsAnimModel.mMaterial[matIndex].emissive = { emissive.r , emissive.g, emissive.b, 1 };
				nsAnimModel.mMaterial[matIndex].specular = { specular.r , specular.g, specular.b, 1 };
				nsAnimModel.mMaterial[matIndex].power = { power };
			}
			else
			{
				nsModel.mMaterial[matIndex].ambient = { ambient.r, ambient.g, ambient.b, 1 };
				nsModel.mMaterial[matIndex].diffuse = { diffuse.r, diffuse.g, diffuse.b, 1 };
				nsModel.mMaterial[matIndex].emissive = { emissive.r , emissive.g, emissive.b, 1 };
				nsModel.mMaterial[matIndex].specular = { specular.r , specular.g, specular.b, 1 };
				nsModel.mMaterial[matIndex].power = { power };
			}
			
			const auto textureCount = inputMaterial->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
			if (textureCount > 0)
			{
				nsModel.mDiffuseTexture.resize(textureCount);
				nsAnimModel.mDiffuseTexture.resize(textureCount);
				for (uint32_t i = 0; i < textureCount; i++)
				{
					if (inputMaterial->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &inputPath) == AI_SUCCESS)
					{
						auto& path = nsModel.mDiffuseTexture[i];
						if (hasBones)
						{
							path = nsAnimModel.mDiffuseTexture[i];
						}
						else
						{
							path = nsModel.mDiffuseTexture[i];
						}
						

						//Check for Embeded Texture
						if (inputPath.C_Str()[0] == '*')
						{
							std::string fileName = params.inputFileName;
							fileName.erase(fileName.length() - 4);
							fileName += "_diffuse_";
							fileName += inputPath.C_Str()[1];

							ASSERT(scene->HasTextures(), "Error: No embedded texture found!");

							int textureIndex = atoi(inputPath.C_Str() + 1);
							ASSERT(textureIndex < (int)scene->mNumTextures, "Error: Invalid Texture Index!");

							const aiTexture* texture = scene->mTextures[i];
							ASSERT(texture->mHeight == 0, "Error: Uncompressed texture found!");

							if (texture->CheckFormat("jpg"))
							{
								fileName += ".jpg";
							}
							else if (texture->CheckFormat("png"))
							{
								fileName += ".png";
							}
							else
							{
								printf("Info: unrecognized texture format\n");
								continue;
							}
							printf("Info: Extracting embedded texture %s\n", fileName.c_str());

							FILE* file = nullptr;
							fopen_s(&file, fileName.c_str(), "wb");
							size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
							ASSERT(written == texture->mWidth, "Error: Failed to extract embedded texture!");
							fclose(file);
							path = fileName.c_str();
							auto loc = path.find_last_of("\\");
							if (loc != std::string::npos)
							{
								path = path.substr(loc + 1);
							}
						}
						else
						{
							//find the last position where '//' or '\' exists, and start one iteration after
							//(remove the directory section of the file)
							path = inputPath.C_Str();
							auto loc = path.find_last_of("\\");
							if (loc != std::string::npos)
							{
								path = path.substr(loc + 1);
							}
							loc = path.find(".tga");
							if (loc != std::string::npos)
							{
								path.replace(loc, 4, ".tif");
							}
						}
					}
				}
			}
		}
	}
	
	Bone* root = BuildSkeleton(*scene->mRootNode,nullptr);

	if (scene->HasAnimations())
	{
		//Resize container Here

		std::cout << "Reading Animations...\n";
		for (uint32_t animIndex = 0; animIndex < scene->mNumAnimations; animIndex++)
		{
			aiAnimation* inputAnimation = scene->mAnimations[animIndex];

			
		}
	}

}

int main(int argc, char* argv[])
{
	try
	{
		const Params params = ParseArg(argc, argv);
		ImportModel(params);
		if (hasBones)
		{
			nsAnimModel.SaveModel(/*params.outputFileName*/"B:/Visual_Studio_Projects/SWGE/Assets/Models/AnimationDemo/NorthernSoulSpin.swge");
		}
		else
		{
			nsModel.SaveModel(/*params.outputFileName*/"B:/Visual_Studio_Projects/SWGE/Assets/Models/AnimationDemo/NorthernSoulSpin.swge");
		}
	}
	catch (std::exception e)
	{
		printf("Exception: %s ", e.what());
	}
	nsModel.Destroy();
	nsAnimModel.Destroy();

#if _DEBUG
	Pause();
#endif

	return 0;
}