

def binary_search(arr, element):
    try:
        if len(arr) == 0:
            return None
        elif len(arr) == 1 and element != arr[0]:
            return None
        mid = int(len(arr) / 2.)
        if element < arr[mid]:
            return binary_search(arr[0:mid], element)
        elif element == arr[mid]:
            return mid
        else: 
            return binary_search(arr[mid:len(arr)], element) + mid
    except TypeError:
        return None


# [1,2,3,4,5,6,7,8,9,10]

# element
# [9,10,1,2,3,4,5,6,7,8]

# [6,7,8,9,10,1,2,3,4,5]

# [3,4,5,6,7,8,9,10,1,2]

def search_in_rotated_array(rotated_arr, element):
    try:
        if len(rotated_arr) == 0:
            return None
        elif len(rotated_arr) == 1 and element != rotated_arr[0]:
            return None
        half = int(len(rotated_arr) / 2.)
        if element == rotated_arr[0]:
            return 0
        elif element == rotated_arr[half]:
            return half
        elif element > rotated_arr[0] or element < rotated_arr[half]:
            return search_in_rotated_array(rotated_arr[0:half], element)
        elif rotated_arr[half] < element < rotated_arr[0]:
            return binary_search(rotated_arr[half:len(rotated_arr)]) + half
    except TypeError:
        return None





