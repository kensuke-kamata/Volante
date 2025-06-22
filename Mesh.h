#pragma once

#include "Volante.h"
#include <glad/glad.h>
#include <vector>

namespace Volante {

struct Vertex {
    Vec3 position;
    Vec3 normal;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {
        setupMesh();
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    // 立方体メッシュを生成
    static Mesh* createCube(float size = 1.0f) {
        float half = size * 0.5f;

        const std::vector<Vertex> vertices = {
            // 前面
            {{-half, -half,  half}, {  0.0f,  0.0f,  1.0f}},
            {{ half, -half,  half}, {  0.0f,  0.0f,  1.0f}},
            {{ half,  half,  half}, {  0.0f,  0.0f,  1.0f}},
            {{-half,  half,  half}, {  0.0f,  0.0f,  1.0f}},
            // 背面
            {{-half, -half, -half}, {  0.0f,  0.0f, -1.0f}},
            {{-half,  half, -half}, {  0.0f,  0.0f, -1.0f}},
            {{ half,  half, -half}, {  0.0f,  0.0f, -1.0f}},
            {{ half, -half, -half}, {  0.0f,  0.0f, -1.0f}},
            // 上面
            {{-half,  half, -half}, {  0.0f,  1.0f,  0.0f}},
            {{-half,  half,  half}, {  0.0f,  1.0f,  0.0f}},
            {{ half,  half,  half}, {  0.0f,  1.0f,  0.0f}},
            {{ half,  half, -half}, {  0.0f,  1.0f,  0.0f}},
            // 下面
            {{-half, -half, -half}, {  0.0f, -1.0f,  0.0f}},
            {{ half, -half, -half}, {  0.0f, -1.0f,  0.0f}},
            {{ half, -half,  half}, {  0.0f, -1.0f,  0.0f}},
            {{-half, -half,  half}, {  0.0f, -1.0f,  0.0f}},
            // 右面
            {{ half, -half, -half}, {  1.0f,  0.0f,  0.0f}},
            {{ half,  half, -half}, {  1.0f,  0.0f,  0.0f}},
            {{ half,  half,  half}, {  1.0f,  0.0f,  0.0f}},
            {{ half, -half,  half}, {  1.0f,  0.0f,  0.0f}},
            // 左面
            {{-half, -half, -half}, { -1.0f,  0.0f,  0.0f}},
            {{-half, -half,  half}, { -1.0f,  0.0f,  0.0f}},
            {{-half,  half,  half}, { -1.0f,  0.0f,  0.0f}},
            {{-half,  half, -half}, { -1.0f,  0.0f,  0.0f}}
        };

        std::vector<unsigned int> indices = {
             0,  1,  2,  2,  3,  0,  // 前面
             4,  5,  6,  6,  7,  4,  // 背面
             8,  9, 10, 10, 11,  8,  // 上面
            12, 13, 14, 14, 15, 12,  // 下面
            16, 17, 18, 18, 19, 16,  // 右面
            20, 21, 22, 22, 23, 20   // 左面
        };

        return new Mesh(vertices, indices);
    }

    // 球メッシュを生成（UV球）
    static Mesh* createSphere(float radius = 1.0f, unsigned int sectorCount = 36, unsigned int stackCount = 18) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        const float sectorStep = 2 * PI / sectorCount;
        const float stackStep = PI / stackCount;

        // 頂点を生成
        for (unsigned int i = 0; i <= stackCount; ++i) {
            const float stackAngle = HALF_PI - i * stackStep;
            const float xy = radius * cosf(stackAngle);
            const float z  = radius * sinf(stackAngle);

            for (unsigned int j = 0; j <= sectorCount; ++j) {
                const float sectorAngle = j * sectorStep;

                Vertex vertex;
                vertex.position.x = xy * cosf(sectorAngle);
                vertex.position.y = xy * sinf(sectorAngle);
                vertex.position.z = z;

                // 正規化された位置が法線ベクトル
                vertex.normal = normalize(vertex.position);

                vertices.push_back(vertex);
            }
        }

        // インデックスを生成
        for (unsigned int i = 0; i < stackCount; ++i) {
            unsigned int k1 = i * (sectorCount + 1);
            unsigned int k2 = k1 + sectorCount + 1;

            for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (stackCount - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        return new Mesh(vertices, indices);
    }

private:
    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

        glBindVertexArray(0);
    }
};

}
