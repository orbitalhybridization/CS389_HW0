#calculate standard devs

import sys,statistics

#take in file
file = sys.argv[1]

variances = {}

with open(file,'r') as f:

    #init loop with first line of file
    time_list = []
    line = f.readline()
    current_iters,time = line.split('\t')[0],line.split('\t')[1]
    prev_iters = current_iters

    #continue until we've reached the end of the file
    while True:

        #go through the times for this iteration number and add them to a list
        while current_iters == prev_iters:
            time_list.append(float(time[:-2])) #truncate \n from time
            line = f.readline()
            if len(line) == 0:
                break
            current_iters,time = line.split('\t')[0],line.split('\t')[1]

        if len(line) == 0:
            break
        #once we have all the data from this iteration number, calculate sd and add to dictionary
        variances[current_iters] = statistics.variance(time_list)
        time_list = []
        prev_iters = current_iters
    
    f.close()

variance_times = variances.values()
variance_times.sort()
minimum_variance = variance_times[0]

for key in variances:

    if variances[key] == minimum_variance:
        
        stable_iterations = key
        break


print("Minimum Variance: " + str(minimum_variance) + "\n" + "Iterations: " + str(stable_iterations))
