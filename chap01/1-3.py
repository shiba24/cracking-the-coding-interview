#
#
#
# 'Mr%20John%20Smith' = somefunc('Mr John Smith        ')
#
# 

# O(actual_lenght ^ 2)
def URLify(inp_str, actual_length):
    actual_string = inp_str[:actual_length]   # No trailing whitespaces
    out_str = ''
    for i in range(0, actual_length):
        if actual_string[i] == ' ':
            out_str = out_str + '%20'
        else:
            out_str = out_str + actual_string[i]
    return out_str



def URLify(inp_str, actual_length):
    inp_str = inp_str[:actual_length]
    out_len = actual_length + inp_str.count(' ') * 2     # len('%20') - len(' ') = 2 #O(n)
    out_str = ' ' * out_len

    for i in 

    actual_string = inp_str[:actual_length]   # No trailing whitespaces
    out_str = ''
    for i in range(0, actual_length):
        if actual_string[i] == ' ':
            out_str = out_str + '%20'
        else:
            out_str = out_str + actual_string[i]
    return out_str

