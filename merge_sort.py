from edx_io import edx_io
import math
with edx_io() as io:
	arr, n = [], io.next_int()
	for i in io.all_tokens():
		arr.append(int(i))

	def merge(a,b):
		print(a,b)
		i, j = 0, 0
		n, m = len(a), len(b)
		c=[]
		while i < n or j < m:
			if j == m or ( i < n and a[i] <= b[j]):
				c.append(a[i])
				i+=1
			else:
				c.append(b[j])
				j+=1
		return c

	def merge_sort(arr):
		i = len(arr)
		if i == 1:
			return arr
		h = math.floor(i/2)
		l,r = arr[0:h], arr[h:i]
		print(l,r)
		l,r = merge_sort(l), merge_sort(r)
		# print(l[0],r[0])
		return merge(l,r)
	arr = merge_sort(arr)
	print(arr)