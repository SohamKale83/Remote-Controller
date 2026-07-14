import serial
import keyboard 

ser = serial.Serial('COM5',115200,timeout=1)

deadzone = 70
center = 512

left_count = 0
right_count = 0
push_count = 0

try: 
    while True:
        if ser.in_waiting>0:
            raw_data = ser.readline()
            clean_data = raw_data.decode('utf-8').strip()

            data_list = clean_data.split()
            length = len(data_list)

            if(length == 7):
                try:
                    vlx = int(data_list[0])
                    vly = int(data_list[1])
                    vrx = int(data_list[2])
                    vry = int(data_list[3])
                    left_sw = int(data_list[4])
                    right_sw = int(data_list[5])
                    push_button = int(data_list[6])

                    if left_sw == 0:
                        left_count += 1
                        if left_count == 4:
                            keyboard.press("a")
                    else:
                        left_count = 0
                        keyboard.release("a")

                    if right_sw == 0:
                        right_count += 1
                        if(right_count == 4):
                            keyboard.press("space")
                    else:
                        right_count = 0
                        keyboard.release("space")

                    if push_button == 0:
                        push_count +=1
                        if push_count == 4:
                            keyboard.press("enter")
                    else:
                        push_count = 0
                        keyboard.release("enter")

                    if(vly > (center + deadzone) ):          
                        keyboard.press("up")
                    else:              
                        keyboard.release("up")
                   
                    if(vly < (center - deadzone)):
                        keyboard.press("down")
                    else:
                        keyboard.release("down")
                    if(vrx < (center - deadzone)):
                        keyboard.press("left")
                    else:
                        keyboard.release("left")
                    if(vrx > (center + deadzone)):
                        keyboard.press("right")
                    else:
                        keyboard.release("right")     
                except ValueError:
                    continue 

except KeyboardInterrupt:
    print("Program stopped without crashing")
finally:     
    ser.close()
    print("PORT closed safely")
