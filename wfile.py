import string
import random
letters = string.ascii_letters
with open('postal_data.txt', 'w') as f:
    for i in range(60):
        line = ["".join([random.choice(letters)for j in range(7)]), str(random.uniform(0,
                100)), str(random.uniform(0, 100)), str(random.uniform(0, 5))]
        for e in line:
            f.write(e + ", ")
        f.write("\n")
