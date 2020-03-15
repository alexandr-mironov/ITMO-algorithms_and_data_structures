from edx_io import edx_io
with edx_io() as io:
	n, k = io.next_int(), 0
	arr=list(range(1,n+1))
	for i in range(n):
		if i>1:
			arr[i], arr[i//2] = arr[i//2], arr[i]
	for i in range(n):
		io.write(arr[i])
		if n-i>1:
		 io.write(' ')