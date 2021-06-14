#!/usr/bin/env python3
import pygame
import man
import part
import random
import numpy as np

import time
import numpy as np



def main():



    pygame.init()
    
    window = pygame.display.set_mode((1000,1000))
    
    pygame.display.set_caption('PPS Sim')
    clock = pygame.time.Clock()

    quit_flag = False

    substrate = []
    pid = 0

    #input("wait")


    m1 = man.PyManager()
    m1.initialize(5000, 93)


    t = 0
    dt = 1
    scale =  2.5
    r_disp = 4
    offset = (100, 100)


    pygame.font.init()
    myfont = pygame.font.SysFont('Comic Sans MS', 30)


    sense_times = []
    position_times = []
    graphics_times = []

    while not quit_flag:
        for event in pygame.event.get():
            if(event.type == pygame.QUIT):
                quit_flag = True


        pygame.display.update()
        clock.tick(30)


        start = time.time()
        m1.sense()
        end = time.time()
        sense_times.append(end-start)

        m1.orient(1)
        m1.move(1)
        start = time.time()
        positions = m1.getPositions()
        end = time.time()
        position_times.append(end-start)

        colors = m1.getColors()
        textsurface = myfont.render('Timestep: {}'.format(t), False, (255,0,0))

        if( t % 1 == 0):
            pass
            window.fill((0, 0, 0))
            window.blit(textsurface, (50,10))

            start = time.time()
            for color, position in zip(colors, positions):    
                pygame.draw.circle(window, color, np.add(offset, np.multiply(scale, position)), r_disp, 2)
                #pygame.draw.line(window, color, scale * position, np.add(np.multiply(scale, position), norm))
                pass
            end = time.time()

            graphics_times.append(end - start)
        t+=dt;     


    print('Sense: avg {}, \t std {}'.format(np.average(sense_times), np.std(sense_times)))
    print('Position: avg {}, \t std {}'.format(np.average(position_times), np.std(position_times)))
    print('Graphics: avg {}, \t std {}'.format(np.average(graphics_times), np.std(graphics_times)))


    pygame.quit()
    quit()


if(__name__ == '__main__'):
    main()
