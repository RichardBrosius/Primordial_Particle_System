#! /usr/bin/env python3



def split(n_particles):

    NUM_CORES = 8
    divisions = []
    groupsizes = []


    division = n_particles // NUM_CORES
    remainder = n_particles % NUM_CORES
    print(remainder)

    for i in range(0,  NUM_CORES + 1, 1):
        divisions.append( i * division )
    

    i = 0
    for i in range(0, NUM_CORES ):
        if( i < remainder ):            
            divisions[i + 1] += i
        elif ( i >= remainder and i < NUM_CORES):
            divisions[i+1] += remainder
    



    for i in range(1, len(divisions)):
        print(divisions[i] - divisions[i -1] , ': ' , divisions[i-1] , ',',  divisions[i] )


if(__name__ == "__main__"):
    split(5000)