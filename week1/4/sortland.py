from edx_io import edx_io
import math

with edx_io() as io:
	n = io.next_int()
	arr=[]

	for i in io.all_tokens():
		arr.append(float(i))

	_arr=arr[:]
	arr.sort()

	io.write("{}".format(_arr.index(min(arr))+1) + " ")
	io.write("{}".format(_arr.index(arr[math.ceil(n/2)-1])+1) + " ")
	io.write("{}".format(_arr.index(max(arr))+1) + " ")