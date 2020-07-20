# smartCarCamp

Automatic car competition was held in 2019 at HGU.

In this competition, we used ROS technique and I don't understand all of tech, but I knew all process to activate car.

Furthermore, my team used openCV to detect line and PID control to make the car smooth driving.

We arranged speed on the course (curve, straight line).


Especially, In camera_on code, left and right lines are detected resulting in average values at each line.

In mailbox_node code, PID control and speed arrangement are used.

To understand ROS technique fully, I have to know about network, but I didn't know about that ; msg communication.

And my team analyzed line detection algorithm with Mathematics like these pictures.

![mat1](./img/analyze1)
![mat2](./img/analyze2)
