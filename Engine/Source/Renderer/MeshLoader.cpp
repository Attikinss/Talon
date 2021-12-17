#include "MeshLoader.h"
#include "Core/Logger.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Talon
{
    namespace Utilites
    {
        static std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene)
        {
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            for (uint32_t i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex newVert;
                newVert.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

                if (mesh->HasTextureCoords(0))
                    newVert.UV = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
                else
                    newVert.UV = { newVert.Position.x, newVert.Position.y };

                if (mesh->HasNormals())
                    newVert.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
                else
                    newVert.Normal = { 0.0f, 0.0f, 0.0f };

                if (mesh->HasTangentsAndBitangents())
                {
                    newVert.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                    newVert.BiTangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
                }
                else
                {
                    newVert.Tangent = { 0.0f, 0.0f, 0.0f };
                    newVert.BiTangent = { 0.0f, 0.0f, 0.0f };
                }

                vertices.emplace_back(newVert);
            }

            for (uint32_t i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                if (face.mNumIndices < 3)
                    continue;

                for (uint32_t j = 0; j < face.mNumIndices; j++)
                    indices.emplace_back(face.mIndices[j]);
            }

            return std::make_shared<Mesh>(vertices, indices);
        }

        static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& meshes)
        {
            for (uint32_t i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(ProcessMesh(mesh, scene));
            }

            for (uint32_t i = 0; i < node->mNumChildren; i++)
                ProcessNode(node->mChildren[i], scene, meshes);
        }
    }

    std::vector<std::shared_ptr<Mesh>> MeshLoader::Load(const std::string& filepath)
	{
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
        std::vector<std::shared_ptr<Mesh>> meshes;

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Logger::Error("Assimp could not process scene: {0}", importer.GetErrorString());
            return meshes;
        }

        // Recursively process scene from root node
        Utilites::ProcessNode(scene->mRootNode, scene, meshes);

        return meshes;
	}
}