
def remove_space(strings):
    return strings.replace(' ', '')

def count_string(strings):
    string_dict = {}
    for s in strings:           # O(n)
        if s in string_dict.keys():
            string_dict[s] = string_dict[s] + 1
        else:
            string_dict[s] = 1
    return string_dict


def check_palindrome_of_permutation(strings):
    string_dict = count_string(remove_space(strings.lower()))
    values = string_dict.values()
    count_odd = [i % 2 for i in values]
    if count_odd.count(1) <= 1:
        return True
    else:
        return False





