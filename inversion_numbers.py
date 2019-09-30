from edx_io import edx_io
with edx_io() as io:
	arr, n, k = [], io.next_int(), 0
	for i in range(n):
		arr.append(io.next_int())
		j=i-1
		while j>=0:
			if arr[j]>arr[i]:
				k+=1
			j-=1
	io.write(k)
	# print(k)