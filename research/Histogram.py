import pandas as pd
import matplotlib.pyplot as plt

func = 'CRC32'

data = pd.read_csv('data.txt', header = None, names = ['x', 'y'], skiprows = 1)

x = data['x']
y = data['y']

y_max = y.max()
y_var = y.var()

print(y_max, y_var)

plt.figure (figsize =(10, 6))
plt.bar (x, y, color='blue', edgecolor='blue')

plt.xlabel('Number of bucket')
plt.ylabel('Number of elements')
plt.title(func)

plt.grid(True, alpha = 0.3)

plt.ylim(0, 20)
# plt.xlim(0, 3000)

plt.text (0.63, 0.95, f'Max number of elements: {y_max}\nVariance: {y_var:.2f}',
          transform = plt.gca().transAxes,
          fontsize = 12,
          verticalalignment = 'top',
          bbox = dict(facecolor = 'white', alpha = 1.0))

file_name = f'../img/{func}Histogram.png'
plt.savefig(file_name, dpi=300, bbox_inches='tight')

plt.show()
