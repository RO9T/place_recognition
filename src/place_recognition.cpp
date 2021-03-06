/*
 *  Node for detecting familiar things and places
 *  Eliot Lim <eliot.lim@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <signal.h>

#include "place_recognition.hpp"
#include "PlaceRecognizer.hpp"

boost::shared_ptr<place_recognizer::PlaceRecognizer> place_recognizer_ptr;

// Detect and save database+vocabulary on shutdown
void mySigintHandler (int sig) {
    ROS_INFO ("SIGTERM received");
    if (place_recognizer_ptr != NULL)
        place_recognizer_ptr->saveDatabase();

    // All the default sigint handler does is call shutdown()
    ros::shutdown();
}


int main (int argc, char** argv) {
    // ros::init must be the first call in main()
    ros::init (argc, argv, "place_recognition");
    ros::NodeHandle nh;

    // Override the default ros sigint handler.
    // This must be set after the first NodeHandle is created.
    signal(SIGINT, mySigintHandler);

    ROS_INFO ("Place Recognition version %s", VERSION_STRING);

    ROS_INFO ("Creating PlaceRecognizer");
    place_recognizer_ptr = boost::shared_ptr<place_recognizer::PlaceRecognizer> (new place_recognizer::PlaceRecognizer());

    ROS_INFO ("Spinner Initialized");
    ros::spin();
}
