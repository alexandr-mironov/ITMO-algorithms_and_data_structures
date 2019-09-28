from edx_io import edx_io

with edx_io() as io:
	a = io.next_int()
	b = io.next_int()
	io.write( a + b ** 2)