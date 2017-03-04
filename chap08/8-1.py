

# 4 >> [3,1], [2,2], [2,1,1], [1,3], [1,2,1], [1,1,2], [1,1,1,1]


def triple_step(n_steps):
    if n_steps == 0:
        return 0
    elif n_steps == 1:
        return 1            # [1]
    elif n_steps == 2:
        return 2            # [1, 1] or [2]
    elif n_steps == 3:
        return 4            # [1, 1, 1] or [1, 2] or [2, 1] or [3]
    return triple_step(n_steps - 1) + triple_step(n_steps - 2) + triple_step(n_steps - 3)





