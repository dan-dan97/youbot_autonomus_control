#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <ros_node_control.hpp>
#include <keyboard_lib.hpp>
#include <gamepad_lib.hpp>

int main() {

    Keyboard keyboard;
    Gamepad gamepad;

    ROSNodeControl::ROSmaster.run();
    ROSNodeControl controlLaunch(ROSNodeInfo::NodeType::LAUNCH, "", "/home/youbot/ROS_Projects/launch/starline_youbot_control.launch");

    bool controlStarted = 0;
    boost::posix_time::ptime lastStartButtonUpTime = boost::posix_time::microsec_clock::local_time();

    while(true){  
        if(!gamepad.keyDown(BTN_START) && gamepad.keyPush(BTN_START)){
            if(!controlStarted){
                controlStarted = 1;
                controlLaunch.run();
            }
            else{
                controlLaunch.killChild(ROSNodeInfo(ROSNodeInfo::NodeType::NODE, "youbot_driver_ros_interface", "youbot_driver_ros_interface"));
            }
        }

        if(!gamepad.keyDown(BTN_START))
            lastStartButtonUpTime = boost::posix_time::microsec_clock::local_time();
        else {
			long timePast = (boost::posix_time::microsec_clock::local_time() - lastStartButtonUpTime).total_milliseconds();
			if(timePast >= 5000){
				system("sudo reboot");
			}
            if(controlStarted && timePast >= 2000) {
                controlStarted = 0;
                controlLaunch.kill();
                controlLaunch.waitKilling();
            }
        }   
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }

    ROSNodeControl::ROSmaster.kill();
    ROSNodeControl::ROSmaster.waitKilling();
    return 0;
}
