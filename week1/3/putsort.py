from edx_io import edx_io

with edx_io() as io:
	n = io.next_int()
	arr=[]
	for i in io.all_tokens():
		arr.append(int(i))

	for i in range(n):
		j=i-1
		key = arr[i]
		while arr[j] > key and j>=0:
			arr[j+1] = arr[j]
			j-=1
		if i == 9:
			io.writeln(j+2)
		else:
			io.write("{}".format(j+2) + " ")
		arr[j+1] = key

	for i in arr:
		io.write("{}".format(i) + " ")
