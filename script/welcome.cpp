#include <gazebo/gazebo.hh>
#include <iostream>

namespace gazebo
{

class WelcomeWorldPlugin : public WorldPlugin
{
public:
    WelcomeWorldPlugin()
    {
        std::cout << "Welcome to ______________'s World!" << std::endl;
        std::cout << "heh... anonimity for the review :P" << std::endl;
    }

    void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) override {}
};

GZ_REGISTER_WORLD_PLUGIN(WelcomeWorldPlugin)

} // namespace gazebo