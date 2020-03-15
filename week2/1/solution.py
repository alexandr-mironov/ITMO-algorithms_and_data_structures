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
		h=math.ceil(i/2)
		print(h)
		al,ar=merge_sort(a,l,l+h),merge_sort(a,l+h,r)
		print(al,ar)
		# if len(al)>1 or len(ar)>1:
		io.writeln("{} {} {} {}".format(l+1,r,al[0],ar[h-1]))
		# print(l+1,r+1,al[0],ar[len(ar)-1])
		return merge(al,ar,l,r)
	arr=merge_sort(arr,0,n)

	io.writeln(arr)
	# print(arr)