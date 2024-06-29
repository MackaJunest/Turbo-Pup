import time, math, Joystick, Serial

class Motion:

    def Wheel_Control():
        global speed
        values=Joystick.Joystick_getValue()
        max_speed=60
        forward_backward_speed = int(-values[1] * max_speed)
        turning_scale_factor = max_speed/ 100
        turning_speed = int(values[0] * 100 * turning_scale_factor)
        # Calculate left and right speeds based on the conditions
        if forward_backward_speed == 0:
            # In-place turning
            left_speed = turning_speed
            right_speed = -turning_speed
        elif forward_backward_speed > 0:
            # Moving forward
            left_speed = forward_backward_speed + turning_speed
            right_speed = forward_backward_speed - turning_speed
        else:
            # Moving backward
            left_speed = forward_backward_speed - turning_speed
            right_speed = forward_backward_speed + turning_speed
        left_speed = max(min(left_speed, max_speed), -max_speed)
        right_speed = max(min(right_speed, max_speed), -max_speed)
        print(f"Left Motor Speed: {left_speed}\tRight Motor Speed: {right_speed}")
        speed=[left_speed,right_speed,values[5]]
        
Joystick.Joystick_INIT()
Serial.COM_INIT()
while 1:
    Joystick.Joystick_getValue()
    Motion.Wheel_Control()
    Serial.Commander_send(speed)




class Motion:

    def Wheel_Control(forbackward, turning):
        global level_shift
        max_speed=60
        differential_Turning_factor=50
    
        # Differential turning logic
        if forbackward != 0.00 :
            leg_level_difference = int(turning * differential_Turning_factor)
            level_shift=[leg_level_difference/2, -leg_level_difference/2]
        else:
            leg_level_difference = 0

        forward_backward_speed = int(-forbackward * max_speed)
        turning_scale_factor = max_speed/ 100
        turning_speed = int(turning * 100 * turning_scale_factor)
        # Calculate left and right speeds based on the conditions
        if forward_backward_speed == 0:
            # In-place turning
            left_speed = turning_speed
            right_speed = -turning_speed
        elif forward_backward_speed > 0:
            # Moving forward
            left_speed = forward_backward_speed + turning_speed
            right_speed = forward_backward_speed - turning_speed
        else:
            # Moving backward
            left_speed = forward_backward_speed - turning_speed
            right_speed = forward_backward_speed + turning_speed
        left_speed = max(min(left_speed, max_speed), -max_speed)
        right_speed = max(min(right_speed, max_speed), -max_speed)
        print(f"Left Motor Speed: {left_speed}\tRight Motor Speed: {right_speed}")
        data=[ left_speed , right_speed]
        return data
=-
