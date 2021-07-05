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

    xsize = 250
    ysize = 250
    t = 0
    dt = 1
    scale =  3.5
    r_disp = 4.0
    offset = (50, 50)
    m1 = man.PyManager(xsize, ysize)
    m1.initialize(5000, 602) 

    pygame.font.init()
    myfont = pygame.font.SysFont('Comic Sans MS', 30)

    while not quit_flag:
        for event in pygame.event.get():
            if(event.type == pygame.QUIT):
                quit_flag = True


        pygame.display.update()
        clock.tick(180)


        m1.sense()
        m1.orient(1)
        m1.move(1)
        positions = m1.getPositions()
        colors = m1.getColors()
        #particles_to_add = m1.regulate(t, .06)
        particles_to_add = 0
        if(particles_to_add != 0):
            print("time:{} creating {} particles".format(t, particles_to_add))
            m1.create_particles(particles_to_add)
        
        textsurface = myfont.render('Timestep: {}'.format(t), False, (255,0,0))

        if( t % 1 == 0 ):
            window.fill((0, 0, 0))
            window.blit(textsurface, (50,10))

            start = time.time()

            ul = np.add(offset, np.multiply(scale, np.array((0,0))))
            lr = np.add(0, np.multiply(scale, np.array((xsize,ysize))))
            rect_coords = (ul[0], ul[1], lr[0], lr[1])

            pygame.draw.rect(window, (255,255,255) , rect_coords, 2)
            for color, position in zip(colors, positions):    
                pygame.draw.circle(window, color, np.add(offset, np.multiply(scale, position)), r_disp, 2)

        t+=dt;     

    pygame.quit()
    quit()


if(__name__ == '__main__'):
    main()
