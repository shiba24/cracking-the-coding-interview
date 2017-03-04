# somefunc(str1, str2)
#
# example
# True = somefunc('qwerty', 'ytrewq')
# False = somefunc('qwerty', 'yfnbewuav')
#
#

# O(n * log(n))
def is_permutation(str1, str2):
    if len(str1) != len(str2):
        return False
    else:
        sorted_str1 = sorted(str1)          # O(s_1 * log(s_1))
        sorted_str2 = sorted(str2)          # O(s_2 * log(s_2))
        if sorted_str1 == sorted_str2:      # O(s) where s = max(s_1, s_2)
            return True
        else:
            return  False

