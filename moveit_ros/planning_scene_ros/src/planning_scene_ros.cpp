/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2011, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#include "planning_scene_ros/planning_scene_ros.h"

bool planning_scene_ros::PlanningSceneROS::loadRobotFromParamServer(void)
{
    std::string name;
    if (nh_.searchParam(robot_description_, name))
    {
        std::string content;
        if (nh_.getParam(name, content))
        {
            if (urdf_.initString(content))
            {
                if (nh_.searchParam(robot_description_ + "_semantic", name))
                {
                    std::string scontent;
                    if (nh_.getParam(name, scontent))
                    {
                        if (srdf_.initString(urdf_, scontent))
                            return configure(urdf_, srdf_);
                        else
                            ROS_ERROR("Unable to parse SRDF");
                    }
                    else
                        ROS_ERROR("Robot semantic description not found. Did you forget to remap '%s_semantic'?", robot_description_.c_str());
                }
                else
                    ROS_ERROR("Robot semantic description not found. Did you forget to remap '%s_semantic'?", robot_description_.c_str());
            }
            else
                ROS_ERROR("Unable to parse URDF");
        }
        else
            ROS_ERROR("Robot model not found! Did you remap '%s'?", robot_description_.c_str());
    }
    else
        ROS_ERROR("Robot model not found! Did you remap '%s'?", robot_description_.c_str());

    return false;
}
