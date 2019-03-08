// This plugin is based in those that can be found in
// https://bitbucket.org/osrf/gazebo/src/ > (branch gazebo9) > plugins

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

// EXAMPLE OF USAGE
// <model name='your_model'>
//   <pose frame=''>1.1 2.2 3.3 4.4 5.5 6.6</pose>
//   <plugin name="back_and_forth" filename="libback_and_forth.so">
//     <link>link</link>
//     <starting_position>1.1 2.2 3.3</starting_position>
//     <ending_position>9.9 9.9 9.9</ending_position>
//     <speed>2</speed>
//   </plugin>
// </model>
// * <speed> must be in m/s
// * <starting_position> is assumed to coincide with the starting position of the model,
//   so the first three numbers in <pose> of the model should coincide with the three
//   numbers in <starting_position>.
// * if yaw, pitch and roll in initial pose of the model are 0.0, reset of the world will
//   be handled correctly by the plugin, meaning that the model will be moved to <starting_position>
//   with yaw, pitch and roll set to 0.0 and the movement will start from there as it should.

} // namespace gazebo