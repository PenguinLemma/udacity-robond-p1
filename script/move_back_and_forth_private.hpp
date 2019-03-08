#pragma once

#include <ignition/math/Vector3.hh>
#include <gazebo/physics/Link.hh>
#include <gazebo/common/Time.hh>
#include <gazebo/common/Events.hh>

namespace gazebo
{

class MoveBackAndForthPluginPrivate
{
public:
    MoveBackAndForthPluginPrivate() : speed_(1.0),
                                      sign_(true),
                                      first_iteration_(true),
                                      previous_sign_change_time_(0.0)
    {}

    ~MoveBackAndForthPluginPrivate() {}

    common::Time previous_sign_change_time_;
    common::Time sign_change_period_;
    ignition::math::Vector3d unit_direction_;
    ignition::math::Vector3d start_pos_;
    ignition::math::Vector3d end_pos_;
    event::ConnectionPtr update_connection_;
    double speed_;
    physics::LinkPtr link_;
    bool sign_;
    bool first_iteration_;
};

} // namespace gazebo