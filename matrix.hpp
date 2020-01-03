
#ifndef _MATRIX_HEAD_ 
#define _MATRIX_HEAD_ 

#include "global.hpp"
#include "vector.hpp" 

#include <iostream> 
#include <cmath> 

template <typename T>
class Matrix
{
public:
    explicit Matrix() {
        set_zero(); 
    }
    explicit Matrix(const int v00, const int v01, const int v02, const int v03, \
                    const int v10, const int v11, const int v12, const int v13, \
                    const int v20, const int v21, const int v22, const int v23, \
                    const int v30, const int v31, const int v32, const int v33 )
    {
        m[0][0] = v00; m[0][1] = v01; m[0][2] = v02; m[0][3] = v03;
        m[1][0] = v10; m[1][1] = v11; m[1][2] = v12; m[1][3] = v13;
        m[2][0] = v20; m[2][1] = v21; m[2][2] = v22; m[2][3] = v23;
        m[3][0] = v30; m[3][1] = v31; m[3][2] = v32; m[3][3] = v33;   
    }

    bool operator==(const Matrix<T>& t) const 
    {
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                if(fabs(m[i][j] - t.m[i][j]) > POSITIVE_FLOAT_ZERO )
                {
                    return false; 
                }
            }
        }
        return true; 
    }

    bool operator!=(const Matrix<T>& t) const 
    {
        return !(operator==(t)); 
    }

    void set_zero()
    {
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                m[i][j] = 0; 
            }
        }
    }

    void set_indentity()
    {
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                m[i][j] = (i==j)?1:0; 
            }
        }
    }

    void scale(const T& x, const T& y, const T& z)
    {
        set_indentity(); 
        m[0][0] = x; m[1][1] = y; m[2][2] = z; 
    } 

    void translate(const T& x, const T& y, const T& z)
    {
        set_indentity(); 
        m[0][3] = x; m[1][3] = y; m[2][3] = z; 
    }

    void rotate(const T& x, const T& y, const T& z, const T& angle)
    {
        // T qsin = static_cast<T>(sin(angle)); 
        // T qcos = static_cast<T>(cos(angle)); 

        T qsin = static_cast<T>(sin(angle * 0.5f)); 
        T qcos = static_cast<T>(cos(angle * 0.5f)); 
        // Vector3<T> n = Vector3<T>(x, y, z); 
        // n = normal(n); 
        // set_indentity();
        // m[0][0] = n.x * n.x * (1 - c) + c;  

        T sq = static_cast<T>(std::sqrt(x*x + y*y + z*z)); 
        T vx = x / sq * qsin; 
        T vy = y / sq * qsin;
        T vz = z / sq * qsin; 
        m[0][0] = 1 - 2*vy*vy - 2 *z *z; 
        m[1][0] = 2 * vx * vy - 2* qcos *vz; 
        m[2][0] = 2 * vx * vz + 2 * qcos * vy; 
        m[0][1] = 2 * vx * vy + 2 * qcos * vz; 
        m[1][1] = 1 - 2 * vx * vx - 2 *vz * vz; 
        m[2][1] = 2 * vy * vz - 2 * qcos * vx; 
        m[0][2] = 2 * vx * vz - 2 * qcos * vy; 
        m[1][2] = 2 * vy * vz + 2 * qcos * vx; 
        m[2][2] = 1 - 2 * vx * vx - 2 * vy * vy; 
        m[0][3] = m[1][3] = m[2][3] = 0; 
        m[3][0] = m[3][1] = m[3][2] = 0; 
        m[3][3] = 1; 
    }

    Matrix<T> operator*(const Matrix<T>& t) const 
    {
        Matrix<T> r; 
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                r.m[i][j] = 0; 
                for(size_t k=0; k<4; ++k)
                {
                    r.m[i][j] += m[i][k] * t.m[k][j]; 
                }
            }
        }
        return r; 
    }

    Matrix<T> operator+(const Matrix<T>& t) const 
    {
        Matrix<T> r; 
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                r.m[i][j] = m[i][j] + t.m[i][j]; 
            }
        }
        return r; 
    }

    Matrix<T> operator-(const Matrix<T>& t) const 
    {
        Matrix<T> r; 
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                r.m[i][j] = m[i][j] - t.m[i][j]; 
            }
        }
        return r; 
    }

    Matrix<T> inverse() const 
    {
        T inv[16]; 
        
        inv[0] = 	m[1][1] * m[2][2] * m[3][3] -
                    m[1][1] * m[2][3] * m[3][2] -
                    m[2][1] * m[1][2]  * m[3][3] +
                    m[2][1] * m[1][3]  * m[3][2] +
                    m[3][1] * m[1][2]  * m[2][3] -
                    m[3][1] * m[1][3]  * m[2][2];

        inv[4] = -m[1][0]  * m[2][2] * m[3][3] +
                            m[1][0]  * m[2][3] * m[3][2] +
                            m[2][0]  * m[1][2]  * m[3][3] -
                            m[2][0]  * m[1][3]  * m[3][2] -
                            m[3][0] * m[1][2]  * m[2][3] +
                            m[3][0] * m[1][3]  * m[2][2];

        inv[8] = 	m[1][0]  * m[2][1]  * m[3][3] -
                            m[1][0]  * m[2][3] * m[3][1] -
                            m[2][0]  * m[1][1]  * m[3][3] +
                            m[2][0]  * m[1][3]  * m[3][1] +
                            m[3][0] * m[1][1]  * m[2][3] -
                            m[3][0] * m[1][3]  * m[2][1];

        inv[12] = -m[1][0]  * m[2][1]  * m[3][2] +
                            m[1][0]  * m[2][2] * m[3][1] +
                            m[2][0]  * m[1][1]  * m[3][2] -
                            m[2][0]  * m[1][2]  * m[3][1] -
                            m[3][0] * m[1][1]  * m[2][2] +
                            m[3][0] * m[1][2]  * m[2][1];

        inv[1] = -m[0][1]  * m[2][2] * m[3][3] +
                            m[0][1]  * m[2][3] * m[3][2] +
                            m[2][1]  * m[0][2] *  m[3][3] -
                            m[2][1]  * m[0][3] *  m[3][2] -
                            m[3][1] * m[0][2] *  m[2][3] +
                            m[3][1] * m[0][3] *  m[2][2];

        inv[5] =  m[0][0]  * m[2][2] * m[3][3] -
                            m[0][0]  * m[2][1] * m[3][2] -
                            m[2][0]  * m[0][2]  * m[3][3] +
                            m[2][0]  * m[0][3]  * m[3][2] +
                            m[3][0] * m[0][2]  * m[2][3] -
                            m[3][0] * m[0][3]  * m[2][2];

        inv[9] = -m[0][0]  * m[2][1]  * m[3][3] +
                            m[0][0]  * m[2][3] * m[3][1] +
                            m[2][0]  * m[0][1]  * m[3][3] -
                            m[2][0]  * m[0][3]  * m[3][1] -
                            m[3][0] * m[0][1]  * m[2][3] +
                            m[3][0] * m[0][3]  * m[2][1];

        inv[13] = m[0][0]  * m[2][1]  * m[3][2] -
                            m[0][0]  * m[2][2] * m[3][1] -
                            m[2][0]  * m[0][1]  * m[3][2] +
                            m[2][0]  * m[0][2]  * m[3][1] +
                            m[3][0] * m[0][1]  * m[2][2] -
                            m[3][0] * m[0][2]  * m[2][1];

        inv[2] = m[0][1]  * m[1][2] * m[3][3] -
                        m[0][1]  * m[1][3] * m[3][2] -
                        m[1][1]  * m[0][2] * m[3][3] +
                        m[1][1]  * m[0][3] * m[3][2] +
                        m[3][1] * m[0][2] * m[1][3] -
                        m[3][1] * m[0][3] * m[1][2];

        inv[6] = -m[0][0]  * m[1][2] * m[3][3] +
                            m[0][0]  * m[1][3] * m[3][2] +
                            m[1][1]  * m[0][2] * m[3][3] -
                            m[1][1]  * m[0][3] * m[3][2] -
                            m[3][0] * m[0][2] * m[1][3] +
                            m[3][0] * m[0][3] * m[1][2];

        inv[10] = m[0][0]  * m[1][1] * m[3][3] -
                            m[0][0]  * m[1][3] * m[3][1] -
                            m[1][0]  * m[0][1] * m[3][3] +
                            m[1][0]  * m[0][3] * m[3][1] +
                            m[3][0] * m[0][1] * m[1][3] -
                            m[3][0] * m[0][3] * m[1][1];

        inv[14] = -m[0][0]  * m[1][1] * m[3][2] +
                            m[0][0]  * m[1][2] * m[3][1] +
                            m[1][0]  * m[0][1] * m[3][2] -
                            m[1][0]  * m[0][2] * m[3][1] -
                            m[3][0] * m[0][1] * m[1][2] +
                            m[3][0] * m[0][2] * m[1][1];

        inv[3] = -m[0][1] * m[1][2] * m[2][3] +
                            m[0][1] * m[1][3] * m[2][2] +
                            m[1][1] * m[0][2] * m[2][3] -
                            m[1][1] * m[0][3] * m[2][2] -
                            m[2][1] * m[0][2] * m[1][3] +
                            m[2][1] * m[0][3] * m[1][2];

        inv[7] =  m[0][0] * m[1][2] * m[2][3] -
                            m[0][0] * m[1][3] * m[2][2] -
                            m[1][0] * m[0][2] * m[2][3] +
                            m[1][0] * m[0][3] * m[2][2] +
                            m[2][0] * m[0][2] * m[1][3] -
                            m[2][0] * m[0][3] * m[1][2];

        inv[11] = -m[0][0] * m[1][1] * m[2][3] +
                            m[0][0] * m[1][3] * m[2][1] +
                            m[1][0] * m[0][1] * m[2][3] -
                            m[1][0] * m[0][3] * m[2][1] -
                            m[2][0] * m[0][1] * m[1][3] +
                            m[2][0] * m[0][3] * m[1][1];

        inv[15] = m[0][0] * m[1][1] * m[2][2] -
                        m[0][0] * m[1][2] * m[2][1] -
                        m[1][0] * m[0][1] * m[2][2] +
                        m[1][0] * m[0][2] * m[2][1] +
                        m[2][0] * m[0][1] * m[1][2] -
                        m[2][0] * m[0][2] * m[1][1];

        double det = m[0][0] * inv[0] + m[0][1] * inv[4] + m[0][2] * inv[8] + m[0][3] * inv[12];

        Matrix<T> r; 
        r.set_indentity(); 
        if (det == 0) { return r;  }

        det = 1.0 / det;
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                r.m[i][j] = inv[i*4 + j] * det; 
            }
        }
        return r;
    }

    Matrix<T> transpose() const 
    {
        Matrix<T> r; 
        for(size_t i=0; i<4; ++i)
        {
            for(size_t j=0; j<4; ++j)
            {
                r.m[i][j] = m[j][i]; 
            }
        }
        return r; 
    }


