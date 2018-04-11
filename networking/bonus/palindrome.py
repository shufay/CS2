import itertools
import sys

'''
To run:
	python palindrome.py <string>

The time complexity is O(N) because we iterate through the string and
try to find a palindrome configuration. The worst case is where we: 
	a) obtain a palindrome by iterating through half the string, or 
	b) discover there are two singular letters when we have iterated
	   through half the string.

The space complexity is O(N) because we store the string as a list in
order to alter it in place. 
'''

def palindrome(string):
	original = list(string)
	half = len(string) // 2 + 1
	unpaired = 0
	i = 0

	while i < half:
		# check if string is a palindrome
		reverse = original[::-1]

		if reverse == original:
			return ''.join(original)

		# if there are more than two single letters, it is not 
		# a palindrome
		if unpaired > 1:
			return ''

		char = original[i]

		# get substring that is behind 'char'
		if i == 0:
			sub = original[i+1:]

		else:
			sub = original[i+1:-i]

		# if 'char' is also found in substring, then move 'char' 
		# in substring to the end.
		if sub.count(char) > 0:
			pos = sub.index(char) + i + 1
			del original[pos]

			if i == 0:
				original.append(char)

			else:	
				original.insert(-i, char)
			
			i += 1

		# if there is only one 'char', move 'char' to middle
		else:
			original.insert(half, char)
			del original[i]
			unpaired += 1


if len(sys.argv) != 2:
	usage = 'python palindrome.py <string>'
	print(usage)

else:
	print(palindrome(sys.argv[1]))