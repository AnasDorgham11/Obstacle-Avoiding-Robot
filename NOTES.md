These notes are based on my experiences throughout this project. Most of the points mentioned here are not verified facts but are derived from my trials. Therefore, some information may be accurate, while other points may need to be revised. If I learn new concepts or realize that I've misunderstood something, I will update this file.

## DC Motors
-	It is common to observe differences in efficiency between motors, even when they come in the same package and have the same specifications. Therefore, if you need the motors to run at the same RPM, simply applying the same PWM signal to each motor is not sufficient. To address this issue, I used an approach in the "HAL/CAR/2_WHEELS/MOVEMENT.c" file to ensure that a 2-wheeled car moves forward or backward without deviation. I achieved this by controlling each motor individually using separate timers, allowing each motor to have an independent speed percentage (duty cycle), ensuring they both reach the same RPM. Functions for managing different speeds for each motor follow the naming convention: "CAR_MOVEMENT_DifferentSpeeds_...".

-	Even after implementing functions to handle the different speeds for each motor, I found that sometimes I could not achieve a point where the two motors worked at the same RPM. I was using a prescaler of 8, so I tried with 64, and they both finally had the same speed. My reasoning for this is that a prescaler of 8 provides faster machine cycles compared to a prescaler of 64, making the difference in efficiency more pronounced with a prescaler of 8. The faster the clock cycle, the more noticeable the difference in efficiency.

-	At one point, I noticed the DC motors would stop suddenly and then resume moving, repeating this cycle. After investigation, I discovered that the issue was caused by the ULTRASONIC_EchoHandler(). This function is triggered by an external interrupt on the falling or rising edge of the input voltage. The problem occurred because I was printing the distance inside this function, followed by a delay. As a result, when the DC motors reached their output compare match value, causing the voltage to drop (executing the PWM), the voltage remained low for an extended period due to the delay in the echo handler. To resolve this, I moved the print statements to main.c, ensuring that the ultrasonic trigger and distance calculations occur outside the interrupt handler. This minimized the time spent in the interrupt, allowing the motors to operate without unexpected stops.
To avoid similar issues, always ensure that interrupt service routines are kept as short as possible, handling only critical tasks, and move non-essential operations like printing or delays outside of the ISR

-	I control the DC motors using Timer 2 when they run at the same speed and Timer2 and Timer1 when they run at different speeds. The reason is to ensure a higher interrupt priority for Timer2 than Timer0 if interrupts occur simultaneously. This prioritization prevents the car from stopping abruptly, especially since car movement should be a high-priority task. Although it’s unlikely that an issue would arise with short ISRs, it is a precaution. The priority order is as follows: Timer2 > Timer1 > Timer0.

  
## Servo Motor
-	After several failed attempts to control the servo motor, I discovered that the appropriate prescaler for controlling a servo motor with a 16 MHz microcontroller is 256, regardless of the desired period. This results in a frequency of 16 MHz / 256 = 62.5 kHz per machine cycle.

-	The duty cycle values required to rotate the servo motor 90° clockwise or counterclockwise may not align with theoretical values. It's often necessary to determine the correct duty cycles through trial and error.


## Kit Powering
-	If you’re using an external power supply to power the kit instead of relying on USB power from a computer, ensure that the voltage is suitable for both the kit and its components. I found that using high-voltage batteries caused the LCD to malfunction, displaying erratic behavior that could have led to permanent damage if I had continued. To resolve this, I used a step-down (buck) converter with a potentiometer to control the voltage level.
While some kits may have internal regulators to manage incoming voltage, the voltage could still be slightly too high. In such cases, you can adjust the voltage using the converter until you achieve the same contrast on the LCD as when powered by the computer.

