# Data manipulation imports
import numpy as np
# Matplotlib/visualisation support imports
import matplotlib.pyplot as plt
import matplotlib.animation as animation



# ==> Reading txt file
data= np.loadtxt('ga_data.txt', skiprows=2)

distance = data[:, -2]
count = data[:, -1]


# ==> Plot 1 - Distance vs Count

plt.plot(count, distance)
plt.xlabel('Generation Count')
plt.ylabel('Distance')
plt.savefig('drone_distance.png')


# ==> Plot 2 - Animation of Paths vs Count

fig, ax = plt.subplots()
frames = int(np.prod(data[:,0].shape))

# Extracting x and y data seperately

def x_data(i):
    x_data = data[i, ::2]
    x_data = np.delete(x_data, -1)
    return x_data
def y_data(i):
    y_data = data[i, 1::2]
    y_data = np.delete(y_data, -1)
    return y_data

# Extracting  direction vectors

num_cords = np.prod(x_data(0).shape)
num_dXY = num_cords - 1

d_X = np.empty(num_dXY, dtype=float, order='C')
d_Y = np.empty(num_dXY, dtype=float, order='C')
x_pos = np.empty(num_dXY, dtype=float, order='C')
y_pos = np.empty(num_dXY, dtype=float, order='C')

# Plotting second figure

def set_plot(x, y):
    for i in range(num_dXY):
        dx = x[i+1] - x[i]
        dy = y[i+1] - y[i]
        xpos = (x[i+1] + x[i]) / 2
        ypos = (y[i+1] + y[i]) / 2
        
        d_X[i] = dx
        d_Y[i] = dy
        x_pos[i] = xpos
        y_pos[i] = ypos
        
    ax.scatter(x, y)
    ax.plot(x, y)
    plt.title('Optimisation of route distance with GA')
    plt.xlabel('x')
    plt.ylabel('y')

    # Plot arrow on each line:
    for X,Y,dX,dY in zip(x_pos, y_pos, d_X, d_Y):
        ax.annotate("", xytext=(X,Y),xy=(X+0.001*dX,Y+0.001*dY), 
        arrowprops=dict(arrowstyle="->"))

# Creates initial frame
set_plot(x=x_data(0), y=y_data(0))

def update(i):
    ax.clear()
    count_val = int(count[i])
    distance_val = distance[i]
    set_plot(x=x_data(i), y=y_data(i))
    plt.title(f'Generation: {count_val}\nTotal Route Distance: {distance_val}')
    
ani = animation.FuncAnimation(fig, update, frames=frames, interval=200)
ani.save('route_optimisation.gif', writer='pillow')
