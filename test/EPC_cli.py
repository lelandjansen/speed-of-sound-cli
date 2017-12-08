import sys
import os
import subprocess
import csv

# user python 2.7

#change python process directory to the location of Drone.jar
os.chdir('/Users/biancaangotti/Documents/Year_4/ECE322/Project/speed-of-sound-cli/build');

with open('speedofsoundEPCtest.csv', 'w') as csvfile:
	spamwriter = csv.writer(csvfile, delimiter=',')
	spamwriter.writerow(['t','h','p','c', 'outputC', 'outputQ', 'outputA'])
	#loop through all combination of EPC values
	temp = [-1,0,30,31]
	humidity = [-0.1,0.0,1.0,1.1]
	pressure = [74999.0, 75000.0, 102000.0, 102001.0]
	co2 = [-0.001,0.00,0.01,0.011]

	for t in temp:
		for h in humidity:
			for p in pressure:
				for c in co2:
					#input them
					proc = subprocess.Popen(["./speed-of-sound-cli"],stdin=subprocess.PIPE, stdout=subprocess.PIPE)
					proc.stdin.write("t\n")
					proc.stdin.write(str(t)+'\n')
					proc.stdin.write("h\n")
					proc.stdin.write(str(h)+'\n')
					proc.stdin.write("p\n")
					proc.stdin.write(str(p)+'\n')
					proc.stdin.write("f\n")
					proc.stdin.write(str(c)+'\n')
					proc.stdin.write("c\n")
					outputC = proc.stdout.readline()
					while("speed of sound: " not in outputC):
						outputC = proc.stdout.readline()
					proc.stdin.write("q\n")
					outputQ = proc.stdout.readline()
					while("speed of sound: " not in outputQ):
						outputQ = proc.stdout.readline()
					proc.stdin.write("a\n")
					outputA = proc.stdout.readline()
					while("approximate speed of sound: " not in outputA):
						outputA = proc.stdout.readline()
					print(str(t)+' '+str(h)+' '+str(p)+' '+str(c)+' '+ str(outputC)+' '+ str(outputQ)+' '+ str(outputA))
					proc.kill()
					spamwriter.writerow([t, h, p, c, outputC, outputQ, outputA])
	#then do one test that's totally legit with all values inside
	proc = subprocess.Popen(["./speed-of-sound-cli"],stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	proc.stdin.write("c\n")
	while("speed of sound: " not in outputC):
		outputC = proc.stdout.readline()
	proc.stdin.write("q\n")
	while("speed of sound: " not in outputQ):
		outputQ = proc.stdout.readline()
	proc.stdin.write("a\n")
	while("approximate speed of sound: " not in outputA):
		outputA = proc.stdout.readline()
	print(str(outputC))
	print(str(outputQ))
	print(str(outputA))
	proc.kill()
	spamwriter.writerow([20, 50, 101325, 0.0314, outputC, outputQ, outputA])