public:
    T m[4][4]; 
}; 



template <typename T>
Matrix<T> Camera_Lookat(const Vector3<T>& eye, const Vector3<T>& at, const Vector3<T>& up)
{
    Matrix<T> r; 

    Vector3<T> z_axis = normal(at - eye); 
    Vector3<T> x_axis = normal(cross(up, z_axis)); 
    Vector3<T> y_axis = normal(cross(z_axis, x_axis)); // 

    r.m[0][0] = x_axis.x; 
    r.m[1][0] = x_axis.y; 
    r.m[2][0] = x_axis.z; 
    r.m[3][0] = -dot(x_axis, eye); 
    r.m[0][1] = y_axis.x; 
    r.m[1][1] = y_axis.y; 
    r.m[2][1] = y_axis.z; 
    r.m[3][1] = -dot(y_axis, eye); 
    r.m[0][2] = z_axis.x; 
    r.m[1][2] = z_axis.y; 
    r.m[2][2] = z_axis.z; 
    r.m[3][2] = -dot(z_axis, eye);

    r.m[0][3] = r.m[1][3] = r.m[2][3] = 0; 
    r.m[3][3] = 1; 
    return r; 
}



template <typename T>
Matrix<T> perspective(const T& fov, const T& aspect, const T& znear, const T& zfar)
{
    Matrix<T> r; 
    r.m[0][0] = static_cast<T>(1.0/(tan(fov * 0.5) * aspect)); 
    r.m[1][1] = static_cast<T>(1.0/tan(fov * 0.5)); 
    r.m[2][2] = zfar / (zfar - znear); 
    r.m[3][2] = - znear * zfar / (zfar - znear); 
    r.m[2][3] = 1; 
    return r; 
}



template <typename T> 
Vector3<T> multi(const Vector3<T>& a, const Matrix<T>& b)
{
    Vector3<T> r; 
    r.x = a.x * b.m[0][0] + a.y * b.m[1][0] + a.z * b.m[2][0] + b.m[3][0];
    r.y = a.x * b.m[0][1] + a.y * b.m[1][1] + a.z * b.m[2][1] + b.m[3][1];
    r.z = a.x * b.m[0][2] + a.y * b.m[1][1] + a.z * b.m[2][2] + b.m[3][2]; 
    return r; 
}
















typedef Matrix<float> mat4f; 


#endif //  _MATRIX_HEAD_  
