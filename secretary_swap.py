from edx_io import edx_io
with edx_io() as io:
	arr, n = [], io.next_int()
	for i in io.all_tokens():
		arr.append(int(i))
	arr_s=sorted(arr)

	for i in range(n):
		# print('EACH',arr[i]!=arr_s[i],arr[i]<arr_s[i])
		if arr[i]!=arr_s[i]:
			k=arr.index(arr_s[i])
			# print(arr)
			arr[i], arr[k] = arr[k], arr[i]
			if k>i:
				a,b=i,k
			else:
				b,a=i,k
			io.writeln("Swap elements at indices {0} and {1}.".format(a+1,b+1))
	# print(arr)
		# arr.append(io.next_int())
		# j=i-1
		# while j>=0 and arr[j]>arr[j+1]:
		# 	arr[j], arr[j+1] = arr[j+1], arr[j]
		# 	io.writeln("Swap elements at indices {0} and {1}.".format(j+1,j+2))
		# 	j-=1

	io.writeln("No more swaps needed.")
	for i in arr:
		io.write("{} ".format(i))
