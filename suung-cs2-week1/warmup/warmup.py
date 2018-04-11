import string

def freq(s):
    '''
    Takes a string as argument and returns the frequencies of each
    letter in a list. The index of elements give the letter the
    frequecies correspond to, e.g. the frequency of 'a' is given by
    the 0th element, the frequency of 'b' is given by the 1st element,
    and so on.

    The time complexity is O(n) as the function loops over each 
    character in the string once.

    The space complexity is O(1) as 'alphabet' and 'frequency' do not
    change in size.
    '''
    alphabet = list(string.ascii_lowercase)
    frequency = [0] * 26

    for letter in s.lower():
	if letter != ' ':
	    i = alphabet.index(letter)
	    frequency[i] += 1
	
    return frequency
		
