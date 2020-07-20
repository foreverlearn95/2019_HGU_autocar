#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int16.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>
#include <unistd.h>
#include <geometry_msgs/Twist.h>
using namespace std;

geometry_msgs::Twist cmd;
int sub_value=0;
ros::Publisher pub2;
ros::Subscriber sub2;
std_msgs::Int8 msg2;
ros::Subscriber sub3;
int key=0;
int spd=0;
int angle=90;

int past_value=0;
int integralation=0;
int derivative=0;
float p_value=0.6,i_value=0.001,d_value=3; //0.6 0.06 0.5  best : 0.6 0.005 3
int pid(int value){
	derivative=value-past_value;
	int pid_value=float(p_value*value)+float(i_value*integralation)+float(d_value*derivative);
	pid_value=115-pid_value; //90 -> 110
	integralation+=derivative;
	past_value=value;
	if(value==9999){
	spd=0;
	pid_value=0;
	}
return pid_value;
}

void msgCallback(const std_msgs::Int16::ConstPtr& given_msg) {
	sub_value = (given_msg->data);
	if(sub_value<0)sub_value=(sub_value*2)/5; //-150-> -60
	if(sub_value>=0)sub_value=(sub_value*2)/5; //150 -> 60
	//angle=90-sub_value;
	angle=pid(sub_value);
	if(angle>150)angle=150;
	if(angle<30)angle=30;
/*
	if(angle<&& angle> )
		spd = 65;
	else
		spd = 70;
*/
//	cout << angle << endl;
	cmd.linear.x = spd;
	cmd.angular.z=angle;
	pub2.publish(cmd);
}

 

 

//edit FROM HERE

 

//int stp = 0;

 

void msgCallback2(const std_msgs::Int16::ConstPtr& given_msg2)

{

   int stp = given_msg2->data;
   if (stp == 2)
   {
      sleep(1);
	  cmd.linear.x = 0;
   }
   pub2.publish(cmd);
}
//TO HERE 
int main(int argc, char **argv)
{
	cout << "input speed ";
	cin >> spd;
	if(spd > 90) spd = 90;
	cout << "speed: " << spd << endl;
	//for pub to motor
	cmd.linear.x=spd;
	ros::init(argc, argv, "msg_publisher");
	ros::NodeHandle nh2;
    ros::NodeHandle nh4;
	pub2 = nh2.advertise<geometry_msgs::Twist>("data_msg", 100);
	sub2 = nh2.subscribe("cam_msg",100,msgCallback);
	//EDIT

	//pub3 = nh4.advertise<geometry_msgs::Twist>("data_msg2", 100);
	sub3 = nh4.subscribe("stop_msg", 100, msgCallback2);
	ros::Rate loop_rate(1);
	printf("mailbox is started");
	while(ros::ok())
	{
		ros::spinOnce();
	}
	return 0;
}


