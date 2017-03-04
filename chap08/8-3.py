

def is_magic_index(element, i):
    pass


def find_magic_index(array):
    index = 0
    magic_index = []
    while index < len(array):
        if array[index] == index:
            magic_index.append(index)
            index += 1
        elif array[index] < index:
            index += 1
        else:
            index = array[index]
    return magic_index


