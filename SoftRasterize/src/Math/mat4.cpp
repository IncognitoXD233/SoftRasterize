#include "../../include/Math/mat4.hpp"

// Methods
#pragma region Methods
Mat4::Mat4()
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            mat[row][col] = (row == col) ? 1.0f : 0.0f;
        }
    }
}

Mat4 Mat4::Identity()
{
    return Mat4();
}

Mat4 Mat4::Transpose() const
{
    Mat4 result;
    __m128 newRow0 = _mm_setr_ps(mat[0][0], mat[1][0], mat[2][0], mat[3][0]);
    __m128 newRow1 = _mm_setr_ps(mat[0][1], mat[1][1], mat[2][1], mat[3][1]);
    __m128 newRow2 = _mm_setr_ps(mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
    __m128 newRow3 = _mm_setr_ps(mat[0][3], mat[1][3], mat[2][3], mat[3][3]);

    _mm_store_ps(result.mat[0], newRow0);
    _mm_store_ps(result.mat[1], newRow1);
    _mm_store_ps(result.mat[2], newRow2);
    _mm_store_ps(result.mat[3], newRow3);
    return result;
}

Mat4 Mat4::Inverse() const
{
    float augmentedMat[4][8];
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            augmentedMat[row][col] = mat[row][col];
            augmentedMat[row][col + 4] = mat[row][col];
        }
    }

    for(int col = 0; col < 4; col++)
    {
        int pivotRow = col;
        float maxVal = std::fabs(augmentedMat[col][col]);
        for(int row = col + 1; row < 4; row++)
        {
            if(std::fabs(augmentedMat[row][col]) > maxVal)
            {
                maxVal = std::fabs(augmentedMat[row][col]);
                pivotRow = row;
            }
        }

        if(std::fabs(augmentedMat[pivotRow][col]) < 1e-8f)
        {
            throw std::runtime_error("Mat4::Inverse(): Matrix is singular.");
        }

        if(pivotRow != col)
        {
            for(int i = 0; i < 4; i++)
            {
                std::swap(augmentedMat[col][i], augmentedMat[pivotRow][i]);
            }
        }

        float pivotInv = 1.0f / augmentedMat[col][col];
        for(int i = 0; i < 8; i++)
        {
            augmentedMat[col][i] *= pivotInv;
        }

        for(int row = 0; row < 4; row++)
        {
            if(row == col) { continue; }

            float factor = augmentedMat[row][col];
            for(int i = 0; i < 8; i++)
            {
                augmentedMat[row][i] -= factor * augmentedMat[col][i];
            }
        }
    }

    Mat4 result;
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            result.mat[row][col] = augmentedMat[row][col + 4];
        }
    }
    return result;
}

Mat4 Mat4::FastInverse() const
{
    Mat4 result;

    __m128 row0 = _mm_load_ps(mat[0]);
    __m128 row1 = _mm_load_ps(mat[1]);
    __m128 row2 = _mm_load_ps(mat[2]);

    __m128 translation = _mm_setr_ps(mat[0][3], mat[1][3], mat[2][3], 0.0f);

    __m128 tmp0 = _mm_shuffle_ps(row0, row1, _MM_SHUFFLE(1, 0, 1, 0));
    __m128 tmp1 = _mm_shuffle_ps(row0, row1, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 tmp2 = _mm_shuffle_ps(row2, row2, _MM_SHUFFLE(0, 1, 0, 1));

    __m128 invRow0 = _mm_shuffle_ps(tmp0, row2, _MM_SHUFFLE(3, 0, 2, 0));
    __m128 invRow1 = _mm_shuffle_ps(tmp1, row2, _MM_SHUFFLE(3, 1, 3, 1));
    __m128 invRow2 = _mm_shuffle_ps(tmp2, row0, _MM_SHUFFLE(3, 2, 2, 0));

    __m128 invTransX = _mm_dp_ps(invRow0, translation, 0xF1);
    __m128 invTransY = _mm_dp_ps(invRow1, translation, 0xF2);
    __m128 invTransZ = _mm_dp_ps(invRow2, translation, 0xF4);

    __m128 invTranslation = _mm_sub_ps(_mm_setzero_ps(), _mm_add_ps(_mm_add_ps(invTransX, invTransY), invTransZ));

    _mm_store_ps(result.mat[0], _mm_blend_ps(invRow0, invTranslation, 0x8));
    _mm_store_ps(result.mat[1], _mm_blend_ps(invRow1, invTranslation, 0x8));
    _mm_store_ps(result.mat[2], _mm_blend_ps(invRow2, invTranslation, 0x8));
    _mm_store_ps(result.mat[3], _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f));

    return result;
}

