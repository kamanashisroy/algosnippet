

def permute(x):
	if len(x) == 0:
		return []
	if len(x) == 1:
		return [x]
	i = 0;
	result = []
	while i < len(x):
		elem = x[i];
		prefixes = permute(x[0:i])
		suffixes = permute(x[(i+1):])
		for prefix in prefixes :
			for suffix in suffixes :
				y = []
				if prefix is not None:
					y = y + prefix
				if suffix is not None:
					y = y + suffix
				j = 0
				while j < len(y):
					z = y[:]
					z.insert(j,elem)
					result.append(z)
					j+=1
		i+=1
	return result

content = [1,2,3,4,5,6,7]
all_combination = permute(content)
print all_combination

