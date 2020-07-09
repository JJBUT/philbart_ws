#!/usr/bin/env python
import rospy
import tf2_ros
import tf2_geometry_msgs
from tf.transformations import euler_from_quaternion

from std_msgs.msg import Bool
from geometry_msgs.msg import PoseWithCovarianceStamped
from nav_msgs.msg import Odometry
from std_srvs.srv import Empty
from piksi_rtk_msgs.msg import ReceiverState_V2_4_1

import math
from array import array



class localization_transition(object):
    def __init__(self):
        self.receiver_state = None
        self.state = None
        self.amcl_pose = None

        rospy.init_node('localization_transition', anonymous=False)
        self.pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=10, latch=False)
        rospy.Subscriber("/piksi/debug/receiver_state", ReceiverState_V2_4_1, self.receiver_state_cb)
        rospy.Subscriber("/odometry/filtered_map", Odometry, self.map_odom_cb)
        rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, self.amcl_pose_cb)
        self.tf_buffer = tf2_ros.Buffer(rospy.Duration(10))
        self.tf_listner = tf2_ros.TransformListener(self.tf_buffer)
        rospy.wait_for_service('/request_nomotion_update', timeout=5)
        self.nomotion_update = rospy.ServiceProxy('/request_nomotion_update', Empty)

        self.satellite_thresh = rospy.get_param('satellite_thresh', 15)
        self.position_error_thresh = rospy.get_param('position_error_thresh', 5.0)
        self.carrier_noise_thresh = rospy.get_param('carrier_noise_thresh', 150.0)
        self.orientation_error_thresh = rospy.get_param('orientation_error_thresh', 0.785)

    def receiver_state_cb(self, data):
        self.receiver_state=data

    def map_odom_cb(self, data):
        self.state=data

    def amcl_pose_cb(self, data):
        self.amcl_pose=data

    def transform_pose(self, pose, target_frame, source_frame):
        try:
            trans = self.tf_buffer.lookup_transform(target_frame, source_frame, rospy.Time())
        except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException) as e:
            rospy.logerr("TF lookup failed: %s", e)
        transform = self.tf_buffer.lookup_transform(target_frame, source_frame, rospy.Time(0), rospy.Duration(1.0)) 
        pose_tfd = tf2_geometry_msgs.do_transform_pose(pose, transform)     #"tfd": transformed

        return(pose_tfd)

    def pose_difference(self, pose1, pose2):
        #position
        pos_diff= math.sqrt((pose1.position.x-pose2.position.x)**2 + (pose1.position.y-pose2.position.y)**2)    #euclidean norm
        #orientation
        or1=euler_from_quaternion(quaternion=(pose1.orientation.x,pose1.orientation.y,pose1.orientation.z,pose1.orientation.w)) 
        or2=euler_from_quaternion(quaternion=(pose2.orientation.x,pose2.orientation.y,pose2.orientation.z,pose2.orientation.w))
        or_diff=abs(or1[2]-or2[2])
        return(pos_diff, or_diff)

    def carrier_noise(self, cn0):
        try:
            average_noise = sum(cn0) / float(len(cn0))  #use float division to void integer division
        except ZeroDivisionError:
            average_noise = 0
            
        return(average_noise)

    def run(self):
        r = rospy.Rate(5)
        while not rospy.is_shutdown(): 
            #make variables local so that they dont get updated and misaligned by the threaded callbacks while the loop is running
            receiver_state = self.receiver_state
            state = self.state
            amcl_pose = self.amcl_pose



            if not (receiver_state == None or state == None or amcl_pose == None):
                now = rospy.get_time()
                aof_rs = now - receiver_state.header.stamp.secs   #"aof": "age of"
                aof_s = now - state.header.stamp.secs
                aof_ap = now - amcl_pose.header.stamp.secs
    
                timeout = 2
                if not aof_ap < timeout:
                    #call AMCL service to run filter and then publish us a new up-to-date pose
                    try:
                        self.nomotion_update()
                        rospy.logdebug("nomotion_update called")
                    except rospy.ServiceException as e:
                        rospy.logwarn("Service call failed: %s", e)
                elif (aof_rs < timeout and aof_s < timeout):
                    #if all the messages are new then we can test for the need for amcl to have an initial pose
                    #first transform the "amcl_pose" into the "map" frame
                    amcl_pose_tfd = self.transform_pose(amcl_pose.pose, "map", amcl_pose.header.frame_id)

                    pos_diff, or_diff = self.pose_difference(amcl_pose_tfd.pose, state.pose.pose)
                    carrier_noise = self.carrier_noise(list(array("B", receiver_state.cn0)))    #use list array formatting to translate uint[] into python list of ints
        
                    # Now we have checked that all the topics have recieved messages, that the messages are fresh (and if AMCL is stale we call for an update), and we have transformed the AMCL pose into the "map" frame, now we can check if we need to publish an initial pose
                    #intial pose publication conditions:
                        #if the amcl_pose and state odom (x,y,z) have large error
                        #if the num_sat is below four
                        #if the fix_mode is "unkown"
                    ###############AFTER LUNCH START HERE
                    if (pos_diff > self.position_error_thresh or (or_diff > self.orientation_error_thresh and or_diff < 6.28-self.orientation_error_thresh)) and (receiver_state.num_sat < self.satellite_thresh or carrier_noise < self.carrier_noise_thresh):
                        rospy.loginfo("pos_diff: %f      or_diff: %f     satellite_count: %i   carrier_noise: %f", pos_diff, or_diff, receiver_state.num_sat, carrier_noise  )
                        rospy.loginfo("%s", "Transition Detected")
                        initial_pose =  PoseWithCovarianceStamped()  
                        initial_pose.header.frame_id = amcl_pose.header.frame_id    #produce this in the amcl map frame
                        initial_pose.header.stamp = rospy.get_rostime()               

                        initial_pose.pose.pose = self.transform_pose(state.pose, amcl_pose.header.frame_id, "map").pose
                        initial_pose.pose.covariance = [0.25, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                        0.0, 0.25, 0.0, 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0, 0.0, 0.0, 0.1]
                             
                        self.pub.publish(initial_pose)      
                else:
                    #if the messages are old just print out an error and loop
                    rospy.logwarn("Messages are old or not being published, timeout is: %i",timeout)

            else:
                rospy.loginfo("%s", "Not all topics subscribed to yet")
            r.sleep()


if __name__ == '__main__':
    inst=localization_transition()
    inst.run()
