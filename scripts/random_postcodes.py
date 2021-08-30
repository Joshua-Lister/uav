import string
import random
letters = string.ascii_letters
num_rand_postcodes = 60
x_max = 100
y_max = 100
with open('postal_data.txt', 'w') as f:
    for i in range(num_rand_postcodes):
        line = ["".join([random.choice(letters)for j in range(7)]), str(random.uniform(0,
                x_max)), str(random.uniform(0, y_max)), str(random.uniform(0, 5))]
        for e in line:
            f.write(e + ", ")
        f.write("\n")
