#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace mmgym {
    // Often used for position, angular velocity, and rotation
    using Vector3d = Eigen::Vector3d;
    using Matrix3d = Eigen::Matrix3d;

    /*
        Commonly used for robot end-effector spatial velocity/torque Twists & Wrenches,
        with the first 3 dimensions for translation and the last 3 for rotation
    */
   using Vector6d = Eigen::Matrix<double, 6, 1>;
   using Matrix6d = Eigen::Matrix<double, 6, 6>;

   // Dynamic-size vectors and matrices
   using VectorXd = Eigen::VectorXd;
   using MatrixXd = Eigen::MatrixXd;

   // Pose Quaternion
   using Quaterniond = Eigen::Quaterniond;

    // [Core Optimization] Specialized dimensions for 7-DOF robotic arms (like Franka Panda)
    // Allocated on the stack, memory is always contiguous, computation with zero delay
    using Vector7d = Eigen::Matrix<double, 7, 1>;
    using Matrix67d = Eigen::Matrix<double, 6, 7>;


struct Pose {
    Vector3d position{Vector3d::Zero()};
    Quaterniond orientation{Quaterniond::Identity()};

    Eigen::Matrix4d to_matrix() const {
        Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
        T.block<3, 3>(0, 0) = orientation.toRotationMatrix();
        T.block<3, 1>(0, 3) = position;
        return T;
    }

    static Pose from_matrix(const Eigen::Matrix4d& T) {
        Pose p;
        p.position = T.block<3, 1>(0, 3);
        p.orientation = Quaterniond(T.block<3, 3>(0, 0));
        return p;
    }
};

} // namespace mmgym