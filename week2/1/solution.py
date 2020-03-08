from edx_io import edx_io
import math
with edx_io() as io:
	arr, n = [], io.next_int()
	for i in io.all_tokens():
		arr.append(int(i))

	def merge(a,b,l,r):
		i, j = 0, 0
		n, m = len(a), len(b)
		# print(l,r,a[0],b[m-1])
		c=[]
		while i < n or j < m:
			if j == m or ( i < n and a[i] <= b[j]):
				c.append(a[i])
				i+=1
			else:
				c.append(b[j])
				j+=1
		return c

	def merge_sort(a,l,r):
		# print(a,l,r)
		c=a[l:r]
		# print(c)
		i=len(c)
		if i == 1:
			return c
		h=i//2
		al,ar=merge_sort(a,l,l+h),merge_sort(a,l+h,r)
		io.writeln("{} {} {} {}".format(l+1,r,a[h-1],a[h]))
		# print(l+1,r,a[l],a[r-1])
		return merge(al,ar,l,r-1)
	arr=merge_sort(arr,0,len(arr))

	io.writeln(arr)
	print(arr)