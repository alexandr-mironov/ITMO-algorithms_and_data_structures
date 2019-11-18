from edx_io import edx_io
import math
with edx_io() as io:
	arr, n = [], io.next_int()
	for i in io.all_tokens():
		arr.append(int(i))

	def merge(a,b,l,r):

		i, j = 0, 0
		n, m = len(a), len(b)
		print(l,r,a[0],b[m-1])
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

	# def merge_sort(arr,ind):
	# 	i = len(arr)
	# 	if i == 1:
	# 		return arr, ind
	# 	h = math.floor(i/2)
	# 	if ind == 0:
	# 		ind1=1
	# 		ind2=h+1
	# 	else:
	# 		ind1=ind
	# 		ind2=ind+h
	# 	l,r = arr[0:h], arr[h:i]
	# 	# print(l,r)
	# 	l,ind1 = merge_sort(l,ind1)
	# 	r,ind2 = merge_sort(r,ind2)
	# 	io.writeln("{} {} {} {}".format(ind1,ind2,l[0],r[0]))
	# 	return merge(l,r), ind
	# arr, ind = merge_sort(arr,0)

	# alternative method
	# global res
	# res = []
	# def merge_sort(arr, a, n):
	# 	if a is None:
	# 		a=0
	# 	if n==1:
	# 		return arr[a]
	# 	print(arr, a, n, res)
	# 	if n is None:
	# 		n = len(arr)
	# 	i, j = 0, 0
	# 	b=math.floor(n/2)
	# 	left, right, = arr[a:b-1], arr[b:n]
	# 	ll, lr = len(left), len(right)
	# 	merge_sort(left,a,ll)
	# 	merge_sort(right,b,lr)
	# 	return res;
	# 	# if ll == 1:

	# def merge_sort(a):
	# 	n = len(a)
	# 	if n < 2:
	# 		return a
	# 	l,r=merge_sort(a[:n//2]),merge_sort(a[n//2:n])
	# 	i,j=0,0
	# 	res=[]
	# 	while i < len(l) or j < len(r):
	# 		if not i < len(l):
	# 			# print(l[i],r[j],i,j)
	# 			res.append(r[j])
	# 			j+=1
	# 		elif not j < len(r):
	# 			# print(l[i],r[j],i,j)
	# 			res.append(l[i])
	# 			i+=1
	# 		elif l[i] < r[j]:
	# 			print(l[i],r[j],i,j)
	# 			res.append(l[i])
	# 			i+=1
	# 		else:
	# 			print(l[i],r[j],i,j)
	# 			res.append(r[j])
	# 			j+=1
	# 	return res


	# arr=merge_sort(arr)
	io.writeln(arr)
	print(arr)