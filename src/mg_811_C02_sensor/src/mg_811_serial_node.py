#!/usr/bin/env python

import rospy
from mg_811_serial import SerialConnection

from mg_811_C02_sensor.msg import MG811Msg

def talker():
    frame = rospy.get_param( 'frame', "mg_811_link" )
    port = rospy.get_param( 'port', '/dev/ttyACM0' )
    baudrate = rospy.get_param( 'baudrate', 9600 )
    timeout = rospy.get_param( 'timeout', 1 )

    mg_811_connection = SerialConnection( port, baudrate, timeout )
    pub = rospy.Publisher('mg_811_data', MG811Msg, queue_size=2)
    rate = rospy.Rate(1) 
    while not rospy.is_shutdown():
        concentration = mg_811_connection.readSerialLine()
        mg_811_msg = MG811Msg()
        mg_811_msg.header.stamp = rospy.Time.now()
        mg_811_msg.header.frame_id = frame
        mg_811_msg.concentration = concentration
        pub.publish( mg_811_msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass