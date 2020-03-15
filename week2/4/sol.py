from edx_io import edx_io
with edx_io() as io:
	n=io.next_int()
	l=io.next_int()
	r=io.next_int()
	arr=[]

	for i in range(5):
		arr.append(int(io.next_int()))

	# _ar=arr[3:5]
	# a=[]
	if n>2:
		for i in range(n-2,n+1):
			k=arr[0]*arr[i]+arr[1]*arr[i+1]+arr[2]
			# k=int.from_bytes(k.to_bytes((k.bit_length() // 8) + 1,byteorder='big'), byteorder='big', signed=True)
			# k=int(k)
			# while k>2147483647 or k<-2147483648:
			# 	if k > 0:
			# 		k=(k-2147483647)*(-1)
			# 	else:
			# 		k=(k+2147483648)*(-1)
			print(i, k)
			# _ar.append(k)
			arr.append(k)

	_ar=sorted(arr[3:])
	# print(_ar)
	for i in range(l,r+1):
		io.write("{} ".format(_ar[i-1]))