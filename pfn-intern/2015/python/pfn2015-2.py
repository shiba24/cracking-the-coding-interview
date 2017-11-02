import numpy as np

def zca_whitening(X, epsilon=1e-5):
    sigma = np.cov(X, rowvar=True)      # (M, M)
    # Singular Value Decomposition. X = U * np.diag(S) * V
    # U: [M x M] eigenvectors of sigma.
    # S: [M x 1] eigenvalues of sigma.
    # V: [M x M] transpose of U
    U,S,V = np.linalg.svd(sigma)
    # ZCA Whitening matrix: U * Lambda * U'
    ZCAMatrix = np.dot(U, np.dot(np.diag(1.0/np.sqrt(S + epsilon)), U.T)) # [M x M]
    return ZCAMatrix

