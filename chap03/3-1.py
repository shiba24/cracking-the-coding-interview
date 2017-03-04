


class Threeinone(object):
    def __init__(self, array_size=3):
        self.array = [None] * array_size
        self.sep1 = 1
        self.sep2 = 2

    def get_stack_start_and_end(self, num_stack):
        if num_stack == 0:
            return 0, self.sep1
        elif num_stack == 1:
            return self.sep1, self.sep2
        elif num_stack == 2:
            return self.sep2, len(self.array)
        else:
            raise IndexError('Input num_stack must be 0, 1, or 2.')

    def pop(self, num_stack):
        s, e = self.get_stack_start_and_end(num_stack)
        iterm = self.array.pop(s)

        return 

    def push(self,):

    def peek(self,):

    def isEmpty(self,):
