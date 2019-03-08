#include "move_back_and_forth.hpp"


namespace gazebo
{

GZ_REGISTER_MODEL_PLUGIN(MoveBackAndForthPlugin)

MoveBackAndForthPlugin::MoveBackAndForthPlugin()
{
    std::cout << "MoveBackAndForthPlugin has be loaded" << std::endl;
    data_ = std::make_unique<MoveBackAndForthPluginPrivate>();
}

MoveBackAndForthPlugin::~MoveBackAndForthPlugin() {}

void MoveBackAndForthPlugin::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
    // Make sure the plugin is attached to an existing model
    GZ_ASSERT(_model, "No model found");

    // Make sure link was specified
    if (!_sdf->HasElement("link"))
    {
        gzerr << "<link> element not found in description of MoveBackAndForth plugin; plugin will not function" << std::endl;
        return;
    }

    const std::string link_name = _sdf->Get<std::string>("link");
    data_->link_ = _model->GetLink(link_name);

    // Make sure link was found
    if (!data_->link_)
    {
        gzerr << "Unable to find link[" << link_name
              << "]; plugin MoveBackAndForth will not function" << std::endl;
        return;
    }

    // Make sure starting position was specified
    if(!_sdf->HasElement("starting_position"))
    {
        gzerr << "<starting_position> element not found in description of MoveBackAndForth plugin; plugin will not function" << std::endl;
        return;
    }

    data_->start_pos_ = _sdf->Get<ignition::math::Vector3d>("starting_position");

    // Make sure ending position was specified
    if(!_sdf->HasElement("ending_position"))
    {
        gzerr << "<ending_position> element not found in description of MoveBackAndForth plugin; plugin will not function" << std::endl;
        return;
    }

    data_->end_pos_ = _sdf->Get<ignition::math::Vector3d>("ending_position");

    data_->unit_direction_ = data_->end_pos_ - data_->start_pos_;
    data_->unit_direction_.Normalize();


    // Make sure speed was specified
    if (!_sdf->HasElement("speed"))
    {
        gzerr << "<speed> element not found in description of MoveBackAndForth plugin; plugin will not function" << std::endl;
        return;
    }

    data_->speed_ = std::abs(_sdf->Get<double>("speed"));

    double distance = data_->start_pos_.Distance(data_->end_pos_);
    data_->sign_change_period_ = distance / data_->speed_;

    // Set up initial velocity
    data_->link_->SetLinearVel(data_->speed_ * data_->unit_direction_);

    // Connect to the world update signal
    data_->update_connection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&MoveBackAndForthPlugin::Update, this, std::placeholders::_1));
}

void MoveBackAndForthPlugin::Reset()
{
    // reset model to the initial position. Yaw, pitch and roll might be wrong, as we didn't
    // save that information when loading.
    ignition::math::Quaternion<double> q(0.0, 0.0, 0.0);
    ignition::math::Pose3<double> p(data_->start_pos_, q);
    data_->link_->GetModel()->SetRelativePose(p);

    data_->first_iteration_ = true;
    data_->sign_ = true;
}

void MoveBackAndForthPlugin::Update(const common::UpdateInfo& _info)
{
    // Make sure there is a link selected to be updated
    GZ_ASSERT(data_->link_, "<link> in MoveBackAndForth plugin is null");
    if (!data_->link_)
        return;

    if(data_->first_iteration_)
    {
        data_->previous_sign_change_time_ = _info.simTime;
        data_->first_iteration_ = false;
    }

    if (!(_info.simTime - data_->previous_sign_change_time_ < data_->sign_change_period_))
    {
        data_->previous_sign_change_time_ = _info.simTime;
        data_->sign_ = !data_->sign_;
    }
    data_->link_->SetLinearVel(data_->sign_ ? data_->speed_ * data_->unit_direction_ : -data_->speed_ * data_->unit_direction_);
}

} // namespace gazebo