float Mat4::Determinant() const
{
    auto determinant3x3 = [=](float a, float b, float c,
                              float d, float e, float f, 
                              float g, float h, float i)
    {
        return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    };

    return mat[0][0] * determinant3x3(mat[1][1], mat[1][2], mat[1][3],
                                      mat[2][1], mat[2][2], mat[2][3],
                                      mat[3][1], mat[3][2], mat[3][3])
                                      
         - mat[0][1] * determinant3x3(mat[1][0], mat[1][2], mat[1][3],
                                      mat[2][0], mat[2][2], mat[2][3],
                                      mat[3][0], mat[3][2], mat[3][3])
                                      
         + mat[0][2] * determinant3x3(mat[1][0], mat[1][1], mat[1][3],
                                      mat[2][0], mat[2][1], mat[2][3],
                                      mat[3][0], mat[3][1], mat[3][3])

         - mat[0][3] * determinant3x3(mat[1][0], mat[1][1], mat[1][2],
                                      mat[2][0], mat[2][1], mat[2][2],
                                      mat[3][0], mat[3][1], mat[3][2]);
}

Mat4 Mat4::LookAt(const Vec3& _eye, 
                  const Vec3& _target, 
                  const Vec3& _up)
{
    
}

Mat4 Mat4::Translate(float _translateX, float _translateY, float _translateZ)
{
    Mat4 result = Identity();
    __m128 translateVec = _mm_setr_ps(_translateX, _translateY, _translateZ, 1.0f);
    _mm_store_ps(&result.mat[0][3], translateVec);
    return result;
}

Mat4 Mat4::Translate(const Vec3& _translateVec)
{ 
    return Translate(_translateVec.x, _translateVec.y, _translateVec.z);
}

Mat4 Mat4::Scale(float _scaleX, float _scaleY, float _scaleZ)
{
    Mat4 result = Identity();
    __m128 scaleVec0 = _mm_setr_ps(_scaleX, 0.0f, 0.0f, 0.0f);
    __m128 scaleVec1 = _mm_setr_ps(0.0f, _scaleY, 0.0f, 0.0f);
    __m128 scaleVec2 = _mm_setr_ps(0.0f, 0.0f, _scaleZ, 0.0f);

    _mm_store_ps(result.mat[0], scaleVec0);
    _mm_store_ps(result.mat[1], scaleVec1);
    _mm_store_ps(result.mat[2], scaleVec2);
    return result;
}

Mat4 Mat4::Scale(const Vec3& _scaleVec)
{ 
    return Scale(_scaleVec.x, _scaleVec.y, _scaleVec.z);
}

Mat4 Mat4::RotateX(float _rotateX)
{ 
    float radX = _rotateX * (M_PI / 180.0f);
    Mat4 rotX = Identity();
    __m128 rotXVec1 = _mm_setr_ps(0.0f, cosf(radX), -sinf(radX), 0.0f);
    __m128 rotXVec2 = _mm_setr_ps(0.0f, sinf(radX), cosf(radX), 0.0f);
    _mm_store_ps(rotX.mat[1], rotXVec1);
    _mm_store_ps(rotX.mat[2], rotXVec2);
    return rotX;
}

Mat4 Mat4::RotateY(float _rotateY)
{ 
    float radY = _rotateY * (M_PI / 180.0f);
    Mat4 rotY = Identity();
    __m128 rotYVec0 = _mm_setr_ps(cosf(radY), 0.0f, sinf(radY), 0.0f);
    __m128 rotYVec2 = _mm_setr_ps(-sinf(radY), 0.0f, cosf(radY), 0.0f);
    _mm_store_ps(rotY.mat[0], rotYVec0);
    _mm_store_ps(rotY.mat[2], rotYVec2);
    return rotY;
}

