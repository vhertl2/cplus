def first_meet(team1, team2):
    """
    :param team1: Enter the first Alien team coming from the left
    :param team2: Enter the second Alien team coming from the right
    :return: Returns a dictionary where the keys are represented by ascending integers, where the lowest value 
    corresponds to the first alien from the team2.
    """
    dictionary = {}
    for i in range(len(team1 + team2)):
        if i < (len(team1)):
            dictionary[i + len(team1)] = team1[i]
        else:
            dictionary[i - len(team2)] = team2[i-len(team1)]

    print("0.  ", end="")
    for j in (team1 + team2):
        print("%s " % j, end="")
    print("\n---------------------")
    return dictionary


def swapper(keys):
    """
    :param keys: Uses keys from function first_meet and sorts them in the required manner 
    :return: Aligned Aliens as desired correspond to the situation when these keys are sorted in ascending order.
    """
    swap = None
    for i in range(len(keys)-1):
        if keys[i] > keys[i+1]:
            if keys[i-1] == swap:
                pass
            else:
                swap = keys[i + 1]
                keys[i + 1] = keys[i]
                keys[i] = swap
    return keys

green = ["A", "B", "C"]  # Aliens coming from the left
blue = ["d", "e", "f"]  # from the right


d = first_meet(blue, green)
numerical_keys = list(d.keys())
current_state = ""
iteration = 1


while numerical_keys != sorted(numerical_keys):
    numerical_keys = swapper(numerical_keys)
    print(str(iteration) + ". ", end="")
    for k in numerical_keys:
        current_state += " " + d[k]
    print(current_state)
    current_state = ""
    iteration += 1
