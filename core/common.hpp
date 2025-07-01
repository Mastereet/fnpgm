#ifndef FNPGM_CORE_COMMON_HPP
#define FNPGM_CORE_COMMON_HPP

// Eigen library
#include <Eigen/Core>

// typedefs for eigen
// double matricies
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatXXD;
typedef Eigen::Matrix<double, 4, 3> Mat43D;
typedef Eigen::Matrix<double, 4, 2> Mat42;
typedef Eigen::Matrix<double, 3, 3> Mat33D;
typedef Eigen::Matrix<double, 3, Eigen::Dynamic> Mat3XD;
typedef Eigen::Matrix<double, 2, 2> Mat22D;
typedef Eigen::Matrix<double, 2, Eigen::Dynamic> Mat2XD;
typedef Eigen::Matrix<double, 4, 4> Mat44D;
typedef Eigen::Matrix<double, 3, 4> Mat34D;

// float matricies
typedef Eigen::Matrix<float, 3, 3> Mat33f;
typedef Eigen::Matrix<float, 2, 2> Mat22f;
typedef Eigen::Matrix<float, 3, 1> Vec3f;
typedef Eigen::Matrix<float, 2, 1> Vec2f;
typedef Eigen::Matrix<float, 6, 1> Vec6f;
typedef Eigen::Matrix<float, 1, 8> Mat18f;
typedef Eigen::Matrix<float, 6, 6> Mat66f;
typedef Eigen::Matrix<float, 8, 8> Mat88f;
typedef Eigen::Matrix<float, 8, 4> Mat84f;
typedef Eigen::Matrix<float, 6, 6> Mat66f;
typedef Eigen::Matrix<float, 4, 4> Mat44f;
typedef Eigen::Matrix<float, 12, 12> Mat1212f;
typedef Eigen::Matrix<float, 13, 13> Mat1313f;
typedef Eigen::Matrix<float, 10, 10> Mat1010f;
typedef Eigen::Matrix<float, 9, 9> Mat99f;
typedef Eigen::Matrix<float, 4, 2> Mat42f;
typedef Eigen::Matrix<float, 6, 2> Mat62f;
typedef Eigen::Matrix<float, 1, 2> Mat12f;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatXXf;

// double vectors
typedef Eigen::Matrix<double, 9, 1> Vec9D;
typedef Eigen::Matrix<double, 8, 1> Vec8D;
typedef Eigen::Matrix<double, 7, 1> Vec7D;
typedef Eigen::Matrix<double, 6, 1> Vec6D;
typedef Eigen::Matrix<double, 5, 1> Vec5D;
typedef Eigen::Matrix<double, 4, 1> Vec4D;
typedef Eigen::Matrix<double, 3, 1> Vec3D;
typedef Eigen::Matrix<double, 2, 1> Vec2D;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VecXD;
template <typename T>
using VecXX = Eigen::Matrix<T, Eigen::Dynamic, 1>;

// float vectors
typedef Eigen::Matrix<float, 12, 1> Vec12f;
typedef Eigen::Matrix<float, 8, 1> Vec8f;
typedef Eigen::Matrix<float, 10, 1> Vec10f;
typedef Eigen::Matrix<float, 4, 1> Vec4f;
typedef Eigen::Matrix<float, 12, 1> Vec12f;
typedef Eigen::Matrix<float, 13, 1> Vec13f;
typedef Eigen::Matrix<float, 9, 1> Vec9f;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> VecXf;
typedef Eigen::Matrix<float, 14, 1> Vec14f;

template <typename T>
using MatX33 = Eigen::Matrix<T, 3, 3>;

template <typename T>
using RefVecXX = Eigen::Ref<VecXX<T>>;

template <typename T>
using ConstRefVecXX = Eigen::Ref<const VecXX<T>>;
#endif // FNPGM_CORE_COMMON_HPP