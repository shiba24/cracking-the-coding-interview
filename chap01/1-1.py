# input : 'aaaaaaaaaaaa'
# True = somefunc(input)
# False = somefunc('voqu34f')
# False = somefunc(21241)
#

# O(n^2)
def IsUnique(strings):
    for s in strings:
        for t in strings:
            if s == t:
                return False
    return True








