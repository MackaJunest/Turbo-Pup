import pygame

def Joystick_INIT(): #Init joystick
    global joystick
    # Initialize Pygame
    pygame.init()
    # Set up the joystick
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

def Joystick_getValue(): #get all joystick values [x1,y1,x2,y2,L2,R2,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,h1[0],h1[1]]
    for event in pygame.event.get(): # key events
        if event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")
    joystick_count = pygame.joystick.get_count()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    x1=round(joystick.get_axis(0),3)#left joystick
    y1=round(joystick.get_axis(1),3)#left joystick
    x2=round(joystick.get_axis(2),3)#right joystick
    y2=round(joystick.get_axis(3),3)#right joystick
    L2=round(joystick.get_axis(4))
    R2=round(joystick.get_axis(5))
    b1 = joystick.get_button(0)
    b2 = joystick.get_button(1)
    b3 = joystick.get_button(2)
    b4 = joystick.get_button(3)
    b5 = joystick.get_button(4)
    b6 = joystick.get_button(5)
    b7 = joystick.get_button(6)
    b8 = joystick.get_button(7)
    b9 = joystick.get_button(8)
    b10 = joystick.get_button(9)
    b11 = joystick.get_button(10)
    h1 = joystick.get_hat(0)
    val=[x1,y1,x2,y2,L2,R2,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,h1[0],h1[1]]
    return val
