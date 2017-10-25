    def __init__(self, n_input, n_nodes=5, eta=0.1):
        self.n_input = n_input
        self.n_nodes = n_nodes
        self.eta = eta

    def __call__(self, x):
        self.x = x
        self.h = affine(self.x, self.W1, self.b1)
        self.y = affine(self.h, self.W2, self.b2)
        return self.y

    def initialize_Wb(self, initial_W=0., initial_b=0.1):
        self.W1 = [[initial_W for i in range(self.n_input)] for i in range(self.n_nodes)]
        self.b1 = [initial_b for i in range(self.n_nodes)]
        self.W2 = [[initial_W for i in range(self.n_nodes)] for i in range(self.n_input)]
        self.b2 = [initial_b for i in range(self.n_input)]

    def forward(self, x):
        self.loss = rms(x, self(x)) / 2.        

    def backward(self):
        gy = subtract_vector(self.y, self.x)
        gW2 = outer(gy, self.h)
        gb2 = gy
        gh = affine(gy, transpose(self.W2), [0] * len(self.W2[0]))
        gW1 = outer(gh, self.x)
        gb1 = gh
        self.W2 = subtract_vector(self.W2, multiple_scalar(gW2, self.eta))
        self.b2 = subtract_vector(self.b2, multiple_scalar(gb2, self.eta))
        self.W1 = subtract_vector(self.W1, multiple_scalar(gW1, self.eta))
        self.b1 = subtract_vector(self.b1, multiple_scalar(gb1, self.eta))



