import random


def boy_or_girl():
    if random.uniform(0, 1) < 0.5:
        return 'boy'
    else:
        return 'girl'


class Citizens(object):
    def __init__(self, initial_size_male, initial_size_female):
        self.male = initial_size_male
        self.female = initial_size_female
        self.family = min(initial_size_male, initial_size_female)

    def have_child(self):
        baby = boy_or_girl()
        if baby == 'boy':
            self.male = self.male + 1
        elif baby == 'girl':
            self.female = self.female + 1
        return baby

    def repeat_until_having_girl(self):
        baby = self.have_child()
        while baby != 'girl':
            baby = self.have_child()

    def print_demographics(self):
        print('All citizens: {}, male: {}, female: {}'\
              .format(self.male + self.female, self.male, self.female))

    def simulate(self, n_repeat=1000):
        self.print_demographics()
        for i in range(0, n_repeat):
            self.repeat_until_having_girl()
        self.print_demographics()

