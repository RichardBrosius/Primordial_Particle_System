#!/usr/bin/env python3
import pygame
import man
import part
import random
import numpy as np


def main():



    pygame.init()
    
    window = pygame.display.set_mode((1000,1000))
    
    pygame.display.set_caption('PPS Sim')
    clock = pygame.time.Clock()

    quit_flag = False

    substrate = []
    pid = 0

    input("wait")


    m1 = man.PyManager()
    m1.initialize(5000, 4)


    t = 0
    dt = 1
    scale = 2.5
    r_disp = 4
    offset = (100, 100)



    while not quit_flag:
        for event in pygame.event.get():
            if(event.type == pygame.QUIT):
                quit_flag = True


        pygame.display.update()
        clock.tick(30)


        m1.sense()
        m1.orient(1)
        m1.move(1)
        positions = m1.getPositions()
        colors = m1.getColors()


        if( t % 2 == 0):
            window.fill((0, 0, 0))
            for color, position in zip(colors, positions):    
                pygame.draw.circle(window, color, np.add(offset, np.multiply(scale, position)), r_disp, 2)
                #print(color)
                #pygame.draw.line(window, color, scale * position, np.add(np.multiply(scale, position), norm))

        t+=1;     



    pygame.quit()
    quit()


if(__name__ == '__main__'):
    main()
