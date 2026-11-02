#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <mmgym/common/math_types.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("Pose Default Initialization", "[math]") {
    mmgym::Pose pose;

    REQUIRE_THAT(pose.position.x(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(pose.position.y(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(pose.position.z(), WithinAbs(0.0, 1e-6));

    REQUIRE_THAT(pose.orientation.w(), WithinAbs(1.0, 1e-6));
    REQUIRE_THAT(pose.orientation.x(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(pose.orientation.y(), WithinAbs(0.0, 1e-6));
    REQUIRE_THAT(pose.orientation.z(), WithinAbs(0.0, 1e-6));
}

TEST_CASE("Pose to Matrix and Back Conversion", "[math]") {
    mmgym::Pose original_pose;
    original_pose.position = mmgym::Vector3d(0.5, -0.2, 0.8);

    // 设定绕 Z 轴旋转 90 度的四元数
    Eigen::AngleAxisd roll_angle(M_PI / 2.0, mmgym::Vector3d::UnitZ());
    original_pose.orientation = mmgym::Quaterniond(roll_angle);

    // 转成 4x4 齐次矩阵
    Eigen::Matrix4d T = original_pose.to_matrix();
    
    // 再逆向转回 Pose
    mmgym::Pose recovered_pose = mmgym::Pose::from_matrix(T);
    
    // 验证位置没有丢失
    REQUIRE_THAT(recovered_pose.position.x(), WithinAbs(0.5, 1e-6));
    REQUIRE_THAT(recovered_pose.position.y(), WithinAbs(-0.2, 1e-6));
    REQUIRE_THAT(recovered_pose.position.z(), WithinAbs(0.8, 1e-6));
    
    // 验证四元数角度一致性
    REQUIRE_THAT(recovered_pose.orientation.w(), WithinAbs(original_pose.orientation.w(), 1e-6));
    REQUIRE_THAT(recovered_pose.orientation.z(), WithinAbs(original_pose.orientation.z(), 1e-6));
}