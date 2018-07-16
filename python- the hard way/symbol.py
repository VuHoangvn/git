def generator():
	for i in range(6):
		yield i*i
		
g = generator()
for i in g:
	print(i)