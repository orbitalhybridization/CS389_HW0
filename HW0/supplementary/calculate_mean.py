#calculate standard devs

import sys,statistics

#take in file and iteration number to search for
file = sys.argv[1]
iteration_search = sys.argv[2]
means = []

with open(file,'r') as f:

    #init loop with first line of file
    line = f.readline()
    current_iters,time = line.split('\t')[0],line.split('\t')[1]
    prev_iters = current_iters

    #continue until we've reached the end of the file
    while True:

        #go through iterations
        while current_iters == prev_iters:

            #if we are at the iteration we're searching for add it to list
            if current_iters == iteration_search:
                means.append(float(time[:-2])) #truncate \n from time
            
            line = f.readline()

            if len(line) == 0:
                break
            
            else: current_iters,time = line.split('\t')[0],line.split('\t')[1]

        if len(line) == 0:
            break
        prev_iters = current_iters
        
    f.close()

mean_time = statistics.mean(means)
print("Mean Time: " + str(mean_time) + " Iterations: " + str(iteration_search))
