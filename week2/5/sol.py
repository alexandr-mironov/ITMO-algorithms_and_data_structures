from edx_io import edx_io
with edx_io() as io:
	n=io.next_int()
	m=io.next_int()
	arr=[]

	for i in range(n):
		arr.append(int(io.next_int()))

	# def qsort(left, right):
	# 	key = arr[(left + right)//2][0];
	# 	i = left;
	# 	j = right;
	# 	while True:
	# 		while arr[i][0] < key:
	# 			i += 1
	# 		while arr[j][0] > key:
	# 			j -= 1
	# 		if i <= j:
	# 			arr[i], arr[j] = arr[j], arr[i];
	# 		i += 1
	# 		j -= 1
	# 		if i > j:
	# 			break;
	# 	if left < j:
	# 		qsort(left, j);
	# 	if i < right:
	# 		qsort(i, right);

	def ver(m):
		if m == 1:
			return "YES"
		for i in range(n):
			k = 0
			j = 0
			while j < len(A[arr[i][0]]):
				if abs(i - A[arr[i][0]][j]) % m == 0:
					k += 1
					A[arr[i][0]].pop(j)
				j += 1;
			if (k==0):
				return "NO"
		return "YES"

	A = dict();
	for i in range(n):
		arr[i] = [int(arr[i]), i]
		A[arr[i][0]] = A.get(arr[i][0],[])
		A[arr[i][0]].append(arr[i][1])
	# qsort(0, n-1);
	arr=sorted(arr)
	io.write(ver(m))