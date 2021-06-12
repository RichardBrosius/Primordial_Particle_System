#!/usr/bin/env python3
import pygame
import particle
import random


def main():

    pygame.init()
    
    window = pygame.display.set_mode((1000,1000))
    pygame.display.set_caption('PPS Sim')
    clock = pygame.time.Clock()

    quit_flag = False

    substrate = []
    pid = 0

    random.seed(30)

    particles = 465

    for i in range(0, particles):
        x = random.randint(10, 80)
        y = random.randint(10, 80)
        phi = random.randint(0, 360)

        substrate.append(particle.Particle(window, i, (x, y), phi=phi))

    t = 0
    dt = 1

    while not quit_flag:
        for event in pygame.event.get():
            if(event.type == pygame.QUIT):
                quit_flag = True


        pygame.display.update()
        clock.tick(10)

        window.fill((0, 0, 0))
        for p in substrate:
            p.sense(substrate)
            p.orient(dt)
            p.move(dt)
            p.render(window)

        t += dt

    pygame.quit()
    quit()


if(__name__ == '__main__'):
    main()
