from edx_io import edx_io
with edx_io() as io:
	n, m, k = io.next_int(), io.next_int(), io.next_int()
	a, b, c = [], [], []


	i=max(a)*max(b)
	s=10
	q=0
	while i:
		i//=s
		q+=1
	# print(q)

	def radix(a):
		shift=1
		for x in range(q):
			result = [[] for _ in range(s)]
			numbers = [x for x in range(s)]
			for e, num in enumerate(numbers):
				for arr in a:
					if num == arr % (shift * s) // shift:
						result[e].append(arr)
			a = reduce(lambda x,y: x+y, result)
			shift = shift * s
		return a