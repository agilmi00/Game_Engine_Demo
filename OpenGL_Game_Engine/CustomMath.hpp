//
//  CustomMath.hpp
//  OpenGL_Game_Engine
//
//  Created by Adrián Gil Miranda.
//

#ifndef CustomMath_hpp
#define CustomMath_hpp

#include <stdio.h>
#include <iostream>
#include "glm/glm.hpp"



namespace  mth {
    
struct Vector3
{
    float x,y,z;
    
    Vector3() = default;
    
    Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    //Temporary
    Vector3(glm::vec3 vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    
    float& operator [] (int i)
    {
        return ((&x)[i]);
    }
    
    const float& operator [] (int i) const
    {
        return ((&x)[i]);
    }
};

inline Vector3 operator + (const Vector3& v1, const Vector3& v2)
{
    return (Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

inline Vector3 operator - (const Vector3& v1, const Vector3& v2)
{
    return (Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

inline Vector3 operator * (const Vector3& v, float s)
{
    return (Vector3(v.x * s, v.y * s, v.z * s));
}

inline Vector3 operator / (const Vector3& v, float s)
{
    return (Vector3(v.x / s, v.y / s, v.z / s));
}

inline float Distance(const Vector3& v1, const Vector3& v2)
{
    return (sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z)));
}

inline float Magnitude(const Vector3& v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline Vector3 Normalize(const Vector3& v)
{
    return (v / Magnitude(v));
}
inline Vector3 toRadians(const Vector3& v)
{
    return (Vector3(v.x * (M_PI / 180), (v.y * M_PI) / 180, (v.z * M_PI) / 180));
}

inline float Dot(const Vector3& v1,  const Vector3& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
    return(Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
}

inline Vector3 Project(const Vector3& v1, const Vector3& v2)
{
    return (v2 * Dot(v1, v2) / Dot(v2, v2));
}

inline Vector3 Reject(const Vector3& v1, const Vector3& v2)
{
    return (v1 - v2 * Dot(v1, v2) / Dot(v2, v2));
}

struct Matrix3
{
    float p[3][3];
    
    Matrix3() = default;
    
    Matrix3(float p00, float p01, float p02,
            float p10, float p11, float p12,
            float p20, float p21, float p22)
    {
        p[0][0] = p00; p[0][1] = p01; p[0][2] = p02;
        p[1][0] = p10; p[1][1] = p11; p[1][2] = p12;
        p[2][0] = p20; p[2][1] = p21; p[2][2] = p22;
    }
    
    float& operator ()(int n, int m)
    {
        return (p[n][m]);
    }
    
    const float& operator ()(int n, int m) const
    {
        return (p[n][m]);
    }
    
    inline Vector3& operator [](int n)
    {
        return (*reinterpret_cast<Vector3 *>(p[n]));
    }
};

inline Vector3 operator *(const Matrix3& M1, const Vector3& V1)
{
    return (Vector3(M1(0,0) * V1.x + M1(0,1) * V1.y + M1(0,2) * V1.z,
                    M1(1,0) * V1.x + M1(1,1) * V1.y + M1(1,2) * V1.z,
                    M1(2,0) * V1.x + M1(2,1) * V1.y + M1(2,2) * V1.z));
}

inline Matrix3 operator *(const Matrix3& M1, const Matrix3& M2)
{
    return (Matrix3(M1(0,0) * M2(0,0) + M1(0,1) * M2(1,0) + M1(0,2) * M2(2,0),
                    M1(0,0) * M2(0,1) + M1(0,1) * M2(1,1) + M1(0,2) * M2(2,1),
                    M1(0,0) * M2(0,2) + M1(0,1) * M2(1,2) + M1(0,2) * M2(2,2),
                    M1(1,0) * M2(0,0) + M1(1,1) * M2(1,0) + M1(1,2) * M2(2,0),
                    M1(1,0) * M2(0,1) + M1(1,1) * M2(1,1) + M1(1,2) * M2(2,1),
                    M1(1,0) * M2(0,2) + M1(1,1) * M2(1,2) + M1(1,2) * M2(2,2),
                    M1(2,0) * M2(0,0) + M1(2,1) * M2(1,0) + M1(2,2) * M2(2,0),
                    M1(2,0) * M2(0,1) + M1(2,1) * M2(1,1) + M1(2,2) * M2(2,1),
                    M1(2,0) * M2(0,2) + M1(2,1) * M2(1,2) + M1(2,2) * M2(2,2)));
}

struct Matrix4
{
    float p[4][4];
    
    Matrix4() = default;
    
    Matrix4(float p00, float p01, float p02, float p03,
            float p10, float p11, float p12, float p13,
            float p20, float p21, float p22, float p23,
            float p30, float p31, float p32, float p33)
    {
//        p[0][0] = p00; p[0][1] = p01; p[0][2] = p02; p[0][3] = p03;
//        p[1][0] = p10; p[1][1] = p11; p[1][2] = p12; p[1][3] = p13;
//        p[2][0] = p20; p[2][1] = p21; p[2][2] = p22; p[2][3] = p23;
//        p[3][0] = p30; p[3][1] = p31; p[3][2] = p32; p[3][3] = p33;
        
        // Column major
        p[0][0] = p00; p[0][1] = p10; p[0][2] = p20; p[0][3] = p30;
        p[1][0] = p01; p[1][1] = p11; p[1][2] = p21; p[1][3] = p31;
        p[2][0] = p02; p[2][1] = p12; p[2][2] = p22; p[2][3] = p32;
        p[3][0] = p03; p[3][1] = p13; p[3][2] = p23; p[3][3] = p33;
    }
    
    // Identity Matrix constructor
    Matrix4(float n)
    {
        p[0][0] = n; p[0][1] = 0; p[0][2] = 0; p[0][3] = 0;
        p[1][0] = 0; p[1][1] = n; p[1][2] = 0; p[1][3] = 0;
        p[2][0] = 0; p[2][1] = 0; p[2][2] = n; p[2][3] = 0;
        p[3][0] = 0; p[3][1] = 0; p[3][2] = 0; p[3][3] = n;
    }
    
    float& operator ()(int n, int m)
    {
        return (p[m][n]);
    }
    
    const float& operator ()(int n, int m) const
    {
        return (p[m][n]);
    }
    
    inline Vector3& operator [](int n)
    {
        return (*reinterpret_cast<Vector3 *>(p[n]));
    }
    
    
    
};
inline Matrix4 translate(const Matrix4& M1, const Vector3& V1)
{

    // Column major
        return (Matrix4(M1(0,0), M1(1,0), M1(2,0), V1.x,
                        M1(0,1), M1(1,1), M1(2,1), V1.y,
                        M1(0,2), M1(1,2), M1(2,2), V1.z,
                        M1(0,3), M1(1,3), M1(2,3), M1(3,3)));
}
inline Matrix4 scale(const Matrix4& M1, const Vector3& V1)
{

    // Column major
        return (Matrix4(M1(0,0)*V1.x, M1(1,0), M1(2,0), M1(3,0),
                        M1(0,1), M1(1,1)*V1.y, M1(2,1), M1(3,1),
                        M1(0,2), M1(1,2), M1(2,2)*V1.z, M1(3,2),
                        M1(0,3), M1(1,3), M1(2,3), M1(3,3)));
}
inline Matrix4 operator *(const Matrix4& M1, const Matrix4& M2)
{
    return (Matrix4(M1(0,0) * M2(0,0) + M1(0,1) * M2(1,0) + M1(0,2) * M2(2,0) + M1(0,3) * M2(3,0),
                    M1(0,0) * M2(0,1) + M1(0,1) * M2(1,1) + M1(0,2) * M2(2,1) + M1(0,3) * M2(3,1),
                    M1(0,0) * M2(0,2) + M1(0,1) * M2(1,2) + M1(0,2) * M2(2,2) + M1(0,3) * M2(3,2),
                    M1(0,0) * M2(0,3) + M1(0,1) * M2(1,3) + M1(0,2) * M2(2,3) + M1(0,3) * M2(3,3),
                    M1(1,0) * M2(0,0) + M1(1,1) * M2(1,0) + M1(1,2) * M2(2,0) + M1(1,3) * M2(3,0),
                    M1(1,0) * M2(0,1) + M1(1,1) * M2(1,1) + M1(1,2) * M2(2,1) + M1(1,3) * M2(3,1),
                    M1(1,0) * M2(0,2) + M1(1,1) * M2(1,2) + M1(1,2) * M2(2,2) + M1(1,3) * M2(3,2),
                    M1(1,0) * M2(0,3) + M1(1,1) * M2(1,3) + M1(1,2) * M2(2,3) + M1(1,3) * M2(3,3),
                    M1(2,0) * M2(0,0) + M1(2,1) * M2(1,0) + M1(2,2) * M2(2,0) + M1(2,3) * M2(3,0),
                    M1(2,0) * M2(0,1) + M1(2,1) * M2(1,1) + M1(2,2) * M2(2,1) + M1(2,3) * M2(3,1),
                    M1(2,0) * M2(0,2) + M1(2,1) * M2(1,2) + M1(2,2) * M2(2,2) + M1(2,3) * M2(3,2),
                    M1(2,0) * M2(0,3) + M1(2,1) * M2(1,3) + M1(2,2) * M2(2,3) + M1(2,3) * M2(3,3),
                    M1(3,0) * M2(0,0) + M1(3,1) * M2(1,0) + M1(3,2) * M2(2,0) + M1(3,3) * M2(3,0),
                    M1(3,0) * M2(0,1) + M1(3,1) * M2(1,1) + M1(3,2) * M2(2,1) + M1(3,3) * M2(3,1),
                    M1(3,0) * M2(0,2) + M1(3,1) * M2(1,2) + M1(3,2) * M2(2,2) + M1(3,3) * M2(3,2),
                    M1(3,0) * M2(0,3) + M1(3,1) * M2(1,3) + M1(3,2) * M2(2,3) + M1(3,3) * M2(3,3)));
}


inline const float *Mat4Point(const Matrix4& M1)
{
    return (const_cast<float *>(reinterpret_cast<const float *>(&M1)));
    
}
inline float *Mat4Point(Matrix4& M1)
{
    return (reinterpret_cast<float *>(&M1));
    
}

struct Quatern
{
    float w, x, y, z;
    
    Quatern(const Vector3& v, float s)
    {
        w = s;
        x = v.x;
        y = v.y;
        z = v.z;
    }
    
    
};

inline Quatern operator *(const Quatern& Q1, const Quatern& Q2)
{
    return (Quatern(Vector3(Q1.x * Q2.w + Q1.y * Q2.z - Q1.z * Q2.y + Q1.w * Q2.x,
                            Q1.y * Q2.w + Q1.z * Q2.x + Q1.w * Q2.y - Q1.x * Q2.z,
                            Q1.z * Q2.w + Q1.w * Q2.z + Q1.x * Q2.y - Q1.y * Q2.x),
                            Q1.w * Q2.w - Q1.x * Q2.x - Q1.y * Q2.y - Q1.z * Q2.z));
}
inline Quatern operator +(const Quatern& Q1, const Quatern& Q2)
{
    return (Quatern(Vector3(Q2.x + Q1.x,
                            Q2.y + Q1.y,
                            Q2.z + Q1.z),
                            Q2.w + Q1.w));
}
inline Quatern operator -(const Quatern& Q1, const Quatern& Q2)
{
    return (Quatern(Vector3(Q1.x - Q2.x,
                            Q1.y - Q2.y,
                            Q1.z - Q2.z),
                            Q1.w - Q2.w));
}
inline Quatern operator *(const Matrix4& M1, const Quatern& Q1)
{
    return (Quatern(Vector3(M1(0,0) * Q1.x + M1(0,1) * Q1.y + M1(0,2) * Q1.z + M1(0,3) * Q1.w,
                            M1(1,0) * Q1.x + M1(1,1) * Q1.y + M1(1,2) * Q1.z + M1(1,3) * Q1.w,
                            M1(2,0) * Q1.x + M1(2,1) * Q1.y + M1(2,2) * Q1.z + M1(2,3) * Q1.w),
                            M1(3,0) * Q1.x + M1(3,1) * Q1.y + M1(3,2) * Q1.z + M1(3,3) * Q1.w));
}

inline Quatern EulerToQuat(double x, double y, double z) // (yaw), (pitch), (roll)
{

    double CosX = cos(x * 0.5);
    double SinX = sin(x * 0.5);
    double CosY = cos(y * 0.5);
    double SinY = sin(y * 0.5);
    double CosZ = cos(z * 0.5);
    double SinZ = sin(z * 0.5);

    return (Quatern(Vector3(CosZ * CosY * SinX - SinZ * SinY * CosX,
                            CosZ * SinY * CosX + SinZ * CosY * SinX,
                            SinZ * CosY * CosX - CosZ * SinY * SinX),
                            CosZ * CosY * CosX + SinZ * SinY * SinX));
}

inline Vector3 RotationV3(const Quatern& q1, const Vector3& v1)
{
    Vector3 vecPart = Vector3(q1.x, q1.y, q1.z);
    float vecPart2 = q1.x * q1.x + q1.y * q1.y + q1.z * q1.z;
    return (v1 * (q1.w * q1.w - vecPart2) + vecPart * (Dot(v1, vecPart)) * 2.0f) + Cross(vecPart, v1) * (q1.w * 2.0f);
}

inline double Magnitud(const Quatern& q1)
{
    return sqrt(q1.x * q1.x + q1.y * q1.y + q1.z * q1.z + q1.w * q1.w);
}

inline Quatern Normalize(const Quatern& q1)
{
    double mag = sqrt(q1.x * q1.x + q1.y * q1.y + q1.z * q1.z + q1.w * q1.w);
    return Quatern(Vector3(q1.x/mag, q1.y/mag, q1.z/mag), q1.w/mag);
}

inline glm::vec3 QuatToEuler(const Quatern& q)
{
    glm::vec3 eulerAngles;

    // yaw (X)
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    eulerAngles.x = std::atan2(siny_cosp, cosy_cosp);
    
    // pitch (Y)
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (std::abs(sinp) >= 1)
        eulerAngles.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        eulerAngles.y = std::asin(sinp);

    // roll (Z)
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    eulerAngles.z = std::atan2(sinr_cosp, cosr_cosp);
    

    return (eulerAngles);
}

inline Matrix4 RotationM4(const Quatern& q1)
{
    float x2 = q1.x * q1.x;
    float y2 = q1.y * q1.y;
    float z2 = q1.z * q1.z;
    float xy = q1.x * q1.y;
    float xz = q1.x * q1.z;
    float yz = q1.y * q1.z;
    float wx = q1.w * q1.x;
    float wy = q1.w * q1.y;
    float wz = q1.w * q1.z;
    
   
    return(Matrix4(1.0 - 2.0 * (y2 + z2), 2.0 * (xy - wz), 2.0 * (xz + wy), 0,
                   2.0 * (xy + wz), 1.0 - 2.0 * (x2 + z2), 2.0 * (yz - wx), 0,
                   2.0 * (xz - wy), 2.0 * (yz + wx), 1.0 - 2.0 * (x2 + y2), 0,
                   0, 0, 0, 1));
}

};



#endif /* CustomMath_hpp */
