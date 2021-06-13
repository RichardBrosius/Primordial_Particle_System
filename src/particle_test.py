#!/usr/bin/env python3

import man
import part
import array as arr
import numpy as np



def main_test():
    #p1 = part.PyParticle(1,arr.array("d",[1,2]), 1, 180)
    # p2 = part.PyParticle(1,arr.array("d",[3,4]), 1, 180)

    # substrate = np.array([p1.position(), p2.position()])
    # print('Starting Substarte \n', substrate)

    # p1.sense(substrate)
    # p1.orient(1)
    # p1.move(1)

    # p2.sense(substrate)
    # p2.orient(1)
    # p2.move(1)

    # print('Ending Substrate \n', substrate)

    print(man)
    print(part)
    m1 = man.PyManager()
    m1.initialize(2)
    print(m1.getPositions())
    print("Moving Particles")
    m1.move(1)
    print(m1.getPositions())

if(__name__ == '__main__'):
    main_test()
