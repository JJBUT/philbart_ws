// Generated by gencpp from file piksi_rtk_msgs/SettingsWriteResponse.msg
// DO NOT EDIT!


#ifndef PIKSI_RTK_MSGS_MESSAGE_SETTINGSWRITERESPONSE_H
#define PIKSI_RTK_MSGS_MESSAGE_SETTINGSWRITERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace piksi_rtk_msgs
{
template <class ContainerAllocator>
struct SettingsWriteResponse_
{
  typedef SettingsWriteResponse_<ContainerAllocator> Type;

  SettingsWriteResponse_()
    : success(false)
    , message()  {
    }
  SettingsWriteResponse_(const ContainerAllocator& _alloc)
    : success(false)
    , message(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _message_type;
  _message_type message;





  typedef boost::shared_ptr< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SettingsWriteResponse_

typedef ::piksi_rtk_msgs::SettingsWriteResponse_<std::allocator<void> > SettingsWriteResponse;

typedef boost::shared_ptr< ::piksi_rtk_msgs::SettingsWriteResponse > SettingsWriteResponsePtr;
typedef boost::shared_ptr< ::piksi_rtk_msgs::SettingsWriteResponse const> SettingsWriteResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace piksi_rtk_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'piksi_rtk_msgs': ['/home/jacksubuntu/philbart_ws/src/ethz_piksi_ros/piksi_rtk_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "937c9679a518e3a18d831e57125ea522";
  }

  static const char* value(const ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x937c9679a518e3a1ULL;
  static const uint64_t static_value2 = 0x8d831e57125ea522ULL;
};

template<class ContainerAllocator>
struct DataType< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "piksi_rtk_msgs/SettingsWriteResponse";
  }

  static const char* value(const ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n\
string message\n\
\n\
";
  }

  static const char* value(const ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
      stream.next(m.message);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SettingsWriteResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::piksi_rtk_msgs::SettingsWriteResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.message);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PIKSI_RTK_MSGS_MESSAGE_SETTINGSWRITERESPONSE_H
