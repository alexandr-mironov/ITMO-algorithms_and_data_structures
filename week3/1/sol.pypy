from edx_io import edx_io
# from functools import reduce
with edx_io() as io:
	n, m = io.next_int(), io.next_int()
	a, b, c = [], [], []

	for i in range(n):
		a.append(io.next_int())
	for i in range(m):
		b.append(io.next_int())

	# for e,g in enumerate(a):
	# 	print(e,g)
	#
	# i=max(a)*max(b)
	# s=10
	# q=0
	# while i:
	# 	i//=s
	# 	q+=1
	# # print(q)
	#
	# def radix(a):
	# 	shift=1
	# 	for x in range(q):
	# 		result = [[] for _ in range(s)]
	# 		numbers = [x for x in range(s)]
	# 		for e, num in enumerate(numbers):
	# 			for arr in a:
	# 				if num == arr % (shift * s) // shift:
	# 					result[e].append(arr)
	# 		a = reduce(lambda x,y: x+y, result)
	# 		shift = shift * s
	# 	return a

	a, b = sorted(a), sorted(b)
	# print(a,b)
	# if n>m:
	# 	a, b, n, m = b, a, m ,n

	# q=0
	for i in range(n):
		for l in range(m):
			c.append(a[i]*b[l])
		# c.append([l * a[i] for l in b])
		# for l in range(m):
		# 	j=a[i]*b[l]
		# 	if j==0:
		# 		c.insert(0,j)
		# 	elif j>=q:
		# 		q=j
		# 		c.append(j)
		# 	else:
		# 		k=len(c)-1
		# 		while c[k]>j:
		# 			k-=1
		# 		c.insert(k+1,j)
		# 		q=j

	# print(c)
	# c=radix(c)
	# print(c)
	c=sorted(c)
	i=len(c)
	l=i//10
	if i%10>0:
		l+=1
	q=0
	for i in range(l):
		q+=int(c[i*10])
	io.write(q)