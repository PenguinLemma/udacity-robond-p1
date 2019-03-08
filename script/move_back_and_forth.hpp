#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <functional>
#include <memory>
#include <sdf/sdf.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/common/UpdateInfo.hh>
#include <gazebo/util/system.hh>
#include <gazebo/common/Events.hh>
#include <gazebo/common/Assert.hh>
#include <gazebo/physics/Model.hh>
#include <gazebo/physics/Link.hh>
#include "move_back_and_forth_private.hpp"

namespace gazebo
{

class MoveBackAndForthPluginPrivate;

class GAZEBO_VISIBLE MoveBackAndForthPlugin : public ModelPlugin
{
public:
    MoveBackAndForthPlugin();

    virtual ~MoveBackAndForthPlugin() override;

    virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override;

    virtual void Reset() override;

private:

    void Update(const common::UpdateInfo& _info);

    std::unique_ptr<MoveBackAndForthPluginPrivate> data_;
};

} // namespace gazebo