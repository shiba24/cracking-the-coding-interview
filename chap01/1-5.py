    # dog, dogs
# dog, dosg
# dog, sdog

# ssss, sssss
def check_insert_one(str_short, str_long):
    if len(str_short) != len(str_long) - 1:
        return False
    else:
        num_different = 0
        for n in range(0, len(str_short)):
            if str_short[n] != str_long[n + num_different]:
                num_different = num_different + 1
            if num_different > 1:
                return False
        return True
        

def check_replace(str1, str2):
    if len(str1) != len(str2):
        return False
    else:
        num_different = 0
        for n in range(0, len(str1)):
            if str1[n] != str2[n]:
                num_different = num_different + 1
            if num_different > 1:
                return False
        return True


def check_one_away(str1, str2):
    if str1 == str2:        # same
        return True
    elif check_insert_one(str1, str2):  # insert
        return True
    elif check_insert_one(str2, str1):  # remove
        return True
    elif check_replace(str1, str2):     # replace
        return True
    else:
        return False






