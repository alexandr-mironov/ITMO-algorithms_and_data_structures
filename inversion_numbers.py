from edx_io import edx_io
import math
with edx_io() as io:
	arr, n = [], io.next_int()
	k=0
	for i in io.all_tokens():
		arr.append(int(i))

	for i in range(n):
		j=i+1
		while j>=0 and j<n:
			if arr[i]>arr[j]:
				k+=1
			j+=1

	io.write(k)
	print(k)