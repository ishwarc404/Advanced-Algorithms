mem = [[100,0],[500,0],[200,0],[300,0],[600,0],[700,0]]

alloc = [212,112,417,426,545]


for i in alloc:
	print "Memeory stack: ",mem
	for j in mem:
		if(i<j[0] and j[1]!=1):
			 #i < j
			free = j[0] - i
			mem = mem[:mem.index(j)] + [[i,1]] +[[free,0]]+ mem[mem.index(j)+1:]
			break

for i in alloc:
	if [i,1] not in mem:
		print "Proccess memory not added:",i

