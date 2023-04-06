#!/usr/bin/env python3
import pygame
import man
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
    seed_cell = 40 # 60
    dense = (10, 10)

    m1.initialize(5000 - seed_cell, 602)
    #m1.initialize(0, 602)



    #m1.create_particles(seed_cell, 110, 110, 30, 30) // 250 x 250 world
    #m1.create_particles(seed_cell, offset[0] - xsize, offset[1] - ysize,  dense[0], dense[1])
    m1.create_particles(seed_cell, offset[0] - xsize + 15, offset[1] - ysize + 15,  dense[0], dense[1])


    spores = []
    cells = []
    types = [0,0]
    types_old = [0,0]

    #Store counts here
    #log =  open("../log/count_log.csv", "w")
    #log.write("{},{},{},{},{},{}\n".format("time", "Magenta", "Blue", "Yellow", "Brown", "Green"))



    pygame.font.init()
    myfont = pygame.font.SysFont('Comic Sans MS', 30)

    while not quit_flag:
        for event in pygame.event.get():
            if(event.type == pygame.QUIT):
                quit_flag = True


        pygame.display.update()
        clock.tick(15)


        m1.sense(8)
        m1.orient(dt)
        m1.move(dt)
        positions = m1.getPositions()
        colors = m1.getColors()

        types = m1.count_types()




        particles_to_add = 0
        if(particles_to_add != 0):
            print("time:{} creating {} particles".format(t, particles_to_add))
            m1.create_particles(particles_to_add, xsize, ysize)

        textsurface = myfont.render('Timestep: {}'.format(t), False, (255,0,0))

        if( t % 2 == 0 ):
            window.fill((0, 0, 0))
            window.blit(textsurface, (50,10))

            start = time.time()

            ul = np.add(offset, np.multiply(scale, np.array((0,0))))
            lr = np.add(0, np.multiply(scale, np.array((xsize,ysize))))
            rect_coords = (ul[0], ul[1], lr[0], lr[1])

            pygame.draw.rect(window, (255,255,255) , rect_coords, 2)
            for color, position in zip(colors, positions):
                pygame.draw.circle(window, color, np.add(offset, np.multiply(scale, position)), r_disp, 2)

        t+=dt


    #log.close()
    pygame.quit()
    quit()


if(__name__ == '__main__'):
    main()