Mat4 Mat4::RotateZ(float _rotateZ)
{ 
    float radZ = _rotateZ * (M_PI / 180.0f);
    Mat4 rotZ = Identity();
    __m128 rotZVec0 = _mm_setr_ps(cosf(radZ), -sinf(radZ), 0.0f, 0.0f);
    __m128 rotZVec1 = _mm_setr_ps(sinf(radZ), cosf(radZ), 0.0f, 0.0f);
    _mm_store_ps(rotZ.mat[0], rotZVec0);
    _mm_store_ps(rotZ.mat[1], rotZVec1);
    return rotZ;
}

Mat4 Mat4::Rotate(float _rotateX, float _rotateY, float _rotateZ)
{
    Mat4 rotX = RotateX(_rotateX);
    Mat4 rotY = RotateY(_rotateY);
    Mat4 rotZ = RotateZ(_rotateZ);
    return rotZ * rotY * rotX;/*Rotate Z -> Y -> X*/
}

Mat4 Mat4::Rotate(const Vec3& _rotateVec)
{ 
    return Rotate(_rotateVec.x, _rotateVec.y, _rotateVec.z);
}

#pragma endregion

// Operators
#pragma region Operators

Mat4 Mat4::operator*(const Mat4& _other) const
{ 
    Mat4 result;
    Mat4 transposeMat = (*this).Transpose();

    __m128 newRow0 = _mm_load_ps(_other.mat[0]);
    __m128 newRow1 = _mm_load_ps(_other.mat[1]);
    __m128 newRow2 = _mm_load_ps(_other.mat[2]);
    __m128 newRow3 = _mm_load_ps(_other.mat[3]);

    for(int row = 0; row < 4; row++)
    {
        __m128 newMul0 = _mm_mul_ps(newRow0, transposeMat.row[row]);
        __m128 newMul1 = _mm_mul_ps(newRow1, transposeMat.row[row]);
        __m128 newMul2 = _mm_mul_ps(newRow2, transposeMat.row[row]);
        __m128 newMul3 = _mm_mul_ps(newRow3, transposeMat.row[row]);
        result.row[row] = _mm_add_ps(_mm_add_ps(newMul0, newMul1), _mm_add_ps(newMul2, newMul3));
    }
    return result;
}

Vec4 Mat4::operator*(const Vec4& _vec) const
{
    __m128 newVecX = _mm_set1_ps(_vec.x);
    __m128 newVecY = _mm_set1_ps(_vec.y);
    __m128 newVecZ = _mm_set1_ps(_vec.z);
    __m128 newVecW = _mm_set1_ps(_vec.w);

    __m128 result = _mm_mul_ps(row[0], newVecX);
    result = _mm_add_ps(result, _mm_mul_ps(row[1], newVecY));
    result = _mm_add_ps(result, _mm_mul_ps(row[2], newVecZ));
    result = _mm_add_ps(result, _mm_mul_ps(row[3], newVecW));

    alignas(16) float data[4];
    _mm_store_ps(data, result);
    return Vec4(data[0], data[1], data[2], data[3]);
}

Vec3 Mat4::operator*(const Vec3& _vec3) const
{
    Vec4 result = (*this) * Vec4(_vec3, 1.0f);
    return result.ToVec3();
}

bool Mat4::operator==(const Mat4& _other) const
{
    const __m128 epsilon = _mm_set1_ps(1e-8f);
    for(int row = 0; row < 4; row++)
    {
        __m128 thisRow = _mm_load_ps(mat[row]);
        __m128 otherRow = _mm_load_ps(_other.mat[row]);

        __m128 diff = _mm_sub_ps(thisRow, otherRow);
        __m128 absDiff = _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), diff), diff);

        __m128 cmp = _mm_cmpgt_ps(absDiff, epsilon);
        if(_mm_movemask_ps(cmp) != 0)
        {
            return false;
        }
    }
    return true;
}

bool Mat4::operator!=(const Mat4& _other) const
{
    return !(*this == _other);
}

#pragma endregion